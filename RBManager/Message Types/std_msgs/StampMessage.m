//
//  StampMessage.m
//  YardBot
//
//  Created by Wes Goodhoofd on 2/11/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "StampMessage.h"

@implementation StampMessage
@synthesize secs, nsecs;

-(NSDate*)date {
    return [NSDate dateWithTimeIntervalSince1970:[self.secs integerValue]];
}
@end
