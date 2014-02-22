//
//  RBPublisher.m
//  YardBot
//
//  Created by Wes Goodhoofd on 1/10/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBPublisher.h"
#import "RBManager.h"
#import "RBMessage.h"

@implementation RBPublisher
@synthesize manager, topic, messageType, publisherId, active, label;

-(void)publish:(RBMessage*)message {
    NSDictionary * messageData = [message publish];
    NSAssert(messageData != nil, @"Message data cannot be null");
    
    NSMutableDictionary * data = [[NSMutableDictionary alloc] initWithObjectsAndKeys:
                           @"publish", @"op",
                           [message publish], @"msg",
                           self.topic, @"topic",
                           nil];
    if (self.publisherId)
        [data setObject:self.publisherId forKey:@"id"];
    
    message.publishDate = [NSDate date];
    self.manager.lastPublishedMessage = message;
    [self.manager sendData:data];
}

/*!
 * Provides default advertising of topic without a message ID
 */
-(void)advertise {
    self.active = YES;
    NSMutableDictionary * data = [[NSMutableDictionary alloc] initWithObjectsAndKeys:
                                  @"advertise", @"op",
                                  self.messageType, @"type",
                                  self.topic, @"topic",
                                  nil];
    if (self.publisherId)
        [data setObject:self.publisherId forKey:@"id"];
    
    [self.manager sendData:data];
}

-(void)unadvertise {
    self.active = NO;
    NSMutableDictionary * data = [[NSMutableDictionary alloc] initWithObjectsAndKeys:
                                  @"unadvertise", @"op",
                                  self.topic, @"topic",
                                  nil];
    if (self.publisherId)
        [data setObject:self.publisherId forKey:@"id"];
    
    [self.manager sendData:data];
}

@end
