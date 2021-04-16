/*
 * Copyright (c) 2021 Ubique Innovation AG <https://www.ubique.ch>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 *  SPDX-License-Identifier: MPL-2.0
 */

import Foundation
import MapCoreSharedModule
import Metal
import UIKit

class Quad2d: BaseGraphicsObject {
    private var verticesBuffer: MTLBuffer?

    private var indicesBuffer: MTLBuffer?

    private var indicesCount: Int = 0

    private var texture: MTLTexture?

    private var shader: MCShaderProgramInterface

    init(shader: MCShaderProgramInterface, metalContext: MetalContext) {
        self.shader = shader
        super.init(device: metalContext.device,
                   sampler: metalContext.samplerLibrary.value(.magLinear))
    }

    override func render(encoder: MTLRenderCommandEncoder,
                         context: RenderingContext,
                         renderPass _: MCRenderPassConfig,
                         mvpMatrix: Int64,
                         isMasked: Bool)
    {
        guard let verticesBuffer = verticesBuffer,
              let indicesBuffer = indicesBuffer else { return }
        shader.setupProgram(context)
        shader.preRender(context)

        encoder.setVertexBuffer(verticesBuffer, offset: 0, index: 0)
        if let matrixPointer = UnsafeRawPointer(bitPattern: Int(mvpMatrix)) {
            encoder.setVertexBytes(matrixPointer, length: 64, index: 1)
        }

        encoder.setFragmentSamplerState(sampler, index: 0)

        if let texture = texture {
            encoder.setFragmentTexture(texture, index: 0)
        }

        encoder.drawIndexedPrimitives(type: .triangle,
                                      indexCount: indicesCount,
                                      indexType: .uint16,
                                      indexBuffer: indicesBuffer,
                                      indexBufferOffset: 0)
    }
}

extension Quad2d: MCMaskingObjectInterface {
    func render(asMask context: MCRenderingContextInterface?, renderPass: MCRenderPassConfig, mvpMatrix: Int64) {
        guard let context = context as? RenderingContext,
              let encoder = context.encoder else { return }

        if let mask = context.mask {
            encoder.setDepthStencilState(mask)
            encoder.setStencilReferenceValue(0b10000000)
        }

        render(encoder: encoder, context: context, renderPass: renderPass, mvpMatrix: mvpMatrix, isMasked: false)
    }

}

extension Quad2d: MCQuad2dInterface {
    func setFrame(_ frame: MCQuad2dD, textureCoordinates: MCRectD) {
        /*
         The quad is made out of 4 vertices as following
         B----C
         |    |
         |    |
         A----D
         Where A-C are joined to form two triangles
         */
        let vertecies: [Vertex] = [
            Vertex(position: frame.bottomLeft, textureU: textureCoordinates.xF, textureV: textureCoordinates.heightF), // A
            Vertex(position: frame.topLeft, textureU: textureCoordinates.xF, textureV: textureCoordinates.yF), // B
            Vertex(position: frame.topRight, textureU: textureCoordinates.widthF, textureV: textureCoordinates.yF), // C
            Vertex(position: frame.bottomRight, textureU: textureCoordinates.widthF, textureV: textureCoordinates.heightF), // D
        ]
        let indices: [UInt16] = [
            0, 1, 2, // ABC
            0, 2, 3, // ACD
        ]

        guard let verticesBuffer = device.makeBuffer(bytes: vertecies, length: MemoryLayout<Vertex>.stride * vertecies.count, options: []), let indicesBuffer = device.makeBuffer(bytes: indices, length: MemoryLayout<UInt16>.stride * indices.count, options: []) else {
            fatalError("Cannot allocate buffers")
        }

        indicesCount = indices.count
        self.verticesBuffer = verticesBuffer
        self.indicesBuffer = indicesBuffer
    }

    func loadTexture(_ textureHolder: MCTextureHolderInterface?) {
        guard let textureHolder = textureHolder as? TextureHolder else {
            fatalError("unexpected TextureHolder")
        }
        texture = textureHolder.texture
    }

    func removeTexture() {
        texture = nil
    }

    func asGraphicsObject() -> MCGraphicsObjectInterface? { self }

    func asMaskingObject() -> MCMaskingObjectInterface? { self }
}
