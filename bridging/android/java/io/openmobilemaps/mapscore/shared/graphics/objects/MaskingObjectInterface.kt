// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from graphicsobjects.djinni

package io.openmobilemaps.mapscore.shared.graphics.objects

import java.util.concurrent.atomic.AtomicBoolean

abstract class MaskingObjectInterface {

    abstract fun asGraphicsObject(): GraphicsObjectInterface

    abstract fun renderAsMask(context: io.openmobilemaps.mapscore.shared.graphics.RenderingContextInterface, renderPass: io.openmobilemaps.mapscore.shared.graphics.RenderPassConfig, mvpMatrix: Long, screenPixelAsRealMeterFactor: Double)

    abstract fun asGraphicsObject(): GraphicsObjectInterface

    private class CppProxy : MaskingObjectInterface {
        private val nativeRef: Long
        private val destroyed: AtomicBoolean = AtomicBoolean(false)

        private constructor(nativeRef: Long) {
            if (nativeRef == 0L) error("nativeRef is zero")
            this.nativeRef = nativeRef
        }

        private external fun nativeDestroy(nativeRef: Long)
        fun _djinni_private_destroy() {
            val destroyed = this.destroyed.getAndSet(true)
            if (!destroyed) nativeDestroy(this.nativeRef)
        }
        protected fun finalize() {
            _djinni_private_destroy()
        }

        override fun asGraphicsObject(): GraphicsObjectInterface {
            assert(!this.destroyed.get()) { error("trying to use a destroyed object") }
            return native_asGraphicsObject(this.nativeRef)
        }
        private external fun native_asGraphicsObject(_nativeRef: Long): GraphicsObjectInterface

        override fun renderAsMask(context: io.openmobilemaps.mapscore.shared.graphics.RenderingContextInterface, renderPass: io.openmobilemaps.mapscore.shared.graphics.RenderPassConfig, mvpMatrix: Long, screenPixelAsRealMeterFactor: Double) {
            assert(!this.destroyed.get()) { error("trying to use a destroyed object") }
            native_renderAsMask(this.nativeRef, context, renderPass, mvpMatrix, screenPixelAsRealMeterFactor)
        }
        private external fun native_renderAsMask(_nativeRef: Long, context: io.openmobilemaps.mapscore.shared.graphics.RenderingContextInterface, renderPass: io.openmobilemaps.mapscore.shared.graphics.RenderPassConfig, mvpMatrix: Long, screenPixelAsRealMeterFactor: Double)

        override fun asGraphicsObject(): GraphicsObjectInterface {
            assert(!this.destroyed.get()) { error("trying to use a destroyed object") }
            return native_asGraphicsObject(this.nativeRef)
        }
        private external fun native_asGraphicsObject(_nativeRef: Long): GraphicsObjectInterface
    }
}
