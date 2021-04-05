package io.openmobilemaps.mapscore.graphics

import io.openmobilemaps.mapscore.shared.map.loader.VectorTileHolderInterface

class VectorTileHolder(private val data: ByteArray) : VectorTileHolderInterface() {
	override fun getData(): ArrayList<Byte> {
		return data.toCollection(ArrayList())
	}
}