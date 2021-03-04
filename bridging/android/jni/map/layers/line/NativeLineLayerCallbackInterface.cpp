// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from line.djinni

#include "NativeLineLayerCallbackInterface.h"  // my header
#include "Marshal.hpp"
#include "NativeLineInfo.h"

namespace djinni_generated {

NativeLineLayerCallbackInterface::NativeLineLayerCallbackInterface() : ::djinni::JniInterface<::LineLayerCallbackInterface, NativeLineLayerCallbackInterface>("io/openmobilemaps/mapscore/shared/map/layers/line/LineLayerCallbackInterface$CppProxy") {}

NativeLineLayerCallbackInterface::~NativeLineLayerCallbackInterface() = default;

NativeLineLayerCallbackInterface::JavaProxy::JavaProxy(JniType j) : Handle(::djinni::jniGetThreadEnv(), j) { }

NativeLineLayerCallbackInterface::JavaProxy::~JavaProxy() = default;

bool NativeLineLayerCallbackInterface::JavaProxy::onLineClickConfirmed(const std::vector<::LineInfo> & c_icons) {
    auto jniEnv = ::djinni::jniGetThreadEnv();
    ::djinni::JniLocalScope jscope(jniEnv, 10);
    const auto& data = ::djinni::JniClass<::djinni_generated::NativeLineLayerCallbackInterface>::get();
    auto jret = jniEnv->CallBooleanMethod(Handle::get().get(), data.method_onLineClickConfirmed,
                                          ::djinni::get(::djinni::List<::djinni_generated::NativeLineInfo>::fromCpp(jniEnv, c_icons)));
    ::djinni::jniExceptionCheck(jniEnv);
    return ::djinni::Bool::toCpp(jniEnv, jret);
}

CJNIEXPORT void JNICALL Java_io_openmobilemaps_mapscore_shared_map_layers_line_LineLayerCallbackInterface_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::LineLayerCallbackInterface>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jboolean JNICALL Java_io_openmobilemaps_mapscore_shared_map_layers_line_LineLayerCallbackInterface_00024CppProxy_native_1onLineClickConfirmed(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_icons)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::LineLayerCallbackInterface>(nativeRef);
        auto r = ref->onLineClickConfirmed(::djinni::List<::djinni_generated::NativeLineInfo>::toCpp(jniEnv, j_icons));
        return ::djinni::release(::djinni::Bool::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

}  // namespace djinni_generated
