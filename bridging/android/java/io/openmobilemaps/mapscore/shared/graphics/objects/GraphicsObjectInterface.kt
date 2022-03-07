// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from graphicsobjects.djinni

package io.openmobilemaps.mapscore.shared.graphics.objects

import java.util.concurrent.atomic.AtomicBoolean

abstract class GraphicsObjectInterface {

    /** Returns true, if graphics object is ready to be drawn */
    abstract fun isReady(): Boolean

    /** Ensure calling on graphics thread */
    abstract fun setup(context: io.openmobilemaps.mapscore.shared.graphics.RenderingContextInterface)

    /** Clear graphics object and invalidate isReady */
    abstract fun clear()

    /**
     * by defaults objects if masked are only rendered where the mask is set
     * if setting this flag the masked is applied inversly
     */
    abstract fun setIsInverseMasked(inversed: Boolean)

    /** Render the graphics object; ensure calling on graphics thread */
    abstract fun render(context: io.openmobilemaps.mapscore.shared.graphics.RenderingContextInterface, renderPass: io.openmobilemaps.mapscore.shared.graphics.RenderPassConfig, mvpMatrix: Long, isMasked: Boolean, screenPixelAsRealMeterFactor: Double)

    private class CppProxy : GraphicsObjectInterface {
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

        override fun isReady(): Boolean {
            assert(!this.destroyed.get()) { error("trying to use a destroyed object") }
            return native_isReady(this.nativeRef)
        }
        private external fun native_isReady(_nativeRef: Long): Boolean

        override fun setup(context: io.openmobilemaps.mapscore.shared.graphics.RenderingContextInterface) {
            assert(!this.destroyed.get()) { error("trying to use a destroyed object") }
            native_setup(this.nativeRef, context)
        }
        private external fun native_setup(_nativeRef: Long, context: io.openmobilemaps.mapscore.shared.graphics.RenderingContextInterface)

        override fun clear() {
            assert(!this.destroyed.get()) { error("trying to use a destroyed object") }
            native_clear(this.nativeRef)
        }
        private external fun native_clear(_nativeRef: Long)

        override fun setIsInverseMasked(inversed: Boolean) {
            assert(!this.destroyed.get()) { error("trying to use a destroyed object") }
            native_setIsInverseMasked(this.nativeRef, inversed)
        }
        private external fun native_setIsInverseMasked(_nativeRef: Long, inversed: Boolean)

        override fun render(context: io.openmobilemaps.mapscore.shared.graphics.RenderingContextInterface, renderPass: io.openmobilemaps.mapscore.shared.graphics.RenderPassConfig, mvpMatrix: Long, isMasked: Boolean, screenPixelAsRealMeterFactor: Double) {
            assert(!this.destroyed.get()) { error("trying to use a destroyed object") }
            native_render(this.nativeRef, context, renderPass, mvpMatrix, isMasked, screenPixelAsRealMeterFactor)
        }
        private external fun native_render(_nativeRef: Long, context: io.openmobilemaps.mapscore.shared.graphics.RenderingContextInterface, renderPass: io.openmobilemaps.mapscore.shared.graphics.RenderPassConfig, mvpMatrix: Long, isMasked: Boolean, screenPixelAsRealMeterFactor: Double)
    }
}
