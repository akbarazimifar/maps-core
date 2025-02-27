/*
 * Copyright (c) 2021 Ubique Innovation AG <https://www.ubique.ch>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 *  SPDX-License-Identifier: MPL-2.0
 */

#include "ColorLineGroup2dShaderOpenGl.h"
#include "OpenGlContext.h"
#include "OpenGlHelper.h"

ColorLineGroup2dShaderOpenGl::ColorLineGroup2dShaderOpenGl() {
    lineValues.resize(sizeLineValuesArray);
}

const std::string ColorLineGroup2dShaderOpenGl::programName = "UBMAP_ColorLineGroupShaderOpenGl";

std::shared_ptr<ShaderProgramInterface> ColorLineGroup2dShaderOpenGl::asShaderProgramInterface() { return shared_from_this(); }

std::string ColorLineGroup2dShaderOpenGl::getProgramName() { return programName; }

void ColorLineGroup2dShaderOpenGl::setupProgram(const std::shared_ptr<::RenderingContextInterface> &context) {
    std::shared_ptr<OpenGlContext> openGlContext = std::static_pointer_cast<OpenGlContext>(context);
    // prepare shaders and OpenGL program
    int vertexShader = loadShader(GL_VERTEX_SHADER, getVertexShader());
    int fragmentShader = loadShader(GL_FRAGMENT_SHADER, getFragmentShader());

    int program = glCreateProgram();       // create empty OpenGL Program
    glAttachShader(program, vertexShader); // add the vertex shader to program
    glDeleteShader(vertexShader);
    glAttachShader(program, fragmentShader); // add the fragment shader to program
    glDeleteShader(fragmentShader);

    glLinkProgram(program); // create OpenGL program executables

    openGlContext->storeProgram(programName, program);
}

void ColorLineGroup2dShaderOpenGl::preRender(const std::shared_ptr<::RenderingContextInterface> &context) {
    BaseShaderProgramOpenGl::preRender(context);
    std::shared_ptr<OpenGlContext> openGlContext = std::static_pointer_cast<OpenGlContext>(context);
    int program = openGlContext->getProgram(programName);

    {
        std::lock_guard<std::recursive_mutex> lock(styleMutex);
        if (numStyles == 0) {
            return;
        }
        int lineStylesHandle = glGetUniformLocation(program, "lineValues");
        glUniform1fv(lineStylesHandle, sizeLineValuesArray, &lineValues[0]);
        int numStylesHandle = glGetUniformLocation(program, "numStyles");
        glUniform1i(numStylesHandle, numStyles);
        int dashingScaleFactorHandle = glGetUniformLocation(program, "dashingScaleFactor");
        glUniform1f(dashingScaleFactorHandle, dashingScaleFactor);
    }
}

void ColorLineGroup2dShaderOpenGl::setStyles(const ::SharedBytes & styles) {
    {
        std::lock_guard<std::recursive_mutex> overlayLock(styleMutex);
        if(styles.elementCount > 0) {
            std::memcpy(lineValues.data(), (void *)styles.address, styles.elementCount * styles.bytesPerElement);
        }

        numStyles = styles.elementCount;
    }
}

void ColorLineGroup2dShaderOpenGl::setDashingScaleFactor(float factor) {
    {
        std::lock_guard<std::recursive_mutex> overlayLock(styleMutex);
        this->dashingScaleFactor = factor;
    }}

std::string ColorLineGroup2dShaderOpenGl::getVertexShader() {
    return OMMVersionedGlesShaderCode(320 es,
                                      precision highp float;
                                      uniform mat4 uMVPMatrix;
                                      in vec2 vPosition;
                                      in vec2 vWidthNormal;
                                      in vec2 vPointA;
                                      in vec2 vPointB;
                                      in float vVertexIndex;
                                      in float vSegmentStartLPos;
                                      in float vStyleInfo;
                                      // lineValues:
                                      //        struct LineStyling {
                                      //            float width; // 0
                                      //            float4 color; // 1 2 3 4
                                      //            float4 gapColor; // 5 6 7 8
                                      //            float widthAsPixels; // 9
                                      //            float opacity; // 10
                                      //            float blur; // 11
                                      //            float capType; // 12
                                      //            float numDashValues; // 13
                                      //            float dashArray[4]; // 14 15 16 17
                                      //            float offset; // 18
                                      //        };
                                      uniform float lineValues[) + std::to_string(sizeLineValuesArray) + OMMShaderCode(];
                                      uniform int numStyles;
                                      uniform float scaleFactor;
                                      uniform float dashingScaleFactor;
                                      out float fStyleIndexBase;
                                      out float radius;
                                      out float segmentStartLPos;
                                      out float fSegmentType;
                                      out vec2 pointDeltaA;
                                      out vec2 pointBDeltaA;
                                      out vec4 color;
                                      out float dashingSize;
                                      out float scaledBlur;

                                       void main() {
                                           float fStyleIndex = mod(vStyleInfo, 256.0);
                                           int lineIndex = int(floor(fStyleIndex + 0.5));
                                           if (lineIndex < 0) {
                                                lineIndex = 0;
                                           } else if (lineIndex > numStyles) {
                                                lineIndex = numStyles;
                                           }
                                           int styleIndexBase = ) + std::to_string(sizeLineValues) + OMMShaderCode(* lineIndex;
                                           int colorIndexBase = styleIndexBase + 1;
                                           float width = lineValues[styleIndexBase];
                                           float isScaled = lineValues[styleIndexBase + 9];
                                           float blur = lineValues[styleIndexBase + 11];
                                           color = vec4(lineValues[colorIndexBase], lineValues[colorIndexBase + 1], lineValues[colorIndexBase + 2],
                                                        lineValues[colorIndexBase + 3]);
                                           segmentStartLPos = vSegmentStartLPos;
                                           fStyleIndexBase = float(styleIndexBase);
                                           fSegmentType = vStyleInfo / 256.0;

                                               vec2 widthNormal = vWidthNormal;
                                               vec2 lengthNormal = vec2(widthNormal.y, -widthNormal.x);

                                               if(vVertexIndex == 0.0) {
                                                   lengthNormal *= -1.0;
                                                   widthNormal *= -1.0;
                                               } else if(vVertexIndex == 1.0) {
                                                   lengthNormal *= -1.0;
                                               } else if(vVertexIndex == 2.0) {
                                                   // all fine
                                               } else if(vVertexIndex == 3.0) {
                                                   widthNormal *= -1.0;
                                               }

                                           float offsetFloat = lineValues[styleIndexBase + 18] * scaleFactor;
                                           vec4 offset = vec4(vWidthNormal.x * offsetFloat, vWidthNormal.y * offsetFloat, 0.0, 0.0);

                                               float scaledWidth = width * 0.5;
                                               dashingSize = width;
                                               if (isScaled > 0.0) {
                                                   scaledWidth = scaledWidth * scaleFactor;
                                                   blur = blur * scaleFactor;
                                                   dashingSize *= dashingScaleFactor;
                                               }

                                               vec4 trfPosition = uMVPMatrix * vec4(vPosition.xy, 0.0, 1.0);
                                               vec4 displ = vec4((lengthNormal + widthNormal).xy, 0.0, 0.0) * vec4(scaledWidth, scaledWidth, 0.0, 0.0) + offset;
                                               vec4 trfDispl = uMVPMatrix * displ;
                                               vec4 extendedPosition = vec4(vPosition.xy, 0.0, 1.0) + displ;
                                               radius = scaledWidth;
                                               scaledBlur = blur;
                                               pointDeltaA = (extendedPosition.xy - vPointA);
                                               pointBDeltaA = vPointB - vPointA;
                                               gl_Position = trfPosition + trfDispl;
                                       }
                                       );
}

std::string ColorLineGroup2dShaderOpenGl::getFragmentShader() {
    return OMMVersionedGlesShaderCode(320 es,
                                      precision highp float;
                                      uniform float lineValues[) + std::to_string(sizeLineValuesArray) + OMMShaderCode(];
                                      in float fStyleIndexBase;
                                      in float radius;
                                      in float segmentStartLPos;
                                      in float scaledBlur;
                                      in float fSegmentType; // 0: inner segment, 1: line start segment (i.e. A is first point in line), 2: line end segment, 3: start and end in segment
                                      in float dashingSize;
                                      in vec2 pointDeltaA;
                                      in vec2 pointBDeltaA;
                                      in vec4 color;

                                      out vec4 fragmentColor;

                                       void main() {
                                           int segmentType = int(floor(fSegmentType + 0.5));
                                           // 0: butt, 1: round, 2: square
                                           int iCapType = int(floor(lineValues[int(fStyleIndexBase) + 12] + 0.5));
                                           float lineLength = length(pointBDeltaA);
                                           float t = dot(pointDeltaA, normalize(pointBDeltaA)) / lineLength;
                                           float d;
                                           if (t < 0.0 || t > 1.0) {
                                               if (segmentType == 0 || iCapType == 1 || (segmentType == 2 && t < 0.0) || (segmentType == 1 && t > 1.0)) {
                                                   d = min(length(pointDeltaA), length(pointDeltaA - pointBDeltaA));
                                               } else if (iCapType == 2) {
                                                   float dLen = t < 0.0 ? -t * lineLength : (t - 1.0) * lineLength;
                                                   vec2 intersectPt = t * pointBDeltaA;
                                                   float dOrth = abs(length(pointDeltaA - intersectPt));
                                                   d = max(dLen, dOrth);
                                               } else {
                                                   discard;
                                               }
                                           } else {
                                               vec2 intersectPt = t * pointBDeltaA;
                                               d = abs(length(pointDeltaA - intersectPt));
                                           }

                                           if (d > radius) {
                                               discard;
                                           }

                                           vec4 fragColor = color;
                                           float opacity = lineValues[int(fStyleIndexBase) + 10];

                                           int dashBase = int(fStyleIndexBase) + 13;
                                           // dash values: {int numDashInfo, vec4 dashArray} -> stride = 5
                                           int numDashInfos = int(floor(lineValues[dashBase] + 0.5));
                                           if (numDashInfos > 0) {
                                               int gapColorIndexBase = int(fStyleIndexBase) + 5;
                                               vec4 gapColor = vec4(lineValues[gapColorIndexBase], lineValues[gapColorIndexBase + 1],
                                                                    lineValues[gapColorIndexBase + 2], lineValues[gapColorIndexBase + 3]);

                                               int baseDashInfos = dashBase + 1;
                                               float factorToT = dashingSize / lineLength;
                                               float dashTotal = lineValues[baseDashInfos + (numDashInfos - 1)] * factorToT;
                                               float startOffsetSegment = mod(segmentStartLPos / lineLength, dashTotal);
                                               float intraDashPos = mod(t + startOffsetSegment, dashTotal);
                                               // unrolled for efficiency reasons
                                               if ((intraDashPos > lineValues[baseDashInfos + 0] * factorToT &&
                                                intraDashPos < lineValues[baseDashInfos + 1] * factorToT) ||
                                                (intraDashPos > lineValues[baseDashInfos + 2] * factorToT &&
                                                intraDashPos < lineValues[baseDashInfos + 3] * factorToT)) {
                                                    fragColor = gapColor;
                                                }
                                            }


                                           if (scaledBlur > 0.0 && t > 0.0 && t < 1.0) {
                                               float nonBlurRange = radius - scaledBlur;
                                               if (d > nonBlurRange) {
                                                   opacity *= clamp(1.0 - max(0.0, d - nonBlurRange) / scaledBlur, 0.0, 1.0);
                                               }
                                           }


                                           fragmentColor = fragColor;
                                           fragmentColor.a = 1.0;
                                           fragmentColor *= fragColor.a * opacity;
                                       });
}
