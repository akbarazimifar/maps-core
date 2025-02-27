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

#include "Actor.h"
#include "Tiled2dMapSource.h"
#include "Tiled2dMapTileInfo.h"

class Tiled2dMapVectorReadyManager : public ActorObject  {
public:
    Tiled2dMapVectorReadyManager(const WeakActor<Tiled2dMapSourceReadyInterface> vectorSource);

    void registerManager();

    void didProcessData(const Tiled2dMapTileInfo &tile, const size_t notReadyCount);

    void setReady(const Tiled2dMapTileInfo &tile, const size_t readyCount);

    void remove(const std::unordered_set<Tiled2dMapTileInfo> &tilesToRemove);

private:
    const WeakActor<Tiled2dMapSourceReadyInterface> vectorSource;

    std::unordered_map<Tiled2dMapTileInfo, size_t> tileNotReadyCount;

    std::unordered_map<Tiled2dMapTileInfo, size_t> tileDataProcessCount;

    size_t managerCount = 0;
};
