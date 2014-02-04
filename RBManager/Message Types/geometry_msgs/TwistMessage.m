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

-(void)setDefaults {
    self.linear = [[VectorMessage alloc] init];
    self.angular = [[VectorMessage alloc] init];
}

@end
