//
//  RBPublisher.h
//  YardBot
//
//  Created by Wes Goodhoofd on 1/10/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import <Foundation/Foundation.h>
@class RBManager;
@class RBMessage;

@interface RBPublisher : NSObject {
    RBManager * manager;
    NSString * topic;
    NSString * messageType;
    NSString * publisherId;
    
    BOOL active;
    
    NSString * label;
}

@property (nonatomic, strong) RBManager * manager;
@property (nonatomic, strong) NSString * topic;
@property (nonatomic, strong) NSString * messageType;
@property (nonatomic, strong) NSString * publisherId;
@property (nonatomic, strong) NSString * label;
@property BOOL active;

/*!
 * Send a message object to ROS
 * \param message the ROS message object
 */
-(void)publish:(RBMessage*)message;
/*!
 * Advertise this publisher with ROS
 */
-(void)advertise;
/*!
 * Unadvertise this publisher from ROS
 */
-(void)unadvertise;
@end
