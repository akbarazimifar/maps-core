// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from loader.djinni

#pragma once

#include "Vec2D.h"
#include <string>
#include <utility>

struct FontInfo final {
    std::string name;
    double ascender;
    double descender;
    double spaceAdvance;
    ::Vec2D bitmapSize;
    /** font size rendered in bitmap multiplied by dpFactor */
    double size;

    FontInfo(std::string name_,
             double ascender_,
             double descender_,
             double spaceAdvance_,
             ::Vec2D bitmapSize_,
             double size_)
    : name(std::move(name_))
    , ascender(std::move(ascender_))
    , descender(std::move(descender_))
    , spaceAdvance(std::move(spaceAdvance_))
    , bitmapSize(std::move(bitmapSize_))
    , size(std::move(size_))
    {}
};
