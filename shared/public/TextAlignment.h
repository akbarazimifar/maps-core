// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from text.djinni

#pragma once

#include <functional>

enum class TextAlignment : int {
    CENTER,
    BOTTOM_LEFT,
};

namespace std {

template <>
struct hash<::TextAlignment> {
    size_t operator()(::TextAlignment type) const {
        return std::hash<int>()(static_cast<int>(type));
    }
};

}  // namespace std
