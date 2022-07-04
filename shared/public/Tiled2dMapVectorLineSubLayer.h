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

#include "Tiled2dMapVectorSubLayer.h"
#include "LineVectorLayerDescription.h"
#include "LineGroup2dLayerObject.h"
#include "Line2dLayerObject.h"
#include "LineInfo.h"
#include "LineGroupShaderInterface.h"


class Tiled2dMapVectorLineSubLayer : public Tiled2dMapVectorSubLayer,
                                     public std::enable_shared_from_this<Tiled2dMapVectorLineSubLayer> {
public:
    Tiled2dMapVectorLineSubLayer(const std::shared_ptr<LineVectorLayerDescription> &description);

    ~Tiled2dMapVectorLineSubLayer() {}

    virtual void update() override;

    virtual void onAdded(const std::shared_ptr<MapInterface> &mapInterface) override;

    virtual void onRemoved() override;

    virtual void pause() override;

    virtual void resume() override;

    virtual void hide() override;

    virtual void show() override;

    virtual void updateTileData(const Tiled2dMapTileInfo &tileInfo, const std::shared_ptr<MaskingObjectInterface> &tileMask,
                                const std::vector<std::tuple<const FeatureContext, const VectorTileGeometryHandler>> &layerFeatures) override;

    void updateTileMask(const Tiled2dMapTileInfo &tileInfo, const std::shared_ptr <MaskingObjectInterface> &tileMask) override;

    virtual void clearTileData(const Tiled2dMapTileInfo &tileInfo) override;

protected:
    void addLines(const Tiled2dMapTileInfo &tileInfo, const std::vector<std::vector<std::tuple<std::vector<Coord>, int>>> &lines);

    void setupLines(const Tiled2dMapTileInfo &tileInfo, const std::vector<std::shared_ptr<GraphicsObjectInterface>> &newLineGraphicsObjects);

    void preGenerateRenderPasses();

private:
    static const int maxNumLinePoints = std::numeric_limits<uint16_t>::max() / 4 + 1; // 4 vertices per line coord, only 2 at the start/end

    std::shared_ptr<LineVectorLayerDescription> description;

    std::shared_ptr<LineGroupShaderInterface> shader;

    std::recursive_mutex lineMutex;
    std::unordered_map<Tiled2dMapTileInfo, std::vector<std::shared_ptr<LineGroup2dLayerObject>>> tileLinesMap;

    std::recursive_mutex featureGroupsMutex;
    std::vector<FeatureContext> featureGroups;
};

