/*
 * Copyright (c) 2021 Ubique Innovation AG <https://www.ubique.ch>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 *  SPDX-License-Identifier: MPL-2.0
 */

#pragma once

#include "GraphicsObjectInterface.h"
#include "PolygonGroup2dInterface.h"
#include "ShaderProgramInterface.h"
#include "OpenGlContext.h"
#include "OpenGlHelper.h"
#include "opengl_wrapper.h"
#include "RenderLineDescription.h"

class PolygonGroup2dOpenGl : public GraphicsObjectInterface,
                             public PolygonGroup2dInterface,
                             public std::enable_shared_from_this<GraphicsObjectInterface> {
public:

    PolygonGroup2dOpenGl(const std::shared_ptr<::ShaderProgramInterface> &shader);

    virtual ~PolygonGroup2dOpenGl() {}

    // PolygonGroup2dInterface

    virtual void setVertices(const std::vector<RenderVerticesDescription> & vertices, const std::vector<int32_t> & indices) override;

    virtual std::shared_ptr<GraphicsObjectInterface> asGraphicsObject() override;

    // GraphicsObjectInterface

    virtual bool isReady() override;

    virtual void setup(const std::shared_ptr<::RenderingContextInterface> & context) override;

    virtual void clear() override;

    virtual void render(const std::shared_ptr<::RenderingContextInterface> & context, const ::RenderPassConfig & renderPass, int64_t mvpMatrix, bool isMasked, double screenPixelAsRealMeterFactor) override;

protected:
    std::shared_ptr<ShaderProgramInterface> shaderProgram;
    int mvpMatrixHandle;
    int positionHandle;
    int styleIndexHandle;
    GLuint attribBuffer;
    std::vector<GLfloat> polygonAttributes;
    GLuint indexBuffer;
    std::vector<GLushort> polygonIndices;

    bool dataReady = false;
    bool ready = false;
};


