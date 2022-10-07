// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from graphicsobjects.djinni

#import "MCRenderingContextInterface.h"
#import "MCTextDescription.h"
#import <Foundation/Foundation.h>
@protocol MCGraphicsObjectInterface;
@protocol MCTextureHolderInterface;


@protocol MCTextInterface

- (void)setTexts:(nonnull NSArray<MCTextDescription *> *)texts;

- (void)loadTexture:(nullable id<MCRenderingContextInterface>)context
      textureHolder:(nullable id<MCTextureHolderInterface>)textureHolder;

- (void)removeTexture;

- (nullable id<MCGraphicsObjectInterface>)asGraphicsObject;

@end
