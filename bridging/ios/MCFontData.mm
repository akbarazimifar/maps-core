// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from loader.djinni

#import "MCFontData.h"


@implementation MCFontData

- (nonnull instancetype)initWithInfo:(nonnull MCFontInfo *)info
                              glyphs:(nonnull NSArray<MCFontGlyph *> *)glyphs
{
    if (self = [super init]) {
        _info = info;
        _glyphs = [glyphs copy];
    }
    return self;
}

+ (nonnull instancetype)fontDataWithInfo:(nonnull MCFontInfo *)info
                                  glyphs:(nonnull NSArray<MCFontGlyph *> *)glyphs
{
    return [(MCFontData*)[self alloc] initWithInfo:info
                                            glyphs:glyphs];
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"<%@ %p info:%@ glyphs:%@>", self.class, (void *)self, self.info, self.glyphs];
}

@end
