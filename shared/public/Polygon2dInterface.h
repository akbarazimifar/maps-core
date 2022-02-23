// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from graphicsobjects.djinni

#pragma once

#include "Vec2D.h"
#include <cstdint>
#include <memory>
#include <vector>

class GraphicsObjectInterface;
class MaskingObjectInterface;

class Polygon2dInterface {
public:
    virtual ~Polygon2dInterface() {}

    virtual void setVertices(const std::vector<::Vec2D> & vertices, const std::vector<int32_t> & indices) = 0;

    virtual std::shared_ptr<GraphicsObjectInterface> asGraphicsObject() = 0;

    virtual std::shared_ptr<MaskingObjectInterface> asMaskingObject() = 0;
};
