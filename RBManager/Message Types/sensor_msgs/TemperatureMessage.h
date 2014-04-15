//
//  TemperatureMessage.h
//  YardBot
//
//  Created by Wes Goodhoofd on 2/20/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBMessage.h"
@class HeaderMessage;

@interface TemperatureMessage : RBMessage {
    HeaderMessage * header;
    
    NSNumber * temperature;
    NSNumber * variance;
}

@property (nonatomic, strong) HeaderMessage * header;
@property (nonatomic, strong) NSNumber * temperature;
@property (nonatomic, strong) NSNumber * variance;

@end
