// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from coordinate_system.djinni

#import "MCCoord.h"


@implementation MCCoord

- (nonnull instancetype)initWithSystemIdentifier:(nonnull NSString *)systemIdentifier
                                               x:(double)x
                                               y:(double)y
                                               z:(double)z
{
    if (self = [super init]) {
        _systemIdentifier = [systemIdentifier copy];
        _x = x;
        _y = y;
        _z = z;
    }
    return self;
}

+ (nonnull instancetype)coordWithSystemIdentifier:(nonnull NSString *)systemIdentifier
                                                x:(double)x
                                                y:(double)y
                                                z:(double)z
{
    return [[self alloc] initWithSystemIdentifier:systemIdentifier
                                                x:x
                                                y:y
                                                z:z];
}

- (BOOL)isEqual:(id)other
{
    if (![other isKindOfClass:[MCCoord class]]) {
        return NO;
    }
    MCCoord *typedOther = (MCCoord *)other;
    return [self.systemIdentifier isEqualToString:typedOther.systemIdentifier] &&
            self.x == typedOther.x &&
            self.y == typedOther.y &&
            self.z == typedOther.z;
}

- (NSUInteger)hash
{
    return NSStringFromClass([self class]).hash ^
            self.systemIdentifier.hash ^
            (NSUInteger)self.x ^
            (NSUInteger)self.y ^
            (NSUInteger)self.z;
}

- (NSComparisonResult)compare:(MCCoord *)other
{
    NSComparisonResult tempResult;
    tempResult = [self.systemIdentifier compare:other.systemIdentifier];
    if (tempResult != NSOrderedSame) {
        return tempResult;
    }
    if (self.x < other.x) {
        tempResult = NSOrderedAscending;
    } else if (self.x > other.x) {
        tempResult = NSOrderedDescending;
    } else {
        tempResult = NSOrderedSame;
    }
    if (tempResult != NSOrderedSame) {
        return tempResult;
    }
    if (self.y < other.y) {
        tempResult = NSOrderedAscending;
    } else if (self.y > other.y) {
        tempResult = NSOrderedDescending;
    } else {
        tempResult = NSOrderedSame;
    }
    if (tempResult != NSOrderedSame) {
        return tempResult;
    }
    if (self.z < other.z) {
        tempResult = NSOrderedAscending;
    } else if (self.z > other.z) {
        tempResult = NSOrderedDescending;
    } else {
        tempResult = NSOrderedSame;
    }
    if (tempResult != NSOrderedSame) {
        return tempResult;
    }
    return NSOrderedSame;
}

#ifndef DJINNI_DISABLE_DESCRIPTION_METHODS
- (NSString *)description
{
    return [NSString stringWithFormat:@"<%@ %p systemIdentifier:%@ x:%@ y:%@ z:%@>", self.class, (void *)self, self.systemIdentifier, @(self.x), @(self.y), @(self.z)];
}

#endif
@end
