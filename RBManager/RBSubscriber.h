//
//  RBSubscriber.h
//  YardBot
//
//  Created by Wes Goodhoofd on 1/9/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import <Foundation/Foundation.h>
@class RBManager;

@interface RBSubscriber : NSObject {
    RBManager * manager;
    Class messageClass;
    NSString * topic;
    NSString * messageType;
    NSString * subscriberId;
    
    BOOL active;
    
    SEL subscriberSelector;
    id subscriberObject;
    
    // extra parameters
    NSString * topicType;
    NSInteger throttleRate;
    NSInteger queueLength;
    NSInteger fragmentSize;
    NSString * compression;
    
    NSString * label;
}

@property (nonatomic, strong) RBManager * manager;
@property (nonatomic, assign) Class messageClass;
@property (nonatomic, strong) NSString * topic;
@property (nonatomic, strong) NSString * messageType;
@property (nonatomic, strong) NSString * subscriberId;
@property (nonatomic, strong) NSString * topicType;
@property (nonatomic, strong) NSString * label;
@property NSInteger throttleRate;
@property NSInteger queueLength;
@property NSInteger fragmentSize;
@property (nonatomic, strong) NSString * compression;
@property (nonatomic) SEL subscriberSelector;
@property (nonatomic, strong) id subscriberObject;
@property BOOL active;

/*!
 * Subscribe this object to ROS
 */
-(void)subscribe;
/*!
 * Unsubscribe this object from ROS
 */
-(void)unsubscribe;
@end
