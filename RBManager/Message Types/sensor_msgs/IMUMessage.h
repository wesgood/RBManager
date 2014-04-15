//
//  IMUMessage.h
//  YardBot
//
//  Created by Wes Goodhoofd on 2/20/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBMessage.h"
#import "HeaderMessage.h"
#import "QuaternionMessage.h"
#import "VectorMessage.h"

@interface IMUMessage : RBMessage {
    HeaderMessage * header;
    
    QuaternionMessage * orientation;
    NSArray * orientation_covariance;
    
    VectorMessage * angular_velocity;
    NSArray * angular_velocity_covariance;
    
    VectorMessage * linear_acceleration;
    NSArray * linear_acceleration_covariance;
}

@property (nonatomic, strong) HeaderMessage * header;
@property (nonatomic, strong) QuaternionMessage * orientation;
@property (nonatomic, strong) NSArray * orientation_covariance;
@property (nonatomic, strong) VectorMessage * angular_velocity;
@property (nonatomic, strong) NSArray * angular_velocity_covariance;
@property (nonatomic, strong) VectorMessage * linear_acceleration;
@property (nonatomic, strong) NSArray * linear_acceleration_covariance;

@end
