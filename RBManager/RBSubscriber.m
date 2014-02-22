//
//  RBSubscriber.m
//  YardBot
//
//  Created by Wes Goodhoofd on 1/9/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBSubscriber.h"
#import "RBManager.h"
#import "RBMessage.h"

@implementation RBSubscriber
@synthesize messageClass, topic, subscriberObject, subscriberSelector, manager, messageType, subscriberId, active, fragmentSize, compression, queueLength, throttleRate, topicType, label;

-(void)subscribe {
    self.active = YES;
    NSMutableDictionary * data = [[NSMutableDictionary alloc] initWithObjectsAndKeys:
                                  @"subscribe", @"op",
                                  self.topic, @"topic",
                                  nil];
    if (self.messageType)
        [data setObject:self.messageType forKey:@"type"];
    if (self.subscriberId)
        [data setObject:self.subscriberId forKey:@"id"];
    if (self.throttleRate)
        [data setObject:[NSNumber numberWithInteger:self.throttleRate] forKey:@"throttle_rate"];
    if (self.queueLength)
        [data setObject:[NSNumber numberWithInteger:self.queueLength] forKey:@"queue_length"];
    if (self.fragmentSize)
        [data setObject:[NSNumber numberWithInteger:self.fragmentSize] forKey:@"fragment_size"];
    if (self.compression)
        [data setObject:self.compression forKey:@"compression"];
    
    [self.manager sendData:data];
}

-(void)unsubscribe {
    self.active = NO;
    NSMutableDictionary * data = [[NSMutableDictionary alloc] initWithObjectsAndKeys:
                                  @"unsubscribe", @"op",
                                  self.topic, @"topic",
                                  nil];
    if (self.subscriberId)
        [data setObject:self.subscriberId forKey:@"id"];
    [self.manager sendData:data];
}
@end
