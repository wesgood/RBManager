//
//  StampMessage.h
//  YardBot
//
//  Created by Wes Goodhoofd on 2/11/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBMessage.h"

@interface StampMessage : RBMessage {
    NSNumber * secs;
    NSNumber * nsecs;
}

@property (nonatomic, strong) NSNumber * secs;
@property (nonatomic, strong) NSNumber * nsecs;

-(NSDate*)date;
@end
