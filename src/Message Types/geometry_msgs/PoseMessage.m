//
//  PoseMessage.m
//  YardBot
//
//  Created by Wes Goodhoofd on 1/12/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "PoseMessage.h"

@implementation PoseMessage
@synthesize angular_velocity, linear_velocity, theta, x, y;

-(NSDictionary*)publish {
    NSMutableDictionary * data = [[NSMutableDictionary alloc] init];
    [self addObject:self.x withKey:@"x" toDictionary:data];
    [self addObject:self.y withKey:@"y" toDictionary:data];
    [self addObject:self.theta withKey:@"theta" toDictionary:data];
    
    [self addObject:self.linear_velocity withKey:@"linear_velocity" toDictionary:data];
    [self addObject:self.angular_velocity withKey:@"angular_velocity" toDictionary:data];
    
    return data;
}

-(NSString*)getMessageType {
    return @"geometry_msgs/Pose2D";
}

@end
