//
//  RBServiceCall.h
//  YardBot
//
//  Created by Wes Goodhoofd on 1/11/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import <Foundation/Foundation.h>
@class RBManager;
@class RBMessage;

@interface RBServiceCall : NSObject {
    RBManager * manager;
    NSString * service;
    NSString * serviceId;
    id args;
    NSInteger fragmentSize;
    NSString * compression;
    NSDictionary * response;
    BOOL result;
    
    SEL serviceSelector;
    id serviceObject;
    Class messageClass;
    
    NSString * label;
}

@property (nonatomic, strong) RBManager * manager;
@property (nonatomic, strong) NSString * service;
@property (nonatomic, strong) NSString * serviceId;
@property (nonatomic, strong) id args;
@property NSInteger fragmentSize;
@property (nonatomic, strong) NSString * compression;
@property (nonatomic, strong) NSDictionary * response;
@property (nonatomic) SEL serviceSelector;
@property (nonatomic, strong) id serviceObject;
@property (nonatomic, assign) Class messageClass;
@property (nonatomic, strong) NSString * label;
@property BOOL result;


/*!
 * Send a service call to ROSBridge
 */
-(void)send;
/*!
 * Process a return message from ROS
 * \param data the dictionary or array data to process
 */
-(void)receive:(id)data;
/*!
 * Set a message to be sent with the service call
 * \param message the ROS message object to include
 */
-(void)setMessage:(RBMessage*)message;

@end
