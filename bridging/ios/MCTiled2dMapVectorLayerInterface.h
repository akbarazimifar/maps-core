// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from tiled_vector_layer.djinni

#import "MCLayerInterface.h"
#import "MCTileLoaderInterface.h"
#import "MCTiled2dMapLayerConfig.h"
#import <Foundation/Foundation.h>
@class MCTiled2dMapVectorLayerInterface;


@interface MCTiled2dMapVectorLayerInterface : NSObject

+ (nullable MCTiled2dMapVectorLayerInterface *)create:(nullable id<MCTiled2dMapLayerConfig>)layerConfig
                                           tileLoader:(nullable id<MCTileLoaderInterface>)tileLoader;

- (nullable id<MCLayerInterface>)asLayerInterface;

@end
