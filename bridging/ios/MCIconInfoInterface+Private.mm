// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from icon.djinni

#import "MCIconInfoInterface+Private.h"
#import "MCIconInfoInterface.h"
#import "DJICppWrapperCache+Private.h"
#import "DJIError.h"
#import "DJIMarshal+Private.h"
#import "MCCoord+Private.h"
#import "MCIconType+Private.h"
#import "MCTextureHolderInterface+Private.h"
#import "MCVec2F+Private.h"
#include <exception>
#include <stdexcept>
#include <utility>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@interface MCIconInfoInterface ()

- (id)initWithCpp:(const std::shared_ptr<::IconInfoInterface>&)cppRef;

@end

@implementation MCIconInfoInterface {
    ::djinni::CppProxyCache::Handle<std::shared_ptr<::IconInfoInterface>> _cppRefHandle;
}

- (id)initWithCpp:(const std::shared_ptr<::IconInfoInterface>&)cppRef
{
    if (self = [super init]) {
        _cppRefHandle.assign(cppRef);
    }
    return self;
}

- (nonnull NSString *)getIdentifier {
    try {
        auto objcpp_result_ = _cppRefHandle.get()->getIdentifier();
        return ::djinni::String::fromCpp(objcpp_result_);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nullable id<MCTextureHolderInterface>)getTexture {
    try {
        auto objcpp_result_ = _cppRefHandle.get()->getTexture();
        return ::djinni_generated::TextureHolderInterface::fromCpp(objcpp_result_);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)setCoordinate:(nonnull MCCoord *)coord {
    try {
        _cppRefHandle.get()->setCoordinate(::djinni_generated::Coord::toCpp(coord));
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull MCCoord *)getCoordinate {
    try {
        auto objcpp_result_ = _cppRefHandle.get()->getCoordinate();
        return ::djinni_generated::Coord::fromCpp(objcpp_result_);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)setIconSize:(nonnull MCVec2F *)size {
    try {
        _cppRefHandle.get()->setIconSize(::djinni_generated::Vec2F::toCpp(size));
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull MCVec2F *)getIconSize {
    try {
        auto objcpp_result_ = _cppRefHandle.get()->getIconSize();
        return ::djinni_generated::Vec2F::fromCpp(objcpp_result_);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (void)setType:(MCIconType)scaleType {
    try {
        _cppRefHandle.get()->setType(::djinni::Enum<::IconType, MCIconType>::toCpp(scaleType));
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (MCIconType)getType {
    try {
        auto objcpp_result_ = _cppRefHandle.get()->getType();
        return ::djinni::Enum<::IconType, MCIconType>::fromCpp(objcpp_result_);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

- (nonnull MCVec2F *)getIconAnchor {
    try {
        auto objcpp_result_ = _cppRefHandle.get()->getIconAnchor();
        return ::djinni_generated::Vec2F::fromCpp(objcpp_result_);
    } DJINNI_TRANSLATE_EXCEPTIONS()
}

namespace djinni_generated {

auto IconInfoInterface::toCpp(ObjcType objc) -> CppType
{
    if (!objc) {
        return nullptr;
    }
    return objc->_cppRefHandle.get();
}

auto IconInfoInterface::fromCppOpt(const CppOptType& cpp) -> ObjcType
{
    if (!cpp) {
        return nil;
    }
    return ::djinni::get_cpp_proxy<MCIconInfoInterface>(cpp);
}

}  // namespace djinni_generated

@end
