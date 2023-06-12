/*
 * Copyright (c) 2021 Ubique Innovation AG <https://www.ubique.ch>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 *  SPDX-License-Identifier: MPL-2.0
 */

#include "Tiled2dMapVectorSourceRasterTileDataManager.h"
#include "PolygonCompare.h"
#include "Tiled2dMapVectorLayer.h"

Tiled2dMapVectorSourceRasterTileDataManager::Tiled2dMapVectorSourceRasterTileDataManager(
        const WeakActor<Tiled2dMapVectorLayer> &vectorLayer,
        const std::shared_ptr<VectorMapDescription> &mapDescription,
        const std::string &source,
        const WeakActor<Tiled2dMapRasterSource> &rasterSource)
        : Tiled2dMapVectorSourceTileDataManager(vectorLayer, mapDescription, source),
          rasterSource(rasterSource) {}

void Tiled2dMapVectorSourceRasterTileDataManager::onRasterTilesUpdated(const std::string &layerName,
                                                                       std::unordered_set<Tiled2dMapRasterTileInfo> currentTileInfos) {
    auto mapInterface = this->mapInterface.lock();
    {
        auto graphicsFactory = mapInterface ? mapInterface->getGraphicsObjectFactory() : nullptr;
        auto coordinateConverterHelper = mapInterface ? mapInterface->getCoordinateConverterHelper() : nullptr;
        auto shaderFactory = mapInterface ? mapInterface->getShaderFactory() : nullptr;
        if (!graphicsFactory || !shaderFactory) {
            return;
        }

        std::unordered_set<Tiled2dMapRasterTileInfo> tilesToAdd;
        std::unordered_set<Tiled2dMapRasterTileInfo> tilesToKeep;

        std::unordered_set<Tiled2dMapTileInfo> tilesToRemove;

        for (const auto &rasterTileInfo: currentTileInfos) {
            if (tiles.count(rasterTileInfo.tileInfo) == 0) {
                tilesToAdd.insert(rasterTileInfo);
            } else {
                tilesToKeep.insert(rasterTileInfo);
            }
        }

        for (const auto &[tileInfo, _]: tiles) {
            bool found = false;
            for (const auto &currentTile: currentTileInfos) {
                if (tileInfo == currentTile.tileInfo) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                tilesToRemove.insert(tileInfo);
            }
        }

        std::unordered_map<Tiled2dMapTileInfo, Tiled2dMapLayerMaskWrapper> newTileMasks;
        for (const auto &tileEntry : tilesToKeep) {

            size_t existingPolygonHash = 0;
            auto it = tileMaskMap.find(tileEntry.tileInfo);
            if (it != tileMaskMap.end()) {
                existingPolygonHash = it->second.getPolygonHash();
            }
            const size_t hash = std::hash<std::vector<::PolygonCoord>>()(tileEntry.masks);

            if (hash != existingPolygonHash) {

                const auto &tileMask = std::make_shared<PolygonMaskObject>(graphicsFactory,
                                                                           coordinateConverterHelper);

                tileMask->setPolygons(tileEntry.masks);

                newTileMasks[tileEntry.tileInfo] = Tiled2dMapLayerMaskWrapper(tileMask, hash);
            }
        }

        if (tilesToAdd.empty() && tilesToRemove.empty() && newTileMasks.empty()) return;

        for (const auto &tile : tilesToAdd) {

            std::unordered_set<int32_t> indexControlSet;

            tiles[tile.tileInfo] = {};

            for (int32_t index = 0; index < mapDescription->layers.size(); index++) {
                auto const &layer= mapDescription->layers.at(index);
                if (layer->getType() != VectorLayerType::raster || layer->identifier != layerName) {
                    continue;
                }

                if (!(layer->minZoom <= tile.tileInfo.zoomIdentifier && layer->maxZoom >= tile.tileInfo.zoomIdentifier)) {
                    continue;
                }
                const auto data = tile.textureHolder;
                if (data) {

                    std::string identifier = layer->identifier;
                    Actor<Tiled2dMapVectorTile> actor = createTileActor(tile.tileInfo, layer);

                    if (actor) {
                        if (selectionDelegate) {
                            actor.message(&Tiled2dMapVectorTile::setSelectionDelegate, selectionDelegate);
                        }

                        indexControlSet.insert(index);

                        tiles[tile.tileInfo].push_back({index, identifier, actor.strongActor<Tiled2dMapVectorTile>()});

                        actor.message(&Tiled2dMapVectorTile::setRasterTileData, data);
                    }
                }
            }

            if (indexControlSet.empty()) {
                rasterSource.message(&Tiled2dMapRasterSource::setTileReady, tile.tileInfo);
            } else {
                tilesReadyControlSet[tile.tileInfo] = indexControlSet;
            }
        }

        if (!(newTileMasks.empty() && tilesToRemove.empty())) {
            auto castedMe = std::static_pointer_cast<Tiled2dMapVectorSourceTileDataManager>(shared_from_this());
            auto selfActor = WeakActor<Tiled2dMapVectorSourceTileDataManager>(mailbox, castedMe);
            selfActor.messagePrecisely(MailboxDuplicationStrategy::replaceNewest, MailboxExecutionEnvironment::graphics, &Tiled2dMapVectorSourceTileDataManager::updateMaskObjects, newTileMasks, tilesToRemove);
        }
    }
    mapInterface->invalidate();

}

void Tiled2dMapVectorSourceRasterTileDataManager::onTileCompletelyReady(const Tiled2dMapTileInfo tileInfo) {
    rasterSource.message(&Tiled2dMapRasterSource::setTileReady, tileInfo);
}

void Tiled2dMapVectorSourceRasterTileDataManager::updateLayerDescription(std::shared_ptr<VectorLayerDescription> layerDescription,
                                                                     int32_t legacyIndex, bool needsTileReplace) {
    auto mapInterface = this->mapInterface.lock();
    if (!mapInterface) {
        return;
    }

    auto const &currentTileInfos = rasterSource.converse(&Tiled2dMapRasterSource::getCurrentTiles).get();

    for (const auto &tileData: currentTileInfos) {
        auto subTiles = tiles.find(tileData.tileInfo);
        if (subTiles == tiles.end()) {
            continue;
        }

        if (needsTileReplace) {
            // Remove invalid legacy tile (only one - identifier is unique)
            subTiles->second.erase(std::remove_if(subTiles->second.begin(), subTiles->second.end(),
                                                  [&identifier = layerDescription->identifier]
                                                          (const std::tuple<int32_t, std::string, Actor<Tiled2dMapVectorTile>> &subTile) {
                                                      return std::get<1>(subTile) == identifier;
                                                  }));

            // If new source of layer is not handled by this manager, continue
            if (layerDescription->source != source) {
                continue;
            }

            // Re-evaluate criteria for the tile creation of this specific sublayer
            if (!(layerDescription->minZoom <= tileData.tileInfo.zoomIdentifier && layerDescription->maxZoom >= tileData.tileInfo.zoomIdentifier)) {
                continue;
            }

            Actor<Tiled2dMapVectorTile> actor = createTileActor(tileData.tileInfo, layerDescription);
            if (actor) {
                if (selectionDelegate) {
                    actor.message(&Tiled2dMapVectorTile::setSelectionDelegate, selectionDelegate);
                }

                if (subTiles->second.empty()) {
                    subTiles->second.push_back(
                            {legacyIndex, layerDescription->identifier, actor.strongActor<Tiled2dMapVectorTile>()});
                } else {
                    auto insertionPoint = std::lower_bound(subTiles->second.begin(), subTiles->second.end(), legacyIndex, [](const auto& subTile, int index) {
                        return std::get<0>(subTile) < index;
                    });

                    subTiles->second.insert(insertionPoint, {legacyIndex, layerDescription->identifier, actor.strongActor<Tiled2dMapVectorTile>()});
                }

                auto indexControlSet = tilesReadyControlSet.find(tileData.tileInfo);
                if (indexControlSet == tilesReadyControlSet.end()) {
                    tilesReadyControlSet[tileData.tileInfo] = {legacyIndex};
                } else {
                    indexControlSet->second.insert(legacyIndex);
                }
                tilesReady.erase(tileData.tileInfo);

                actor.message(&Tiled2dMapVectorTile::setRasterTileData, tileData.textureHolder);
            }
        } else {
            for (auto &[index, identifier, tile]  : subTiles->second) {

                auto indexControlSet = tilesReadyControlSet.find(tileData.tileInfo);
                if (indexControlSet == tilesReadyControlSet.end()) {
                    tilesReadyControlSet[tileData.tileInfo] = {legacyIndex};
                } else {
                    indexControlSet->second.insert(legacyIndex);
                }
                tilesReady.erase(tileData.tileInfo);

                if (identifier == layerDescription->identifier) {
                    tile.message(&Tiled2dMapVectorTile::updateRasterLayerDescription, layerDescription, tileData.textureHolder);
                    break;
                }
            }
        }

    }
}
