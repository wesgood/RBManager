//
//  VectorMessage.m
//  YardBot
//
//  Created by Wes Goodhoofd on 1/11/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "VectorMessage.h"

@implementation VectorMessage
@synthesize x, y, z;

-(NSDictionary*)publish {
    NSMutableDictionary * data = [[NSMutableDictionary alloc] init];
    [self addObject:self.x withKey:@"x" toDictionary:data];
    [self addObject:self.y withKey:@"y" toDictionary:data];
    [self addObject:self.z withKey:@"z" toDictionary:data];
    return data;
}

-(NSString*)getMessageType {
    return @"geometry_msgs/Vector3";
}
@end
