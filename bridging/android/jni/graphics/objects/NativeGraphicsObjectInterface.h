// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from graphicsobjects.djinni

#pragma once

#include "GraphicsObjectInterface.h"
#include "djinni_support.hpp"

namespace djinni_generated {

class NativeGraphicsObjectInterface final : ::djinni::JniInterface<::GraphicsObjectInterface, NativeGraphicsObjectInterface> {
public:
    using CppType = std::shared_ptr<::GraphicsObjectInterface>;
    using CppOptType = std::shared_ptr<::GraphicsObjectInterface>;
    using JniType = jobject;

    using Boxed = NativeGraphicsObjectInterface;

    ~NativeGraphicsObjectInterface();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeGraphicsObjectInterface>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeGraphicsObjectInterface>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeGraphicsObjectInterface();
    friend ::djinni::JniClass<NativeGraphicsObjectInterface>;
    friend ::djinni::JniInterface<::GraphicsObjectInterface, NativeGraphicsObjectInterface>;

    class JavaProxy final : ::djinni::JavaProxyHandle<JavaProxy>, public ::GraphicsObjectInterface
    {
    public:
        JavaProxy(JniType j);
        ~JavaProxy();

        bool isReady() override;
        void setup(const std::shared_ptr<::RenderingContextInterface> & context) override;
        void clear() override;
        void render(const std::shared_ptr<::RenderingContextInterface> & context, const ::RenderPassConfig & renderPass, int64_t mvpMatrix, bool isMasked) override;

    private:
        friend ::djinni::JniInterface<::GraphicsObjectInterface, ::djinni_generated::NativeGraphicsObjectInterface>;
    };

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("io/openmobilemaps/mapscore/shared/graphics/objects/GraphicsObjectInterface") };
    const jmethodID method_isReady { ::djinni::jniGetMethodID(clazz.get(), "isReady", "()Z") };
    const jmethodID method_setup { ::djinni::jniGetMethodID(clazz.get(), "setup", "(Lio/openmobilemaps/mapscore/shared/graphics/RenderingContextInterface;)V") };
    const jmethodID method_clear { ::djinni::jniGetMethodID(clazz.get(), "clear", "()V") };
    const jmethodID method_render { ::djinni::jniGetMethodID(clazz.get(), "render", "(Lio/openmobilemaps/mapscore/shared/graphics/RenderingContextInterface;Lio/openmobilemaps/mapscore/shared/graphics/RenderPassConfig;JZ)V") };
};

}  // namespace djinni_generated
