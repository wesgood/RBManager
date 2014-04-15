//
//  NavSatStatusMessage.h
//  YardBot
//
//  Created by Wes Goodhoofd on 2/11/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBMessage.h"

@interface NavSatStatusMessage : RBMessage {
    NSNumber * status;
    NSNumber * service;
}

@property (nonatomic, strong) NSNumber * status;
@property (nonatomic, strong) NSNumber * service;

@end
