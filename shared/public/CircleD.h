// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from common.djinni

#pragma once

#include <utility>

struct CircleD final {
    double x;
    double y;
    double radius;

    CircleD(double x_,
            double y_,
            double radius_)
    : x(std::move(x_))
    , y(std::move(y_))
    , radius(std::move(radius_))
    {}
};
