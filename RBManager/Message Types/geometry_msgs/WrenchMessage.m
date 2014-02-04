//
//  WrenchMessage.m
//  YardBot
//
//  Created by Wes Goodhoofd on 2/3/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "WrenchMessage.h"

@implementation WrenchMessage
@synthesize force, torque;

-(void)setDefaults {
    self.force = [[VectorMessage alloc] init];
    self.torque = [[VectorMessage alloc] init];
}
@end
