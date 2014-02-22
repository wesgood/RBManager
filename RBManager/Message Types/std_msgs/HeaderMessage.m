//
//  HeaderMessage.m
//  YardBot
//
//  Created by Wes Goodhoofd on 2/11/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "HeaderMessage.h"

@implementation HeaderMessage
@synthesize frame_id, seq, stamp;

-(void)setDefaults {
    self.stamp = [[StampMessage alloc] init];
}
@end
