//
//  LoggerMessage.h
//  YardBot
//
//  Created by Wes Goodhoofd on 2014-04-14.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBMessage.h"

@interface LoggerMessage : RBMessage {
    NSString * level;
    NSString * name;
}

@property (nonatomic, strong) NSString * level;
@property (nonatomic, strong) NSString * name;

@end
