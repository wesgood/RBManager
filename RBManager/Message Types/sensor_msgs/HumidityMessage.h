//
//  HumidityMessage.h
//  YardBot
//
//  Created by Wes Goodhoofd on 2/20/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBMessage.h"

@class HeaderMessage;
@interface HumidityMessage : RBMessage {
    HeaderMessage * header;
    
    NSNumber * relative_humidity;
    NSNumber * variance;
}

@property (nonatomic, strong) HeaderMessage * header;
@property (nonatomic, strong) NSNumber * relative_humidity;
@property (nonatomic, strong) NSNumber * variance;

@end
