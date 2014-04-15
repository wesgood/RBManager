//
//  LogMessage.m
//  YardBot
//
//  Created by Wes Goodhoofd on 2014-04-13.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "LogMessage.h"

@implementation LogMessage
@synthesize file, function, header, level, line, msg, name, topics;

-(void)setDefaults {
    self.header = [[HeaderMessage alloc] init];
}

-(NSString*)verbosityLabel {
    switch (self.level) {
        case debug:
            return @"DEBUG";
        case info:
            return @"INFO";
        case warn:
            return @"WARN";
        case error:
            return @"ERROR";
        case fatal:
            return @"FATAL";
    }
}

-(UIColor*)verbosityColour {
    switch (self.level) {
        case debug:
            return [UIColor colorWithWhite:0.480 alpha:1.000];
        case info:
            return nil;
        case warn:
            return [UIColor colorWithRed:1.000 green:0.803 blue:0.000 alpha:1.000];
        case error:
            return [UIColor colorWithRed:1.000 green:0.589 blue:0.000 alpha:1.000];
        case fatal:
            return [UIColor colorWithRed:1.000 green:0.208 blue:0.000 alpha:1.000];
    }
}
@end
