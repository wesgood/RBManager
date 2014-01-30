//
//  RBManager.h
//  YardBot
//
//  Created by Wes Goodhoofd on 1/9/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SRWebSocket.h"

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
@property BOOL connected;

+(RBManager*)defaultManager;

// public
-(void)connect:(NSString*)socketHost;
-(void)disconnect;
-(RBSubscriber*)addSubscriber:(id)subscriberObject selector:(SEL)subscriberSelector name:(NSString*)topic messageClass:(Class)messageClass;
-(RBPublisher*)addPublisher:(NSString*)topic messageType:(NSString*)messageType;
-(RBServiceCall*)makeServiceCall:(id)serviceCallObject selector:(SEL)serviceSelector name:(NSString*)service;
-(RBServiceCall*)setParam:(NSString*)name value:(NSString*)value;
-(RBServiceCall*)getParam:(NSString*)name object:(id)object selector:(SEL)responseSelector;

-(void)addExistingSubscriber:(RBSubscriber*)subscriber;
-(void)addExistingPublisher:(RBPublisher*)publisher;
-(void)addExistingServiceCall:(RBServiceCall*)serviceCall;
-(void)removeSubscriber:(RBSubscriber*)subscriber;
-(void)removePublisher:(RBPublisher*)publisher;
-(void)removeServiceCall:(RBServiceCall*)serviceCall;

// private
-(void)postServiceCallResponse:(NSDictionary*)data;
-(void)postSubscriberData:(NSDictionary*)data;
-(void)advertisePublishers;
-(void)attachSubscribers;
/*!
 * Use the web socket to send data to ROS
 * \param data The data to send
 */
-(void)sendData:(NSDictionary*)data;
@end

@protocol RBManagerDelegate <NSObject>
@optional
-(void)managerDidConnect:(RBManager*)manager;
-(void)manager:(RBManager*)manager didFailWithError:(NSError*)error;
-(void)manager:(RBManager*)manager didCloseWithCode:(NSInteger)code reason:(NSString *)reason wasClean:(BOOL)wasClean;

@end