#pragma once

#include "LayerInterface.h"
#include <vtzero/vector_tile.hpp>
#include "Tiled2dMapVectorTileInfo.h"

class Tiled2dMapVectorSubLayerInterface: public LayerInterface {
public:
    virtual ~Tiled2dMapVectorSubLayerInterface() {}

    virtual void updateTileData(const Tiled2dMapVectorTileInfo &tileInfo, vtzero::layer &data) = 0;

    virtual void clearTileData(const Tiled2dMapVectorTileInfo &tileInfo) = 0;
};

