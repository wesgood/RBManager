//
//  TwistMessage.m
//  YardBot
//
//  Created by Wes Goodhoofd on 1/11/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "TwistMessage.h"

@implementation TwistMessage
@synthesize linear, angular;

-(void)create {
    self.linear = [[VectorMessage alloc] init];
    self.angular = [[VectorMessage alloc] init];
}

-(NSDictionary*)publish {
    NSDictionary * data = [[NSDictionary alloc] initWithObjectsAndKeys:
                           [self.linear publish], @"linear",
                           [self.angular publish], @"angular",
                           nil];
    return data;
}

-(NSString*)getMessageType {
    return @"geometry_msgs/Twist";
}

@end
