//
//  RBManager.h
//  YardBot
//
//  Created by Wes Goodhoofd on 1/9/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SRWebSocket.h"

// include the built in messages
#import "PoseMessage.h"
#import "TwistMessage.h"
#import "VectorMessage.h"
#import "PointMessage.h"
#import "WrenchMessage.h"
#import "QuaternionMessage.h"

#import "EmptyMessage.h"
#import "BoolMessage.h"


@class RBSubscriber;
@class RBPublisher;
@class RBMessage;
@class RBServiceCall;

@protocol RBManagerDelegate;

@interface RBManager : NSObject <SRWebSocketDelegate> {
    NSMutableArray * subscribers;
    NSMutableArray * publishers;
    NSMutableArray * queue;
    
    NSString * host;
    SRWebSocket * socket;
    id<RBManagerDelegate> delegate;
    
    BOOL connected;
    NSTimer * timeoutTimer;
    NSInteger timeout;
    
    RBMessage * lastPublishedMessage;
    RBMessage * lastReceivedMessage;
    RBServiceCall * lastServiceCall;
}

@property (nonatomic, strong) NSMutableArray * subscribers;
@property (nonatomic, strong) NSMutableArray * publishers;
@property (nonatomic, strong) NSMutableArray * queue;
@property (nonatomic, strong) NSString * host;
@property (nonatomic, strong) SRWebSocket * socket;
@property (nonatomic, strong) id<RBManagerDelegate> delegate;
@property (nonatomic, strong) RBMessage * lastPublishedMessage;
@property (nonatomic, strong) RBMessage * lastReceivedMessage;
@property (nonatomic, strong) RBServiceCall * lastServiceCall;
@property (nonatomic, strong) NSTimer * timeoutTimer;
@property NSInteger timeout;
@property BOOL connected;

+(RBManager*)defaultManager;

// public
/*!
 * Connect to the specified websocket.
 * \param socketHost the websocket IP
 */
-(void)connect:(NSString*)socketHost;
/*!
 * Disconnect from the currently connected websocket.
 */
-(void)disconnect;
/*!
 * Create a new subscriber object to receive ROS messages.
 * \param subscriberObject the target of the subscriber callback
 * \param subscriberSelector the name of the method to receive the message
 * \param topic the ROS topic to subscribe to
 * \param messageClass the class of the ROS message to populate
 * \returns A new RBSubscriber object
 */
-(RBSubscriber*)addSubscriber:(NSString*)topic responseTarget:(id)subscriberObject selector:(SEL)subscriberSelector messageClass:(Class)messageClass;
/*!
 * Create a new publisher object to send messages to ROS
 * \param topic the ROS topic to publish to
 * \param messageType the type of message ROS is expecting
 * \returns A new RBPublisher object
 */
-(RBPublisher*)addPublisher:(NSString*)topic messageType:(NSString*)message;
/*!
 * Create a new service call object to control ROS
 * \param serviceCallObject the target of the service call callback
 * \param serviceSelector the method that receives the response data
 * \param service the ROS service that receives the request
 * \returns A new RBServiceCall object
 */
-(RBServiceCall*)makeServiceCall:(NSString*)service responseTarget:(id)serviceCallObject selector:(SEL)serviceSelector;
/*!
 * Creates a new service call object preset to set a particular ROS parameter
 * \param name the name of the ROS parameter to update
 * \param value the new value of the parameter
 * \returns A new RBServiceCall object
 */
-(RBServiceCall*)setParam:(NSString*)name value:(id)value;
/*!
 * Creates a new service call object preset to receive a particular ROS parameter
 * \param name the name of the ROS parameter to get
 * \param object the target of the response callback
 * \param responseSelector the method that will receive the callback data
 * \returns A new RBServiceCall object
 */
-(RBServiceCall*)getParam:(NSString*)name responseTarget:(id)object selector:(SEL)responseSelector;

/*!
 * Add a previously made RBSubscriber object to the manager
 * \param subscriber the RBSubscriber object to add in
 */
-(void)addExistingSubscriber:(RBSubscriber*)subscriber;
/*!
 * Add a previously made RBPublisher object to the manager
 * \param publisher the RBPublisher object to add in
 */
-(void)addExistingPublisher:(RBPublisher*)publisher;
/*!
 * Remove a previously made RBSubscriber object from the manager
 * \param subscriber the RBSubscriber object to remove
 */
-(void)removeSubscriber:(RBSubscriber*)subscriber;
/*!
 * Remove a previously made RBPublisher object from the manager
 * \param publisher the RBPublisher object to remove
 */
-(void)removePublisher:(RBPublisher*)publisher;

// private
-(void)postServiceCallResponse:(NSDictionary*)data;
-(void)postSubscriberData:(NSDictionary*)data;
-(void)advertisePublishers;
-(void)attachSubscribers;
-(void)didTimeout;
/*!
 * Use the web socket to send data to ROS
 * \param data The data to send
 */
-(void)sendData:(NSDictionary*)data;
@end

@protocol RBManagerDelegate <NSObject>
@optional
-(void)managerDidConnect:(RBManager*)manager;
-(void)managerDidTimeout:(RBManager*)manager;
-(void)manager:(RBManager*)manager didFailWithError:(NSError*)error;
-(void)manager:(RBManager*)manager didCloseWithCode:(NSInteger)code reason:(NSString *)reason wasClean:(BOOL)wasClean;

@end