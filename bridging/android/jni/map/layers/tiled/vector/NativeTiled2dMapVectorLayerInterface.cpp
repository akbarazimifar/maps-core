// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from tiled_vector_layer.djinni

#include "NativeTiled2dMapVectorLayerInterface.h"  // my header
#include "Marshal.hpp"
#include "NativeFontLoaderInterface.h"
#include "NativeLayerInterface.h"
#include "NativeLoaderInterface.h"
#include "NativeTiled2dMapVectorLayerSelectionCallbackInterface.h"
#include "NativeTiled2dMapZoomInfo.h"
#include "NativeVectorLayerFeatureInfoValue.h"

namespace djinni_generated {

NativeTiled2dMapVectorLayerInterface::NativeTiled2dMapVectorLayerInterface() : ::djinni::JniInterface<::Tiled2dMapVectorLayerInterface, NativeTiled2dMapVectorLayerInterface>("io/openmobilemaps/mapscore/shared/map/layers/tiled/vector/Tiled2dMapVectorLayerInterface$CppProxy") {}

NativeTiled2dMapVectorLayerInterface::~NativeTiled2dMapVectorLayerInterface() = default;


CJNIEXPORT void JNICALL Java_io_openmobilemaps_mapscore_shared_map_layers_tiled_vector_Tiled2dMapVectorLayerInterface_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        delete reinterpret_cast<::djinni::CppProxyHandle<::Tiled2dMapVectorLayerInterface>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_io_openmobilemaps_mapscore_shared_map_layers_tiled_vector_Tiled2dMapVectorLayerInterface_createFromStyleJson(JNIEnv* jniEnv, jobject /*this*/, jstring j_layerName, jstring j_path, jobject j_loaders, ::djinni_generated::NativeFontLoaderInterface::JniType j_fontLoader, jdouble j_dpFactor)
{
    try {
        auto r = ::Tiled2dMapVectorLayerInterface::createFromStyleJson(::djinni::String::toCpp(jniEnv, j_layerName),
                                                                       ::djinni::String::toCpp(jniEnv, j_path),
                                                                       ::djinni::List<::djinni_generated::NativeLoaderInterface>::toCpp(jniEnv, j_loaders),
                                                                       ::djinni_generated::NativeFontLoaderInterface::toCpp(jniEnv, j_fontLoader),
                                                                       ::djinni::F64::toCpp(jniEnv, j_dpFactor));
        return ::djinni::release(::djinni_generated::NativeTiled2dMapVectorLayerInterface::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jobject JNICALL Java_io_openmobilemaps_mapscore_shared_map_layers_tiled_vector_Tiled2dMapVectorLayerInterface_createFromStyleJsonWithZoomInfo(JNIEnv* jniEnv, jobject /*this*/, jstring j_layerName, jstring j_path, jobject j_loaders, ::djinni_generated::NativeFontLoaderInterface::JniType j_fontLoader, jdouble j_dpFactor, ::djinni_generated::NativeTiled2dMapZoomInfo::JniType j_zoomInfo)
{
    try {
        auto r = ::Tiled2dMapVectorLayerInterface::createFromStyleJsonWithZoomInfo(::djinni::String::toCpp(jniEnv, j_layerName),
                                                                                   ::djinni::String::toCpp(jniEnv, j_path),
                                                                                   ::djinni::List<::djinni_generated::NativeLoaderInterface>::toCpp(jniEnv, j_loaders),
                                                                                   ::djinni_generated::NativeFontLoaderInterface::toCpp(jniEnv, j_fontLoader),
                                                                                   ::djinni::F64::toCpp(jniEnv, j_dpFactor),
                                                                                   ::djinni_generated::NativeTiled2dMapZoomInfo::toCpp(jniEnv, j_zoomInfo));
        return ::djinni::release(::djinni_generated::NativeTiled2dMapVectorLayerInterface::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jobject JNICALL Java_io_openmobilemaps_mapscore_shared_map_layers_tiled_vector_Tiled2dMapVectorLayerInterface_createFromLocalStyleJson(JNIEnv* jniEnv, jobject /*this*/, jstring j_layerName, jstring j_styleJson, jobject j_loaders, ::djinni_generated::NativeFontLoaderInterface::JniType j_fontLoader, jdouble j_dpFactor)
{
    try {
        auto r = ::Tiled2dMapVectorLayerInterface::createFromLocalStyleJson(::djinni::String::toCpp(jniEnv, j_layerName),
                                                                            ::djinni::String::toCpp(jniEnv, j_styleJson),
                                                                            ::djinni::List<::djinni_generated::NativeLoaderInterface>::toCpp(jniEnv, j_loaders),
                                                                            ::djinni_generated::NativeFontLoaderInterface::toCpp(jniEnv, j_fontLoader),
                                                                            ::djinni::F64::toCpp(jniEnv, j_dpFactor));
        return ::djinni::release(::djinni_generated::NativeTiled2dMapVectorLayerInterface::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jobject JNICALL Java_io_openmobilemaps_mapscore_shared_map_layers_tiled_vector_Tiled2dMapVectorLayerInterface_createFromLocalStyleJsonWithZoomInfo(JNIEnv* jniEnv, jobject /*this*/, jstring j_layerName, jstring j_styleJson, jobject j_loaders, ::djinni_generated::NativeFontLoaderInterface::JniType j_fontLoader, jdouble j_dpFactor, ::djinni_generated::NativeTiled2dMapZoomInfo::JniType j_zoomInfo)
{
    try {
        auto r = ::Tiled2dMapVectorLayerInterface::createFromLocalStyleJsonWithZoomInfo(::djinni::String::toCpp(jniEnv, j_layerName),
                                                                                        ::djinni::String::toCpp(jniEnv, j_styleJson),
                                                                                        ::djinni::List<::djinni_generated::NativeLoaderInterface>::toCpp(jniEnv, j_loaders),
                                                                                        ::djinni_generated::NativeFontLoaderInterface::toCpp(jniEnv, j_fontLoader),
                                                                                        ::djinni::F64::toCpp(jniEnv, j_dpFactor),
                                                                                        ::djinni_generated::NativeTiled2dMapZoomInfo::toCpp(jniEnv, j_zoomInfo));
        return ::djinni::release(::djinni_generated::NativeTiled2dMapVectorLayerInterface::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_io_openmobilemaps_mapscore_shared_map_layers_tiled_vector_Tiled2dMapVectorLayerInterface_00024CppProxy_native_1setSelectionDelegate(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_selectionDelegate)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::Tiled2dMapVectorLayerInterface>(nativeRef);
        ref->setSelectionDelegate(::djinni_generated::NativeTiled2dMapVectorLayerSelectionCallbackInterface::toCpp(jniEnv, j_selectionDelegate));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT ::djinni_generated::NativeLayerInterface::JniType JNICALL Java_io_openmobilemaps_mapscore_shared_map_layers_tiled_vector_Tiled2dMapVectorLayerInterface_00024CppProxy_native_1asLayerInterface(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::Tiled2dMapVectorLayerInterface>(nativeRef);
        auto r = ref->asLayerInterface();
        return ::djinni::release(::djinni_generated::NativeLayerInterface::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_io_openmobilemaps_mapscore_shared_map_layers_tiled_vector_Tiled2dMapVectorLayerInterface_00024CppProxy_native_1getStyleMetadataJson(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::Tiled2dMapVectorLayerInterface>(nativeRef);
        auto r = ref->getStyleMetadataJson();
        return ::djinni::release(::djinni::Optional<std::optional, ::djinni::String>::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_io_openmobilemaps_mapscore_shared_map_layers_tiled_vector_Tiled2dMapVectorLayerInterface_00024CppProxy_native_1setFeatureState(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_identifier, jobject j_properties)
{
    try {
        const auto& ref = ::djinni::objectFromHandleAddress<::Tiled2dMapVectorLayerInterface>(nativeRef);
        ref->setFeatureState(::djinni::String::toCpp(jniEnv, j_identifier),
                             ::djinni::Map<::djinni::String, ::djinni_generated::NativeVectorLayerFeatureInfoValue>::toCpp(jniEnv, j_properties));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

} // namespace djinni_generated
