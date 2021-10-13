// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from graphicsobjects.djinni

#import "MCGlyphDescription.h"


@implementation MCGlyphDescription

- (nonnull instancetype)initWithFrame:(nonnull MCQuad2dD *)frame
                   textureCoordinates:(nonnull MCQuad2dD *)textureCoordinates
{
    if (self = [super init]) {
        _frame = frame;
        _textureCoordinates = textureCoordinates;
    }
    return self;
}

+ (nonnull instancetype)glyphDescriptionWithFrame:(nonnull MCQuad2dD *)frame
                               textureCoordinates:(nonnull MCQuad2dD *)textureCoordinates
{
    return [(MCGlyphDescription*)[self alloc] initWithFrame:frame
                                         textureCoordinates:textureCoordinates];
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"<%@ %p frame:%@ textureCoordinates:%@>", self.class, (void *)self, self.frame, self.textureCoordinates];
}

@end
