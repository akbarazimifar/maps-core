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

#include "MapConfig.h"
#include "LoaderInterface.h"
#include "TextureLoaderResult.h"
#include "Tiled2dMapRasterTileInfo.h"
#include "Tiled2dMapSource.h"

class Tiled2dMapRasterSource : public Tiled2dMapSource<TextureHolderInterface, TextureLoaderResult, std::shared_ptr<::TextureHolderInterface>> {
  public:
    Tiled2dMapRasterSource(const MapConfig &mapConfig, const std::shared_ptr<Tiled2dMapLayerConfig> &layerConfig,
                           const std::shared_ptr<CoordinateConversionHelperInterface> &conversionHelper,
                           const std::shared_ptr<SchedulerInterface> &scheduler,
                           const std::shared_ptr<::LoaderInterface> & textureLoader,
                           const std::shared_ptr<Tiled2dMapSourceListenerInterface> &listener,
                           float screenDensityPpi);

    std::unordered_set<Tiled2dMapRasterTileInfo> getCurrentTiles();

  protected:
    virtual TextureLoaderResult loadTile(Tiled2dMapTileInfo tile) override;

    virtual std::shared_ptr<::TextureHolderInterface> postLoadingTask(const TextureLoaderResult &loadedData, const Tiled2dMapTileInfo &tile) override;

  private:
    const std::shared_ptr<LoaderInterface> loader;
};
