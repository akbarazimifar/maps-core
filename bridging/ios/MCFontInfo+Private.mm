// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from loader.djinni

#import "MCFontInfo+Private.h"
#import "DJIMarshal+Private.h"
#import "MCVec2D+Private.h"
#include <cassert>

namespace djinni_generated {

auto FontInfo::toCpp(ObjcType obj) -> CppType
{
    assert(obj);
    return {::djinni::String::toCpp(obj.name),
            ::djinni::F64::toCpp(obj.ascender),
            ::djinni::F64::toCpp(obj.descender),
            ::djinni::F64::toCpp(obj.spaceAdvance),
            ::djinni_generated::Vec2D::toCpp(obj.bitmapSize),
            ::djinni::F64::toCpp(obj.size)};
}

auto FontInfo::fromCpp(const CppType& cpp) -> ObjcType
{
    return [[MCFontInfo alloc] initWithName:(::djinni::String::fromCpp(cpp.name))
                                   ascender:(::djinni::F64::fromCpp(cpp.ascender))
                                  descender:(::djinni::F64::fromCpp(cpp.descender))
                               spaceAdvance:(::djinni::F64::fromCpp(cpp.spaceAdvance))
                                 bitmapSize:(::djinni_generated::Vec2D::fromCpp(cpp.bitmapSize))
                                       size:(::djinni::F64::fromCpp(cpp.size))];
}

}  // namespace djinni_generated
