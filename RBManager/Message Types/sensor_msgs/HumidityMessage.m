//
//  HumidityMessage.m
//  YardBot
//
//  Created by Wes Goodhoofd on 2/20/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "HumidityMessage.h"
#import "HeaderMessage.h"

@implementation HumidityMessage
@synthesize header, relative_humidity, variance;

-(void)setDefaults {
    self.header = [[HeaderMessage alloc] init];
}

@end
