//
//  PoseMessage.h
//  YardBot
//
//  Created by Wes Goodhoofd on 1/12/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBMessage.h"

@interface PoseMessage : RBMessage {
    NSNumber * x;
    NSNumber * y;
    NSNumber * theta;
    
    NSNumber * linear_velocity;
    NSNumber * angular_velocity;
}

@property (nonatomic, strong) NSNumber * x;
@property (nonatomic, strong) NSNumber * y;
@property (nonatomic, strong) NSNumber * theta;

@property (nonatomic, strong) NSNumber * linear_velocity;
@property (nonatomic, strong) NSNumber * angular_velocity;
@end
