// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from tiled_layer.djinni

package io.openmobilemaps.mapscore.shared.map.layers.tiled

import com.snapchat.djinni.NativeObjectManager
import java.util.concurrent.atomic.AtomicBoolean

abstract class Tiled2dMapLayerConfig {

    abstract fun getCoordinateSystemIdentifier(): Int

    abstract fun getTileUrl(x: Int, y: Int, t: Int, zoom: Int): String

    abstract fun getZoomLevelInfos(): ArrayList<Tiled2dMapZoomLevelInfo>

    abstract fun getZoomInfo(): Tiled2dMapZoomInfo

    abstract fun getLayerName(): String

    abstract fun getVectorSettings(): Tiled2dMapVectorSettings?

    private class CppProxy : Tiled2dMapLayerConfig {
        private val nativeRef: Long
        private val destroyed: AtomicBoolean = AtomicBoolean(false)

        private constructor(nativeRef: Long) {
            if (nativeRef == 0L) error("nativeRef is zero")
            this.nativeRef = nativeRef
            NativeObjectManager.register(this, nativeRef)
        }

        companion object {
            @JvmStatic
            external fun nativeDestroy(nativeRef: Long)
        }

        override fun getCoordinateSystemIdentifier(): Int {
            assert(!this.destroyed.get()) { error("trying to use a destroyed object") }
            return native_getCoordinateSystemIdentifier(this.nativeRef)
        }
        private external fun native_getCoordinateSystemIdentifier(_nativeRef: Long): Int

        override fun getTileUrl(x: Int, y: Int, t: Int, zoom: Int): String {
            assert(!this.destroyed.get()) { error("trying to use a destroyed object") }
            return native_getTileUrl(this.nativeRef, x, y, t, zoom)
        }
        private external fun native_getTileUrl(_nativeRef: Long, x: Int, y: Int, t: Int, zoom: Int): String

        override fun getZoomLevelInfos(): ArrayList<Tiled2dMapZoomLevelInfo> {
            assert(!this.destroyed.get()) { error("trying to use a destroyed object") }
            return native_getZoomLevelInfos(this.nativeRef)
        }
        private external fun native_getZoomLevelInfos(_nativeRef: Long): ArrayList<Tiled2dMapZoomLevelInfo>

        override fun getZoomInfo(): Tiled2dMapZoomInfo {
            assert(!this.destroyed.get()) { error("trying to use a destroyed object") }
            return native_getZoomInfo(this.nativeRef)
        }
        private external fun native_getZoomInfo(_nativeRef: Long): Tiled2dMapZoomInfo

        override fun getLayerName(): String {
            assert(!this.destroyed.get()) { error("trying to use a destroyed object") }
            return native_getLayerName(this.nativeRef)
        }
        private external fun native_getLayerName(_nativeRef: Long): String

        override fun getVectorSettings(): Tiled2dMapVectorSettings? {
            assert(!this.destroyed.get()) { error("trying to use a destroyed object") }
            return native_getVectorSettings(this.nativeRef)
        }
        private external fun native_getVectorSettings(_nativeRef: Long): Tiled2dMapVectorSettings?
    }
}
