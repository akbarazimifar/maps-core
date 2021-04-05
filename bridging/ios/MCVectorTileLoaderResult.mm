// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from loader.djinni

#import "MCVectorTileLoaderResult.h"


@implementation MCVectorTileLoaderResult

- (nonnull instancetype)initWithData:(nullable id<MCVectorTileHolderInterface>)data
                              status:(MCLoaderStatus)status
{
    if (self = [super init]) {
        _data = data;
        _status = status;
    }
    return self;
}

+ (nonnull instancetype)vectorTileLoaderResultWithData:(nullable id<MCVectorTileHolderInterface>)data
                                                status:(MCLoaderStatus)status
{
    return [(MCVectorTileLoaderResult*)[self alloc] initWithData:data
                                                          status:status];
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"<%@ %p data:%@ status:%@>", self.class, (void *)self, self.data, @(self.status)];
}

@end
