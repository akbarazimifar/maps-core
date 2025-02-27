/*
 * Copyright (c) 2021 Ubique Innovation AG <https://www.ubique.ch>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 *  SPDX-License-Identifier: MPL-2.0
 */

#include "Tiled2dMapVectorSourceVectorTileDataManager.h"
#include "PolygonCompare.h"
#include "Tiled2dMapVectorLayer.h"

Tiled2dMapVectorSourceVectorTileDataManager::Tiled2dMapVectorSourceVectorTileDataManager(
                                                                                         const WeakActor<Tiled2dMapVectorLayer> &vectorLayer,
                                                                                         const std::shared_ptr<VectorMapDescription> &mapDescription,
                                                                                         const std::shared_ptr<Tiled2dMapVectorLayerConfig> &layerConfig,
                                                                                         const std::string &source,
                                                                                         const WeakActor<Tiled2dMapVectorSource> &vectorSource,
                                                                                         const Actor<Tiled2dMapVectorReadyManager> &readyManager,
                                                                                         const std::shared_ptr<Tiled2dMapVectorFeatureStateManager> &featureStateManager)
: Tiled2dMapVectorSourceTileDataManager(vectorLayer, mapDescription, layerConfig, source, readyManager, featureStateManager),
vectorSource(vectorSource) {
    readyManager.message(&Tiled2dMapVectorReadyManager::registerManager);
}

void Tiled2dMapVectorSourceVectorTileDataManager::onVectorTilesUpdated(const std::string &sourceName,
                                                                       std::unordered_set<Tiled2dMapVectorTileInfo> currentTileInfos) {
    auto mapInterface = this->mapInterface.lock();
    {
        auto graphicsFactory = mapInterface ? mapInterface->getGraphicsObjectFactory() : nullptr;
        auto coordinateConverterHelper = mapInterface ? mapInterface->getCoordinateConverterHelper() : nullptr;
        auto shaderFactory = mapInterface ? mapInterface->getShaderFactory() : nullptr;
        if (!graphicsFactory || !shaderFactory) {
            return;
        }

        // Just insert pointers here since we will only access the objects inside this method where we know that currentTileInfos is retained
        std::vector<const Tiled2dMapVectorTileInfo*> tilesToAdd;
        std::vector<const Tiled2dMapVectorTileInfo*> tilesToKeep;

        std::unordered_set<Tiled2dMapTileInfo> tilesToRemove;

        std::unordered_map<Tiled2dMapTileInfo, TileState> tileStateUpdates;

        for (const auto &vectorTileInfo: currentTileInfos) {
            if (tiles.count(vectorTileInfo.tileInfo) == 0) {
                tilesToAdd.push_back(&vectorTileInfo);
            } else {
                tilesToKeep.push_back(&vectorTileInfo);
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

            auto tileStateIt = tileStateMap.find(tileEntry->tileInfo);
            if (tileStateIt == tileStateMap.end() || tileStateIt->second != tileEntry->state) {
                tileStateUpdates[tileEntry->tileInfo] = tileEntry->state;
            }

            size_t existingPolygonHash = 0;
            auto it = tileMaskMap.find(tileEntry->tileInfo);
            if (it != tileMaskMap.end()) {
                existingPolygonHash = it->second.getPolygonHash();
            }

            const size_t hash = std::hash<std::vector<::PolygonCoord>>()(tileEntry->masks);

            if (hash != existingPolygonHash) {

                const auto &tileMask = std::make_shared<PolygonMaskObject>(graphicsFactory,
                                                                           coordinateConverterHelper);

                tileMask->setPolygons(tileEntry->masks);

                newTileMasks[tileEntry->tileInfo] = Tiled2dMapLayerMaskWrapper(tileMask, hash);
            }
        }

        if (tilesToAdd.empty() && tilesToRemove.empty() && newTileMasks.empty() && tileStateUpdates.empty()) return;

        for (const auto &tile : tilesToAdd) {

            std::unordered_set<int32_t> indexControlSet;

            tiles[tile->tileInfo] = {};
            assert(tileStateMap.count(tile->tileInfo) == 0);
            tileStateUpdates[tile->tileInfo] = tile->state;

            for (int32_t index = 0; index < mapDescription->layers.size(); index++) {
                auto const &layer= mapDescription->layers.at(index);
                if (layer->source != sourceName) {
                    continue;
                }
                auto const mapIt = tile->layerFeatureMaps->find(layer->sourceLayer);
                if (mapIt == tile->layerFeatureMaps->end()) {
                    continue;
                }

                std::string identifier = layer->identifier;
                Actor<Tiled2dMapVectorTile> actor = createTileActor(tile->tileInfo, layer);

                if (actor) {
                    if (auto strongSelectionDelegate = selectionDelegate.lock()) {
                        actor.message(&Tiled2dMapVectorTile::setSelectionDelegate, strongSelectionDelegate);
                    }

                    indexControlSet.insert(index);
                    tiles[tile->tileInfo].push_back({index, identifier, actor.strongActor<Tiled2dMapVectorTile>()});

                    actor.message(&Tiled2dMapVectorTile::setVectorTileData, mapIt->second);
                }
            }

            if (!indexControlSet.empty()) {
                tilesReadyControlSet[tile->tileInfo] = indexControlSet;
            }
            
            readyManager.message(&Tiled2dMapVectorReadyManager::didProcessData, tile->tileInfo, indexControlSet.empty() ? 0 : 1);
        }

        if (!(newTileMasks.empty() && tilesToRemove.empty() && tileStateUpdates.empty())) {
            auto castedMe = std::static_pointer_cast<Tiled2dMapVectorSourceTileDataManager>(shared_from_this());
            auto selfActor = WeakActor<Tiled2dMapVectorSourceTileDataManager>(mailbox, castedMe);
            selfActor.messagePrecisely(MailboxDuplicationStrategy::replaceNewest, MailboxExecutionEnvironment::graphics, &Tiled2dMapVectorSourceTileDataManager::updateMaskObjects, newTileMasks, tilesToRemove, tileStateUpdates);
        }
    }
    mapInterface->invalidate();
}


void Tiled2dMapVectorSourceVectorTileDataManager::onTileCompletelyReady(const Tiled2dMapTileInfo tileInfo) {
    readyManager.message(&Tiled2dMapVectorReadyManager::setReady, tileInfo, 1);
}

void Tiled2dMapVectorSourceVectorTileDataManager::updateLayerDescription(std::shared_ptr<VectorLayerDescription> layerDescription,
                                                                   int32_t legacyIndex,
                                                                   bool needsTileReplace) {
    auto mapInterface = this->mapInterface.lock();
    if (!mapInterface) {
        return;
    }

    auto const &currentTileInfos = vectorSource.converse(&Tiled2dMapVectorSource::getCurrentTiles).get();

    for (const auto &tileData: currentTileInfos) {
        auto subTiles = tiles.find(tileData.tileInfo);
        if (subTiles == tiles.end()) {
            continue;
        }

        if (needsTileReplace) {
            std::vector<Actor<Tiled2dMapVectorTile>> tilesToClear;
            // Remove invalid legacy tile (only one - identifier is unique)
            auto legacyPos = std::find_if(subTiles->second.begin(), subTiles->second.end(),
                                          [&identifier = layerDescription->identifier]
                                                  (const std::tuple<int32_t, std::string, Actor<Tiled2dMapVectorTile>> &subTile) {
                                              return std::get<1>(subTile) == identifier;
                                          });
            if (legacyPos == subTiles->second.end()) {
                continue;
            }
            tilesToClear.push_back(std::get<2>(*legacyPos));
            subTiles->second.erase(legacyPos);

            // If new source of layer is not handled by this manager, continue
            if (layerDescription->source != source) {
                continue;
            }

            auto const mapIt = tileData.layerFeatureMaps->find(layerDescription->sourceLayer);
            if (mapIt == tileData.layerFeatureMaps->end()) {
                continue;
            }

            Actor<Tiled2dMapVectorTile> actor = createTileActor(tileData.tileInfo, layerDescription);
            if (actor) {
                if (auto strongSelectionDelegate = selectionDelegate.lock()) {
                    actor.message(&Tiled2dMapVectorTile::setSelectionDelegate, strongSelectionDelegate);
                }

                if (subTiles->second.empty()) {
                    subTiles->second.push_back({legacyIndex, layerDescription->identifier, actor.strongActor<Tiled2dMapVectorTile>()});
                } else {
                    auto insertionPoint = std::lower_bound(subTiles->second.begin(), subTiles->second.end(), legacyIndex, [](const auto& subTile, int index) {
                        return std::get<0>(subTile) < index;
                    });

                    subTiles->second.insert(insertionPoint, {legacyIndex, layerDescription->identifier, actor.strongActor<Tiled2dMapVectorTile>()});
                }

                auto controlSetEntry = tilesReadyControlSet.find(tileData.tileInfo);
                if (controlSetEntry == tilesReadyControlSet.end()) {
                    tilesReadyControlSet[tileData.tileInfo] = {legacyIndex};
                } else {
                    controlSetEntry->second.insert(legacyIndex);
                }
                tilesReady.erase(tileData.tileInfo);

                actor.message(&Tiled2dMapVectorTile::setVectorTileData, mapIt->second);
                auto castedMe = std::static_pointer_cast<Tiled2dMapVectorSourceVectorTileDataManager>(shared_from_this());
                auto selfActor = WeakActor<Tiled2dMapVectorSourceVectorTileDataManager>(mailbox, castedMe);
                selfActor.message(MailboxExecutionEnvironment::graphics, &Tiled2dMapVectorSourceVectorTileDataManager::clearTiles, tilesToClear);
            }

        } else {
            for (auto &[index, identifier, tile]  : subTiles->second) {
                if (identifier == layerDescription->identifier) {
                    auto const mapIt = tileData.layerFeatureMaps->find(layerDescription->sourceLayer);
                    if (mapIt == tileData.layerFeatureMaps->end()) {
                        break;
                    }

                    auto controlSetEntry = tilesReadyControlSet.find(tileData.tileInfo);
                    if (controlSetEntry == tilesReadyControlSet.end()) {
                        tilesReadyControlSet[tileData.tileInfo] = {legacyIndex};
                    } else {
                        controlSetEntry->second.insert(legacyIndex);
                    }
                    tilesReady.erase(tileData.tileInfo);

                    tile.message(&Tiled2dMapVectorTile::updateVectorLayerDescription, layerDescription, mapIt->second);
                    break;
                }
            }
        }
    }
}

void Tiled2dMapVectorSourceVectorTileDataManager::clearTiles(const std::vector<Actor<Tiled2dMapVectorTile>> &tilesToClear) {
    for (const auto &tile: tilesToClear) {
        tile.syncAccess([&](auto tileActor){
            tileActor->clear();
        });
    }
}
