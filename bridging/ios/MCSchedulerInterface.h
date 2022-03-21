// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from task_scheduler.djinni

#import <Foundation/Foundation.h>
@protocol MCTaskInterface;


@protocol MCSchedulerInterface

- (void)addTask:(nullable id<MCTaskInterface>)task;

- (void)addTasks:(nonnull NSArray<id<MCTaskInterface>> *)tasks;

- (void)removeTask:(nonnull NSString *)id;

- (void)clear;

- (void)pause;

- (void)resume;

@end
