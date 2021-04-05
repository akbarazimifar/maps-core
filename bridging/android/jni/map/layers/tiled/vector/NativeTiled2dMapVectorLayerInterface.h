// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from tiled_vector_layer.djinni

#pragma once

#include "Tiled2dMapVectorLayerInterface.h"
#include "djinni_support.hpp"

namespace djinni_generated {

class NativeTiled2dMapVectorLayerInterface final : ::djinni::JniInterface<::Tiled2dMapVectorLayerInterface, NativeTiled2dMapVectorLayerInterface> {
public:
    using CppType = std::shared_ptr<::Tiled2dMapVectorLayerInterface>;
    using CppOptType = std::shared_ptr<::Tiled2dMapVectorLayerInterface>;
    using JniType = jobject;

    using Boxed = NativeTiled2dMapVectorLayerInterface;

    ~NativeTiled2dMapVectorLayerInterface();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeTiled2dMapVectorLayerInterface>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeTiled2dMapVectorLayerInterface>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeTiled2dMapVectorLayerInterface();
    friend ::djinni::JniClass<NativeTiled2dMapVectorLayerInterface>;
    friend ::djinni::JniInterface<::Tiled2dMapVectorLayerInterface, NativeTiled2dMapVectorLayerInterface>;

};

}  // namespace djinni_generated
