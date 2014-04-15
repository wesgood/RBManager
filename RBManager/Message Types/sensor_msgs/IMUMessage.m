//
//  IMUMessage.m
//  YardBot
//
//  Created by Wes Goodhoofd on 2/20/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "IMUMessage.h"

@implementation IMUMessage
@synthesize header, angular_velocity, angular_velocity_covariance, linear_acceleration, linear_acceleration_covariance, orientation, orientation_covariance;

-(void)setDefaults {
    self.header = [[HeaderMessage alloc] init];
    self.angular_velocity = [[VectorMessage alloc] init];
    self.angular_velocity_covariance = [[NSArray alloc] initWithObjects:[NSNumber numberWithInteger:-1], nil];
    self.linear_acceleration = [[VectorMessage alloc] init];
    self.linear_acceleration_covariance = [[NSArray alloc] initWithObjects:[NSNumber numberWithInteger:-1], nil];
    self.orientation = [[QuaternionMessage alloc] init];
    self.orientation_covariance = [[NSArray alloc] initWithObjects:[NSNumber numberWithInteger:-1], nil];
}
@end
