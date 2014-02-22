//
//  RBManager.m
//  YardBot
//
//  Created by Wes Goodhoofd on 1/9/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBManager.h"
#import "RBSubscriber.h"
#import "RBMessage.h"
#import "RBPublisher.h"
#import "RBServiceCall.h"

static RBManager * sharedInstance;

@implementation RBManager
@synthesize subscribers, publishers, host, socket, delegate, connected, queue, lastReceivedMessage, lastPublishedMessage, lastServiceCall, timeout, timeoutTimer;

+(void) initialize {
    sharedInstance = [[RBManager alloc] init];
}

+(RBManager*) defaultManager {
    return sharedInstance;
}

-(id)init {
    self = [super init];
    if (self) {
        self.subscribers = [[NSMutableArray alloc] init];
        self.publishers = [[NSMutableArray alloc] init];
        self.queue = [[NSMutableArray alloc] init];
        self.connected = NO;
        self.timeout = 5;
    }
    return self;
}

-(RBSubscriber*)addSubscriber:(NSString*)topic responseTarget:(id)subscriberObject selector:(SEL)subscriberSelector messageClass:(Class)messageClass {
    RBSubscriber * subscriber = [[RBSubscriber alloc] init];
    subscriber.manager = self;
    subscriber.subscriberObject = subscriberObject;
    subscriber.subscriberSelector = subscriberSelector;
    subscriber.topic = topic;
    subscriber.messageClass = messageClass;
    subscriber.active = YES;
    
    [self.subscribers addObject:subscriber];
    return subscriber;
}

-(RBPublisher*)addPublisher:(NSString*)topic messageType:(NSString*)message {
    RBPublisher * publisher = [[RBPublisher alloc] init];
    publisher.manager = self;
    publisher.topic = topic;
    publisher.active = YES;
    
    // get the message type from the object
    publisher.messageType = message;
    
    [self.publishers addObject:publisher];
    return publisher;
}

-(RBServiceCall*)makeServiceCall:(NSString*)service responseTarget:(id)serviceCallObject selector:(SEL)serviceSelector {
    RBServiceCall * serviceCall = [[RBServiceCall alloc] init];
    serviceCall.manager = self;
    serviceCall.service = service;
    serviceCall.serviceSelector = serviceSelector;
    serviceCall.serviceObject = serviceCallObject;
    
    return serviceCall;
}

-(RBServiceCall*)setParam:(NSString*)name value:(id)value {
    RBServiceCall * serviceCall = [[RBServiceCall alloc] init];
    serviceCall.manager = self;
    serviceCall.service = @"/rosapi/set_param";
    serviceCall.args = [NSArray arrayWithObjects:name, value, nil];
    
    return serviceCall;
}

-(RBServiceCall*)getParam:(NSString*)name responseTarget:(id)object selector:(SEL)responseSelector {
    RBServiceCall * serviceCall = [[RBServiceCall alloc] init];
    serviceCall.manager = self;
    serviceCall.service = @"/rosapi/get_param";
    serviceCall.serviceObject = object;
    serviceCall.serviceSelector = responseSelector;
    
    return serviceCall;
}

-(void)addExistingSubscriber:(RBSubscriber*)subscriber {
    [subscriber subscribe];
}
-(void)addExistingPublisher:(RBPublisher*)publisher {
    [publisher advertise];
}

-(void)removeSubscriber:(RBSubscriber *)subscriber {
    [subscriber unsubscribe];
}

-(void)removePublisher:(RBPublisher*)publisher {
    [publisher unadvertise];
}

-(void)connect:(NSString *)socketHost {
    if (self.connected || self.socket) {
    #ifdef DEBUG
        NSLog(@"Socket already open");
    #endif
    } else {
#ifdef DEBUG
        NSLog(@"connecting -- %@", socketHost);
#endif
        
        // set the timeout timer
        timeoutTimer = [NSTimer scheduledTimerWithTimeInterval:self.timeout target:self selector:@selector(didTimeout) userInfo:nil repeats:NO];
        
        // open the socket and can't change host while connected
        self.host = socketHost;
        NSURLRequest * request = [NSURLRequest requestWithURL:[NSURL URLWithString:socketHost]];
        self.socket = [[SRWebSocket alloc] initWithURLRequest:request];
        self.socket.delegate = self;
        [self.socket open];
    }
}

-(void)didTimeout {
#ifdef DEBUG
    NSLog(@"timeout");
#endif
    
    self.connected = NO;
    self.socket = nil;
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"rbmanager/timeout" object:nil];
    if ([self.delegate respondsToSelector:@selector(managerDidTimeout:)])
        [self.delegate managerDidTimeout:self];
}

-(void)disconnect {
    [self.socket close];
}

-(void)sendData:(NSDictionary*)data {
    // send the preformatted dictionary through the socket
    #ifdef DEBUG
    NSLog(@"sending -- %@", data);
    #endif
    
    NSError * jsonError = nil;
    NSData * jsonDictionary = [NSJSONSerialization dataWithJSONObject:data options:0 error:&jsonError];
    
    if (jsonError)
        NSLog(@"JSON error -- %@", [jsonError localizedDescription]);
    else {
        [self.socket send:jsonDictionary];
    }
}

-(void)postSubscriberData:(NSDictionary *)data {
    // post to subscribers
    NSDictionary * msg = [data objectForKey:@"msg"];
    NSString * topic = [data objectForKey:@"topic"];
    for (RBSubscriber * subscriber in self.subscribers) {
        // compare the JSON message with the subscriber
        if ((subscriber.subscriberId != nil && [subscriber.subscriberId isEqualToString:[data objectForKey:@"id"]] && [subscriber.topic isEqualToString:topic]) || [subscriber.topic isEqualToString:topic]) {
            RBMessage * message = [[subscriber.messageClass alloc] init];
            [message process:msg];
            
            if ([subscriber.subscriberObject respondsToSelector:subscriber.subscriberSelector])
                [subscriber.subscriberObject performSelectorOnMainThread:subscriber.subscriberSelector withObject:message waitUntilDone:YES];
        }
    }
}

-(void)postServiceCallResponse:(NSDictionary *)data {
    if (self.lastServiceCall) {
        [self.lastServiceCall receive:data];
        
        if ([self.lastServiceCall.serviceObject respondsToSelector:self.lastServiceCall.serviceSelector]) {
            [self.lastServiceCall.serviceObject performSelectorOnMainThread:self.lastServiceCall.serviceSelector withObject:self.lastServiceCall waitUntilDone:YES];
        }
    }
}

-(void)advertisePublishers {
    for (RBPublisher * publisher in self.publishers) {
        if (publisher.active)
            [publisher advertise];
    }
}

-(void)attachSubscribers {
    for (RBSubscriber * subscriber in self.subscribers) {
        if (subscriber.active)
            [subscriber subscribe];
    }
}

#pragma mark SocketRocket Delegate
-(void)webSocket:(SRWebSocket *)webSocket didReceiveMessage:(id)message {
#ifdef DEBUG
    NSLog(@"received -- %@", message);
#endif
    
    // process the message from JSON
    NSError * error = nil;
    NSData * data = [message dataUsingEncoding:NSUTF8StringEncoding];
    NSDictionary * response = [NSJSONSerialization JSONObjectWithData:data options:0 error:&error];
    if (error)
        NSLog(@"JSON error -- %@", [error localizedDescription]);
    else {
        // check for service call
        NSString * op = [response objectForKey:@"op"];
        if ([op isEqualToString:@"publish"])
            [self postSubscriberData:response];
        else if ([op isEqualToString:@"service_response"])
            [self postServiceCallResponse:response];
    }
}

-(void)webSocket:(SRWebSocket *)webSocket didCloseWithCode:(NSInteger)code reason:(NSString *)reason wasClean:(BOOL)wasClean {
#ifdef DEBUG
    NSLog(@"Socket closed -- %@ -- Code %d -- %@", [webSocket.url description], code, reason);
#endif
    self.connected = NO;
    self.socket = nil;
    [[NSNotificationCenter defaultCenter] postNotificationName:@"rbmanager/disconnected" object:nil];
    if ([self.delegate respondsToSelector:@selector(manager:didCloseWithCode:reason:wasClean:)])
        [self.delegate manager:self didCloseWithCode:code reason:reason wasClean:wasClean];
}

-(void)webSocket:(SRWebSocket *)webSocket didFailWithError:(NSError *)error {
#ifdef DEBUG
    NSLog(@"Socket failed -- %@ -- %@", [webSocket.url description], [error localizedDescription]);
#endif
    self.connected = NO;
    self.socket = nil;
    [[NSNotificationCenter defaultCenter] postNotificationName:@"rbmanager/disconnected" object:nil];
    if ([self.delegate respondsToSelector:@selector(manager:didFailWithError:)])
        [self.delegate manager:self didFailWithError:error];
}

-(void)webSocketDidOpen:(SRWebSocket *)webSocket {
#ifdef DEBUG
    NSLog(@"Socket open -- %@", [webSocket.url description]);
#endif
    
    [self.timeoutTimer invalidate];
    self.timeoutTimer = nil;
    
    self.connected = YES;
    [self advertisePublishers];
    [self attachSubscribers];
    [[NSNotificationCenter defaultCenter] postNotificationName:@"rbmanager/connected" object:nil];
    if ([self.delegate respondsToSelector:@selector(managerDidConnect:)])
        [self.delegate managerDidConnect:self];
}
@end
