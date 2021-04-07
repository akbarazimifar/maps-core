// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from graphicsobjects.djinni

#import "MCLineShaderProgramInterface.h"
#import "MCShaderProgramInterface.h"
#import <Foundation/Foundation.h>
@protocol MCLine2dInterface;
@protocol MCPolygon2dInterface;
@protocol MCQuad2dInterface;


@protocol MCGraphicsObjectFactoryInterface

- (nullable id<MCQuad2dInterface>)createQuad:(nullable id<MCShaderProgramInterface>)shader;

- (nullable id<MCLine2dInterface>)createLine:(nullable id<MCLineShaderProgramInterface>)lineShader;

- (nullable id<MCPolygon2dInterface>)createPolygon:(nullable id<MCShaderProgramInterface>)shader;

- (nullable id<MCQuad2dInterface>)createQuadMask;

- (nullable id<MCPolygon2dInterface>)createPolygonMask;

@end
