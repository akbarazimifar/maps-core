// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from line.djinni

#pragma once

#include <functional>

enum class LineCapType : int {
    BUTT,
    ROUND,
    SQUARE,
};

namespace std {

template <>
struct hash<::LineCapType> {
    size_t operator()(::LineCapType type) const {
        return std::hash<int>()(static_cast<int>(type));
    }
};

}  // namespace std
