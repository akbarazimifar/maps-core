// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from graphicsobjects.djinni

package io.openmobilemaps.mapscore.shared.graphics.objects

import java.util.concurrent.atomic.AtomicBoolean

abstract class PolygonGroup2dInterface {

    abstract fun setVertices(vertices: ArrayList<RenderVerticesDescription>, indices: ArrayList<Int>)

    abstract fun asGraphicsObject(): GraphicsObjectInterface

    private class CppProxy : PolygonGroup2dInterface {
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

        override fun setVertices(vertices: ArrayList<RenderVerticesDescription>, indices: ArrayList<Int>) {
            assert(!this.destroyed.get()) { error("trying to use a destroyed object") }
            native_setVertices(this.nativeRef, vertices, indices)
        }
        private external fun native_setVertices(_nativeRef: Long, vertices: ArrayList<RenderVerticesDescription>, indices: ArrayList<Int>)

        override fun asGraphicsObject(): GraphicsObjectInterface {
            assert(!this.destroyed.get()) { error("trying to use a destroyed object") }
            return native_asGraphicsObject(this.nativeRef)
        }
        private external fun native_asGraphicsObject(_nativeRef: Long): GraphicsObjectInterface
    }
}
