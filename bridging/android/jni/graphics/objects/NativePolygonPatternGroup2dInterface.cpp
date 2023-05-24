// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from graphicsobjects.djinni

#include "NativePolygonPatternGroup2dInterface.h"  // my header
#include "Marshal.hpp"
#include "NativeGraphicsObjectInterface.h"
#include "NativeRenderingContextInterface.h"
#include "NativeSharedBytes.h"
#include "NativeTextureHolderInterface.h"

namespace djinni_generated {

NativePolygonPatternGroup2dInterface::NativePolygonPatternGroup2dInterface() : ::djinni::JniInterface<::PolygonPatternGroup2dInterface, NativePolygonPatternGroup2dInterface>("io/openmobilemaps/mapscore/shared/graphics/objects/PolygonPatternGroup2dInterface$CppProxy") {}

NativePolygonPatternGroup2dInterface::~NativePolygonPatternGroup2dInterface() = default;

NativePolygonPatternGroup2dInterface::JavaProxy::JavaProxy(JniType j) : Handle(::djinni::jniGetThreadEnv(), j) { }

NativePolygonPatternGroup2dInterface::JavaProxy::~JavaProxy() = default;

void NativePolygonPatternGroup2dInterface::JavaProxy::setVertices(const ::SharedBytes & c_vertices, const ::SharedBytes & c_indices) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativePolygonPatternGroup2dInterface>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setVertices,
                           ::djinni::get(::djinni_generated::NativeSharedBytes::fromCpp(jniEnv, c_vertices)),
                           ::djinni::get(::djinni_generated::NativeSharedBytes::fromCpp(jniEnv, c_indices)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativePolygonPatternGroup2dInterface::JavaProxy::setOpacities(const ::SharedBytes & c_values) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativePolygonPatternGroup2dInterface>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setOpacities,
                           ::djinni::get(::djinni_generated::NativeSharedBytes::fromCpp(jniEnv, c_values)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativePolygonPatternGroup2dInterface::JavaProxy::setTextureCoordinates(const ::SharedBytes & c_values) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativePolygonPatternGroup2dInterface>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setTextureCoordinates,
                           ::djinni::get(::djinni_generated::NativeSharedBytes::fromCpp(jniEnv, c_values)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativePolygonPatternGroup2dInterface::JavaProxy::setScalingFactor(float c_factor) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativePolygonPatternGroup2dInterface>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_setScalingFactor,
                           ::djinni::get(::djinni::F32::fromCpp(jniEnv, c_factor)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativePolygonPatternGroup2dInterface::JavaProxy::loadTexture(const /*not-null*/ std::shared_ptr<::RenderingContextInterface> & c_context, const /*not-null*/ std::shared_ptr<::TextureHolderInterface> & c_textureHolder) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativePolygonPatternGroup2dInterface>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_loadTexture,
                           ::djinni::get(::djinni_generated::NativeRenderingContextInterface::fromCpp(jniEnv, c_context)),
                           ::djinni::get(::djinni_generated::NativeTextureHolderInterface::fromCpp(jniEnv, c_textureHolder)));
    ::djinni::jniExceptionCheck(jniEnv);
}
void NativePolygonPatternGroup2dInterface::JavaProxy::removeTexture() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativePolygonPatternGroup2dInterface>::get();
    jniEnv->CallVoidMethod(Handle::get().get(), data.method_removeTexture);
    ::djinni::jniExceptionCheck(jniEnv);
}
/*not-null*/ std::shared_ptr<::GraphicsObjectInterface> NativePolygonPatternGroup2dInterface::JavaProxy::asGraphicsObject() {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativePolygonPatternGroup2dInterface>::get();
    auto jret = jniEnv->CallObjectMethod(Handle::get().get(), data.method_asGraphicsObject);
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni_generated::NativeGraphicsObjectInterface::toCpp(jniEnv, jret);
}

CJNIEXPORT void JNICALL Java_io_openmobilemaps_mapscore_shared_graphics_objects_PolygonPatternGroup2dInterface_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        delete reinterpret_cast<::djinni::CppProxyHandle<::PolygonPatternGroup2dInterface>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_io_openmobilemaps_mapscore_shared_graphics_objects_PolygonPatternGroup2dInterface_00024CppProxy_native_1setVertices(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, ::djinni_generated::NativeSharedBytes::JniType j_vertices, ::djinni_generated::NativeSharedBytes::JniType j_indices)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::PolygonPatternGroup2dInterface>(nativeRef);
        ref->setVertices(::djinni_generated::NativeSharedBytes::toCpp(jniEnv, j_vertices),
                         ::djinni_generated::NativeSharedBytes::toCpp(jniEnv, j_indices));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_io_openmobilemaps_mapscore_shared_graphics_objects_PolygonPatternGroup2dInterface_00024CppProxy_native_1setOpacities(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, ::djinni_generated::NativeSharedBytes::JniType j_values)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::PolygonPatternGroup2dInterface>(nativeRef);
        ref->setOpacities(::djinni_generated::NativeSharedBytes::toCpp(jniEnv, j_values));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_io_openmobilemaps_mapscore_shared_graphics_objects_PolygonPatternGroup2dInterface_00024CppProxy_native_1setTextureCoordinates(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, ::djinni_generated::NativeSharedBytes::JniType j_values)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::PolygonPatternGroup2dInterface>(nativeRef);
        ref->setTextureCoordinates(::djinni_generated::NativeSharedBytes::toCpp(jniEnv, j_values));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_io_openmobilemaps_mapscore_shared_graphics_objects_PolygonPatternGroup2dInterface_00024CppProxy_native_1setScalingFactor(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jfloat j_factor)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::PolygonPatternGroup2dInterface>(nativeRef);
        ref->setScalingFactor(::djinni::F32::toCpp(jniEnv, j_factor));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_io_openmobilemaps_mapscore_shared_graphics_objects_PolygonPatternGroup2dInterface_00024CppProxy_native_1loadTexture(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, ::djinni_generated::NativeRenderingContextInterface::JniType j_context, jobject j_textureHolder)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::PolygonPatternGroup2dInterface>(nativeRef);
        ref->loadTexture(::djinni_generated::NativeRenderingContextInterface::toCpp(jniEnv, j_context),
                         ::djinni_generated::NativeTextureHolderInterface::toCpp(jniEnv, j_textureHolder));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_io_openmobilemaps_mapscore_shared_graphics_objects_PolygonPatternGroup2dInterface_00024CppProxy_native_1removeTexture(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::PolygonPatternGroup2dInterface>(nativeRef);
        ref->removeTexture();
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_io_openmobilemaps_mapscore_shared_graphics_objects_PolygonPatternGroup2dInterface_00024CppProxy_native_1asGraphicsObject(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::PolygonPatternGroup2dInterface>(nativeRef);
        auto r = ref->asGraphicsObject();
        return ::djinni::release(::djinni_generated::NativeGraphicsObjectInterface::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

} // namespace djinni_generated
