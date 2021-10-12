/*
 * Copyright (c) 2021 Ubique Innovation AG <https://www.ubique.ch>
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 *  SPDX-License-Identifier: MPL-2.0
 */

#include <metal_stdlib>
using namespace metal;

struct LineVertexIn {
    float2 position [[attribute(0)]];
    float2 lineA [[attribute(1)]];
    float2 lineB [[attribute(2)]];
    float2 widthNormal [[attribute(3)]];
    float2 lenghtNormal [[attribute(4)]];
    int stylingIndex [[attribute(5)]];
    int segmentType [[attribute(6)]];
    float lenghtPrefix [[attribute(7)]];
};

struct LineVertexOut {
    float4 position [[ position ]];
    float2 uv;
    float2 lineA;
    float2 lineB;
    int stylingIndex;
    float width;
    int segmentType;
    float lenghtPrefix;
};

vertex LineVertexOut
lineVertexShader(const LineVertexIn vertexIn [[stage_in]],
                 constant float4x4 &mvpMatrix [[buffer(1)]],
                 constant float &width [[buffer(2)]])
{
    // extend position in width direction and in lenght direction by width / 2.0
    float4 extendedPosition = float4(vertexIn.position.xy + (vertexIn.widthNormal.xy * width / 2.0) + (vertexIn.lenghtNormal.xy * width / 2.0), 0.0, 1.0);
    
    LineVertexOut out {
        .position = mvpMatrix * extendedPosition,
        .uv = extendedPosition.xy,
        .lineA = vertexIn.lineA,
        .lineB = vertexIn.lineB,
        .stylingIndex = 0,
        .width = 0,
        .segmentType = vertexIn.segmentType,
        .lenghtPrefix = vertexIn.lenghtPrefix,

    };

    return out;
}

fragment float4
lineFragmentShader(LineVertexOut in [[stage_in]],
                   constant float4 &color [[buffer(1)]],
                   constant float &radius [[buffer(2)]])
{
    float2 m = in.lineB - in.lineA;
    float t0 = dot(m, in.uv - in.lineA) / dot(m, m);
    float d;
    if (t0 <= 0) {
        d = length(in.uv - in.lineA) / radius;
    } else if (t0 > 0 && t0 < 1) {
        float2 intersectPt = in.lineA + t0 * m;
        d = length(in.uv - intersectPt) / radius;
    } else {
        d = length(in.uv - in.lineB) / radius;
    }

    if (d >= 1) {
        discard_fragment();
    }

    return color;
}

// Line Group


struct LineStyling {
    float width;
    float4 color;
    char widthAsPixels;
    float opacity;
    char capType;
    char numDashValues;
    float dashArray[8];
};

/**

 var numDashValues: char

 var dashArray: [Float]
 */

vertex LineVertexOut
lineGroupVertexShader(const LineVertexIn vertexIn [[stage_in]],
                 constant float4x4 &mvpMatrix [[buffer(1)]],
                 constant float &scalingFactor [[buffer(2)]],
                 constant LineStyling *styling [[buffer(3)]])
{
    // extend position in width direction and in lenght direction by width / 2.0
    float width = styling[vertexIn.stylingIndex].width / 2;
    if (styling[vertexIn.stylingIndex].widthAsPixels) {
        width *= scalingFactor;
    }

    float4 extendedPosition = float4(vertexIn.position.xy, 0.0, 1.0) + float4((vertexIn.lenghtNormal + vertexIn.widthNormal).xy, 0.0,0.0)
            * float4(width, width, width, 0.0);

    LineVertexOut out {
        .position = mvpMatrix * extendedPosition,
        .uv = extendedPosition.xy,
        .lineA = (extendedPosition.xy - vertexIn.lineA),
        .lineB = vertexIn.lineB - vertexIn.lineA,
        .stylingIndex = vertexIn.stylingIndex,
        .width = width,
        .segmentType = vertexIn.segmentType,
        .lenghtPrefix = vertexIn.lenghtPrefix,
    };

    return out;
}

fragment float4
lineGroupFragmentShader(LineVertexOut in [[stage_in]],
                        constant LineStyling *styling [[buffer(1)]])
{
    half lineLength = length(in.lineB);
    half t = half(dot(in.lineA, normalize(in.lineB)) / lineLength);
    half d;
    LineStyling style = styling[in.stylingIndex];
    char capType = style.capType;
    char segmentType = in.segmentType;
    if (t < 0.0 || t > 1.0) {
        if (segmentType == 0 || capType == 1 || (segmentType == 2 && t < 0.0) || (segmentType == 1 && t > 1.0)) {
            d = half(min(length(in.lineA), length(in.lineA - in.lineB)));
        } else if (capType == 2) {
            half dLen = t < 0.0 ? -t * lineLength : (t - 1.0) * lineLength;
            float2 intersectPt = t * in.lineB;
            half dOrth = abs(length(in.lineA - intersectPt));
            d = max(dLen, dOrth);
        } else {
            d = 0;
            discard_fragment();
        }
    } else {
        float2 intersectPt = t * in.lineB;
        d = abs(length(in.lineA - intersectPt));
    }

    if (d > in.width) {
        discard_fragment();
    }

    if (style.numDashValues > 0) {
        half factorToT = (in.width * 2) / lineLength;
        half dashTotal = style.dashArray[7] * factorToT;
        half startOffsetSegment = fmod(half(in.lenghtPrefix) / lineLength, dashTotal);
        half intraDashPos = fmod(t + startOffsetSegment, dashTotal);

        if ((intraDashPos > style.dashArray[0] * factorToT && intraDashPos < style.dashArray[1] * factorToT) ||
            (intraDashPos > style.dashArray[2] * factorToT && intraDashPos < style.dashArray[3] * factorToT) ||
            (intraDashPos > style.dashArray[4] * factorToT && intraDashPos < style.dashArray[5] * factorToT) ||
            (intraDashPos > style.dashArray[6] * factorToT && intraDashPos < style.dashArray[7] * factorToT)) {
            discard_fragment();
        }
    }

    return style.color * style.opacity;

}
