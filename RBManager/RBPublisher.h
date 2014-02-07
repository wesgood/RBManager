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

-(void)publish:(RBMessage*)message;
-(void)advertise;
-(void)unadvertise;
@end
