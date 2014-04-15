//
//  TemperatureMessage.m
//  YardBot
//
//  Created by Wes Goodhoofd on 2/20/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "TemperatureMessage.h"
#import "HeaderMessage.h"

@implementation TemperatureMessage
@synthesize header, temperature, variance;

-(void)setDefaults {
    self.header = [[HeaderMessage alloc] init];
}
@end
