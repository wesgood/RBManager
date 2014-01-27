//
//  RBServiceCall.m
//  YardBot
//
//  Created by Wes Goodhoofd on 1/11/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBServiceCall.h"
#import "RBManager.h"
#import "RBMessage.h"

@implementation RBServiceCall
@synthesize service, manager, args, compression, fragmentSize, serviceId, response, responseClass, serviceObject, serviceSelector;

-(void)send {
    NSMutableDictionary * data = [[NSMutableDictionary alloc] initWithObjectsAndKeys:
                                  @"call_service", @"op",
                                  self.service, @"service",
                                  nil];
    if (self.serviceId)
        [data setObject:self.serviceId forKey:@"id"];
    if (self.args) {
        [data setObject:self.args forKey:@"args"];
    }
    if (self.compression)
        [data setObject:self.compression forKey:@"compression"];
    if (self.fragmentSize)
        [data setObject:[NSNumber numberWithInteger:self.fragmentSize] forKey:@"fragment_size"];
    
    self.manager.lastServiceCall = self;
    [self.manager sendData:data];
}

-(void)receive:(id)data {
    if (self.responseClass) {
        RBMessage * message = [[self.responseClass alloc] init];
        [message process:data];
        self.response = message;
    } else {
        self.response = data;
    }
}

-(void)setMessage:(RBMessage*)message {
    self.args = [message publish];
}

@end
