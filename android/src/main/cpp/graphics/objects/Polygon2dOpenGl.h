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
#include "MaskingObjectInterface.h"
#include "OpenGlContext.h"
#include "Polygon2dInterface.h"
#include "ShaderProgramInterface.h"
#include "opengl_wrapper.h"

class Polygon2dOpenGl : public GraphicsObjectInterface,
                        public MaskingObjectInterface,
                        public Polygon2dInterface,
                        public std::enable_shared_from_this<Polygon2dOpenGl> {
public:
    Polygon2dOpenGl(const std::shared_ptr<::ShaderProgramInterface> &shader);

    ~Polygon2dOpenGl() {};

    virtual bool isReady() override;

    virtual void setup(const std::shared_ptr<::RenderingContextInterface> &context) override;

    virtual void clear() override;

    virtual void render(const std::shared_ptr<::RenderingContextInterface> &context, const ::RenderPassConfig &renderPass,
                        int64_t mvpMatrix, bool isMasked, double screenPixelAsRealMeterFactor) override;

    virtual void renderAsMask(const std::shared_ptr<::RenderingContextInterface> &context, const ::RenderPassConfig &renderPass,
                              int64_t mvpMatrix, double screenPixelAsRealMeterFactor) override;

    virtual void setPolygonPositions(const std::vector<::Vec2D> &positions, const std::vector<std::vector<::Vec2D>> &holes,
                                     bool isConvex) override;

    virtual std::shared_ptr<GraphicsObjectInterface> asGraphicsObject() override;

    virtual std::shared_ptr<MaskingObjectInterface> asMaskingObject() override;

protected:
    void initializePolygon();

    void drawPolygon(std::shared_ptr<OpenGlContext> openGlContext, int program, int64_t mvpMatrix);

    std::shared_ptr<ShaderProgramInterface> shaderProgram;

    bool polygonIsConvex = false;
    std::vector<::Vec2D> polygonCoordinates;
    std::vector<std::vector<::Vec2D>> holePolygonCoordinates;

    std::vector<GLfloat> vertexBuffer;
    std::vector<GLushort> indexBuffer;

    bool ready = false;
};
