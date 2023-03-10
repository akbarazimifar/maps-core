/*
 * Copyright (c) 2021 Ubique Innovation AG <https://www.ubique.ch>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 *  SPDX-License-Identifier: MPL-2.0
 */

#pragma once

#include "Tiled2dMapVectorTile.h"
#include "MapInterface.h"
#include "PolygonVectorLayerDescription.h"
#include "PolygonGroup2dLayerObject.h"
#include "PolygonCoord.h"

class Tiled2dMapVectorPolygonTile
        : public Tiled2dMapVectorTile,
          public std::enable_shared_from_this<Tiled2dMapVectorPolygonTile> {
public:
    Tiled2dMapVectorPolygonTile(const std::weak_ptr<MapInterface> &mapInterface,
                                const Tiled2dMapTileInfo &tileInfo,
                                const WeakActor<Tiled2dMapVectorLayer> &vectorLayer,
                                const std::shared_ptr<PolygonVectorLayerDescription> &description);

    void updateLayerDescription(const std::shared_ptr<VectorLayerDescription> &description,
                                const Tiled2dMapVectorTileDataVariant &layerFeatures) override;

    void update() override;

    virtual std::vector<std::shared_ptr<RenderPassInterface>> buildRenderPasses() override;

    virtual void clear() override;

    virtual void setup() override;

    virtual void setScissorRect(const std::optional<::RectI> &scissorRect) override;

    virtual void setTileData(const std::shared_ptr<MaskingObjectInterface> &tileMask,
                             const Tiled2dMapVectorTileDataVariant &tileData) override;

    virtual void updateTileMask(const std::shared_ptr<MaskingObjectInterface> &tileMask) override;

    bool onClickConfirmed(const Vec2F &posScreen) override;

protected:
    virtual void preGenerateRenderPasses();

private:
    void addPolygons(const std::vector<std::tuple<std::vector<std::tuple<std::vector<Coord>, int>>, std::vector<int32_t>>> &polygons);

    void setupPolygons(const std::vector<std::shared_ptr<GraphicsObjectInterface>> &newPolygonObjects,
                       const std::vector<std::shared_ptr<GraphicsObjectInterface>> &oldPolygonObjects);


    std::shared_ptr<PolygonGroupShaderInterface> shader;

    std::vector<std::shared_ptr<PolygonGroup2dLayerObject>> polygons;
    std::vector<std::tuple<size_t, FeatureContext>> featureGroups;
    std::unordered_set<std::string> usedKeys;

    std::unordered_map<Tiled2dMapTileInfo, std::vector<std::tuple<PolygonCoord, FeatureContext>>> hitDetectionPolygonMap;

    std::shared_ptr<MaskingObjectInterface> tileMask;
    std::optional<::RectI> scissorRect = std::nullopt;
    std::vector<std::shared_ptr<RenderPassInterface>> renderPasses;
};
