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

#include "Coord.h"
#include "CoordinateConversionHelperInterface.h"
#include "LambdaTask.h"
#include "MapConfig.h"
#include "PrioritizedTiled2dMapTileInfo.h"
#include "SchedulerInterface.h"
#include "Tiled2dMapLayerConfig.h"
#include "Tiled2dMapSourceInterface.h"
#include "Tiled2dMapZoomInfo.h"
#include "Tiled2dMapZoomLevelInfo.h"
#include "QuadCoord.h"
#include "PolygonCoord.h"
#include "CoordinateSystemIdentifiers.h"
#include <atomic>
#include <cmath>
#include <mutex>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "gpc.h"
#include "Actor.h"
#include "Future.hpp"
#include "LoaderStatus.h"
#include "TileState.h"

template<class R>
struct TileWrapper {
public:
    const R result;
    std::vector<::PolygonCoord> masks;
    const PolygonCoord tileBounds;
    gpc_polygon tilePolygon;
    TileState state = TileState::IN_SETUP;

    TileWrapper(const R &result,
                const std::vector<::PolygonCoord> & masks,
                const PolygonCoord & tileBounds,
                const gpc_polygon &tilePolygon) :
    result(std::move(result)),
    masks(std::move(masks)),
    tileBounds(std::move(tileBounds)),
    tilePolygon(std::move(tilePolygon)) {};
};


class Tiled2dMapSourceReadyInterface {
public:
    virtual ~Tiled2dMapSourceReadyInterface() = default;

    virtual void setTileReady(const Tiled2dMapTileInfo &tile) = 0;
};


// T is the Object used for loading
// L is the Loading type
// R is the Result type
template<class T, class L, class R>
class Tiled2dMapSource :
        public Tiled2dMapSourceInterface,
        public Tiled2dMapSourceReadyInterface,
        public std::enable_shared_from_this<Tiled2dMapSourceInterface>,
        public ActorObject {
public:
    Tiled2dMapSource(const MapConfig &mapConfig, const std::shared_ptr<Tiled2dMapLayerConfig> &layerConfig,
                     const std::shared_ptr<CoordinateConversionHelperInterface> &conversionHelper,
                     const std::shared_ptr<SchedulerInterface> &scheduler,
                     float screenDensityPpi,
                     size_t loaderCount);

    virtual void onVisibleBoundsChanged(const ::RectCoord &visibleBounds, int curT, double zoom) override;

    virtual bool isTileVisible(const Tiled2dMapTileInfo &tileInfo);

    virtual void pause() override;

    virtual void resume() override;

    virtual RectCoord getCurrentViewBounds();

    void setMinZoomLevelIdentifier(std::optional<int32_t> value) override;

    void setMaxZoomLevelIdentifier(std::optional<int32_t> value) override;

    std::optional<int32_t> getMinZoomLevelIdentifier() override;

    std::optional<int32_t> getMaxZoomLevelIdentifier() override;

    virtual ::LayerReadyState isReadyToRenderOffscreen() override;

    virtual void setErrorManager(const std::shared_ptr<::ErrorManager> &errorManager) override;

    virtual void forceReload() override;

    void setTileReady(const Tiled2dMapTileInfo &tile) override;

    void setTilesReady(const std::vector<Tiled2dMapTileInfo> &tiles);
            
    virtual void cancelLoad(Tiled2dMapTileInfo tile, size_t loaderIndex) = 0;
            
    virtual ::djinni::Future<L> loadDataAsync(Tiled2dMapTileInfo tile, size_t loaderIndex) = 0;
            
    void didLoad(Tiled2dMapTileInfo tile, size_t loaderIndex, const R &result);

    void didFailToLoad(Tiled2dMapTileInfo tile, size_t loaderIndex, const LoaderStatus &status, const std::optional<std::string> &errorCode);

    void performDelayedTasks();

  protected:
    virtual bool hasExpensivePostLoadingTask() = 0;

    virtual R postLoadingTask(const L &loadedData, const Tiled2dMapTileInfo &tile) = 0;

    MapConfig mapConfig;
    std::shared_ptr<Tiled2dMapLayerConfig> layerConfig;
    int32_t layerSystemId;
    std::shared_ptr<CoordinateConversionHelperInterface> conversionHelper;
    std::weak_ptr<SchedulerInterface> scheduler;
    std::shared_ptr<::ErrorManager> errorManager;

    std::vector<Tiled2dMapZoomLevelInfo> zoomLevelInfos;
    const Tiled2dMapZoomInfo zoomInfo;

    std::optional<int32_t> minZoomLevelIdentifier;
    std::optional<int32_t> maxZoomLevelIdentifier;

    std::map<Tiled2dMapTileInfo, TileWrapper<R>> currentTiles;

    int currentZoomLevelIdentifier = 0;

    std::unordered_set<Tiled2dMapTileInfo> currentVisibleTiles;

    std::vector<VisibleTilesLayer> currentPyramid;

    RectCoord currentViewBounds = RectCoord(Coord(CoordinateSystemIdentifiers::RENDERSYSTEM(), 0.0, 0.0, 0.0),
                                            Coord(CoordinateSystemIdentifiers::RENDERSYSTEM(), 0.0, 0.0, 0.0));


    std::atomic<bool> isPaused;

    float screenDensityPpi;
    std::set<Tiled2dMapTileInfo> readyTiles;

private:
    void performLoadingTask(Tiled2dMapTileInfo tile, size_t loaderIndex);

    void onVisibleTilesChanged(const std::vector<VisibleTilesLayer> &pyramid);

    void updateTileMasks();

    std::unordered_map<Tiled2dMapTileInfo, int> currentlyLoading;

    const long long MAX_WAIT_TIME = 32000;
    const long long MIN_WAIT_TIME = 1000;

    struct ErrorInfo {
        long long lastLoad;
        long long delay;
    };

    std::unordered_map<size_t, std::map<Tiled2dMapTileInfo, ErrorInfo>> errorTiles;
    std::optional<long long> nextDelayTaskExecution;

    std::unordered_set<Tiled2dMapTileInfo> notFoundTiles;
};

#include "Tiled2dMapSourceImpl.h"
