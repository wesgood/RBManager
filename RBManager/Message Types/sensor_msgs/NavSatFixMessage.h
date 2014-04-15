//
//  NavSatFixMessage.h
//  YardBot
//
//  Created by Wes Goodhoofd on 2/11/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBMessage.h"
#import "NavSatStatusMessage.h"
#import "HeaderMessage.h"
#import <MapKit/MapKit.h>

@interface NavSatFixMessage : RBMessage {
    NavSatStatusMessage * status;
    HeaderMessage * header;
    
    NSNumber * latitude;
    NSNumber * longitude;
    NSNumber * altitude;
    
    NSArray * position_covariance;
    
    NSNumber * position_covariance_type;
}

@property (nonatomic, strong) NavSatStatusMessage * status;
@property (nonatomic, strong) HeaderMessage * header;
@property (nonatomic, strong) NSNumber * latitude;
@property (nonatomic, strong) NSNumber * longitude;
@property (nonatomic, strong) NSNumber * altitude;
@property (nonatomic, strong) NSArray * position_covariance;
@property (nonatomic, strong) NSNumber * position_covariance_type;

-(CLLocation*)location;
-(CLLocationCoordinate2D)coordinate;
@end
