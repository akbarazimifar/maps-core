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


#include <mutex>
#include <unordered_map>
#include "Tiled2dMapVectorSubLayerInterface.h"
#include "PolygonInfo.h"
#include "LineInfo.h"
#include "Polygon2dLayerObject.h"
#include "Line2dLayerObject.h"

class Tiled2dMapVectorSubLayer : public Tiled2dMapVectorSubLayerInterface, public std::enable_shared_from_this<Tiled2dMapVectorSubLayer> {
public:
    Tiled2dMapVectorSubLayer(const Color &fillColor);

    virtual void update() override;

    virtual std::vector<std::shared_ptr<::RenderPassInterface>> buildRenderPasses() override;

    void preGenerateRenderPasses();

    virtual void onAdded(const std::shared_ptr<MapInterface> & mapInterface) override;

    virtual void onRemoved() override;

    virtual void pause() override;

    virtual void resume() override;

    virtual void hide() override;

    virtual void show() override;

    virtual void updateTileData(const Tiled2dMapVectorTileInfo &tileInfo, vtzero::layer &data) override;

    virtual void clearTileData(const Tiled2dMapVectorTileInfo &tileInfo) override;

protected:
    void addPolygons(const Tiled2dMapVectorTileInfo &tileInfo, const std::vector<const PolygonInfo> &polygons);
    void addLines(const Tiled2dMapVectorTileInfo &tileInfo, const std::vector<const LineInfo> &lines);

private:
    std::shared_ptr<MapInterface> mapInterface;

    Color fillColor;

    std::recursive_mutex updateMutex;
    std::unordered_map<Tiled2dMapVectorTileInfo, std::vector<std::shared_ptr<Polygon2dLayerObject>>> tilePolygonMap;

    std::unordered_map<Tiled2dMapVectorTileInfo, std::vector<std::shared_ptr<Line2dLayerObject>>> tileLineMap;
    // TODO: add line and other graphic-primitives support

    std::vector<std::shared_ptr<::RenderPassInterface>> renderPasses;
};
