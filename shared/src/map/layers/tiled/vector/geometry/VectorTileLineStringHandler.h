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
#include "RectCoord.h"
#include "RectCoord.h"
#include "vtzero/geometry.hpp"

class VectorTileLineStringHandler {
public:
    VectorTileLineStringHandler(::RectCoord tileCoords, int extent) : tileCoords(tileCoords), extent((double) extent),
                                                                   tileWidth(tileCoords.bottomRight.x - tileCoords.topLeft.x),
                                                                   tileHeight(tileCoords.bottomRight.y - tileCoords.topLeft.y) {};



    void linestring_begin(uint32_t count) {
        coordinates.reserve(count);
    }

    void linestring_point(vtzero::point point) noexcept {
        double x = tileCoords.topLeft.x + tileWidth * (((double) point.x) / ((double) extent));
        double y = tileCoords.topLeft.y + tileHeight * (((double) point.y) / ((double) extent));
        Coord newCoord = Coord(tileCoords.topLeft.systemIdentifier, x, y, 0.0);
        coordinates.push_back(newCoord);
    }

    void linestring_end() const noexcept {}

    std::vector<::Coord> getCoordinates() {
        return std::move(coordinates);
    }


private:
    std::vector<::Coord> coordinates;

    RectCoord tileCoords;
    double tileWidth;
    double tileHeight;
    double extent;
};
