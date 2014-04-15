//
//  LogMessage.h
//  YardBot
//
//  Created by Wes Goodhoofd on 2014-04-13.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBMessage.h"
#import "HeaderMessage.h"

typedef enum {
    debug = 1,
    info = 2,
    warn = 4,
    error = 8,
    fatal = 16
} VerbosityLevel;

@interface LogMessage : RBMessage {
    HeaderMessage * header;
    VerbosityLevel level;
    NSString * name;
    NSString * msg;
    NSString * file;
    NSString * function;
    NSInteger line;
    NSArray * topics;
}

@property (nonatomic, strong) HeaderMessage * header;
@property (nonatomic, strong) NSString * name;
@property (nonatomic, strong) NSString * msg;
@property (nonatomic, strong) NSString * file;
@property (nonatomic, strong) NSString * function;
@property (nonatomic, strong) NSArray * topics;
@property VerbosityLevel level;
@property NSInteger line;

-(NSString*)verbosityLabel;
-(UIColor*)verbosityColour;
@end
