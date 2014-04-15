//
//  NavSatFixMessage.m
//  YardBot
//
//  Created by Wes Goodhoofd on 2/11/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "NavSatFixMessage.h"

@implementation NavSatFixMessage
@synthesize altitude, latitude, longitude, position_covariance, position_covariance_type, status, header;

-(void)setDefaults {
    self.header = [[HeaderMessage alloc] init];
    self.status = [[NavSatStatusMessage alloc] init];
}

-(CLLocation*)location {
    return [[CLLocation alloc] initWithLatitude:[self.latitude floatValue] longitude:[self.longitude floatValue]];
}
-(CLLocationCoordinate2D)coordinate {
    return CLLocationCoordinate2DMake([self.latitude floatValue], [self.longitude floatValue]);
}
@end
