/*
 * Copyright (c) 2021 Ubique Innovation AG <https://www.ubique.ch>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 *  SPDX-License-Identifier: MPL-2.0
 */

#include "OpenGlContext.h"
#include "OpenGlHelper.h"
#include "ColorPolygonGroup2dShaderOpenGl.h"

std::shared_ptr <ShaderProgramInterface> ColorPolygonGroup2dShaderOpenGl::asShaderProgramInterface() {
    return shared_from_this();
}

std::string ColorPolygonGroup2dShaderOpenGl::getProgramName() {
    return "UBMAP_ColorPolygonGroupShaderOpenGl";
}

void ColorPolygonGroup2dShaderOpenGl::setupProgram(const std::shared_ptr<::RenderingContextInterface> &context) {
    std::shared_ptr<OpenGlContext> openGlContext = std::static_pointer_cast<OpenGlContext>(context);
    std::string programName = getProgramName();
    // prepare shaders and OpenGL program
    int vertexShader = loadShader(GL_VERTEX_SHADER, getVertexShader());
    int fragmentShader = loadShader(GL_FRAGMENT_SHADER, getFragmentShader());

    int program = glCreateProgram();       // create empty OpenGL Program
    glAttachShader(program, vertexShader); // add the vertex shader to program
    OpenGlHelper::checkGlError("glAttachShader Vertex  PolygonGroup");
    glDeleteShader(vertexShader);
    glAttachShader(program, fragmentShader); // add the fragment shader to program
    OpenGlHelper::checkGlError("glAttachShader Fragment PolygonGroup");
    glDeleteShader(fragmentShader);

    glLinkProgram(program); // create OpenGL program executables
    OpenGlHelper::checkGlError("glLinkProgram PolygonGroup");

    openGlContext->storeProgram(programName, program);
}

void ColorPolygonGroup2dShaderOpenGl::preRender(const std::shared_ptr<::RenderingContextInterface> &context) {
    std::shared_ptr<OpenGlContext> openGlContext = std::static_pointer_cast<OpenGlContext>(context);
    int program = openGlContext->getProgram(getProgramName());

    {
        std::lock_guard<std::recursive_mutex> overlayLock(styleMutex);
        int lineStylesHandle = glGetUniformLocation(program, "polygonStyles");
        glUniform1fv(lineStylesHandle, sizeStyleValuesArray, &polygonStyles[0]);
        OpenGlHelper::checkGlError("glUniform1f polygonStyles");
        int numStylesHandle = glGetUniformLocation(program, "numStyles");
        glUniform1i(numStylesHandle, numStyles);
        OpenGlHelper::checkGlError("glUniform1f numStyles");
    }
}

void ColorPolygonGroup2dShaderOpenGl::setStyles(const std::vector<::PolygonStyle> &styles) {
    std::vector<float> styleValues(sizeStyleValuesArray, 0.0);
    int numStyles = styles.size();
    for (int i = 0; i < styles.size(); i++) {
        const auto &style = styles[i];
        styleValues[sizeStyleValues * i] = style.color.r;
        styleValues[sizeStyleValues * i + 1] = style.color.g;
        styleValues[sizeStyleValues * i + 2] = style.color.b;
        styleValues[sizeStyleValues * i + 3] = style.color.a * style.opacity;
    }

    {
        std::lock_guard<std::recursive_mutex> overlayLock(styleMutex);
        this->polygonStyles = styleValues;
        this->numStyles = numStyles;
    }
}

std::string ColorPolygonGroup2dShaderOpenGl::getVertexShader() {
    return UBRendererShaderCode(
            precision highp float;

            uniform mat4 uMVPMatrix;
            attribute vec2 vPosition;
            attribute float vStyleIndex;
            // polygonStyles: {vec4 color} - stride = 4
            uniform float polygonStyles[4 * 32];
            uniform int numStyles;

            varying vec4 color;

            void main() {
                int styleIndex = 4 * clamp(int(floor(vStyleIndex + 0.5)), 0, numStyles);
                color = vec4(polygonStyles[styleIndex], polygonStyles[styleIndex + 1], polygonStyles[styleIndex + 2], polygonStyles[styleIndex + 3]);
                gl_Position = uMVPMatrix * vec4(vPosition, 0.0, 1.0);
            });
}

std::string ColorPolygonGroup2dShaderOpenGl::getFragmentShader() {
    return UBRendererShaderCode(
            precision highp float;

            varying vec4 color;

            void main() {
                gl_FragColor = color;
                gl_FragColor.a = 1.0;
                gl_FragColor *= color.a;
            });
}

