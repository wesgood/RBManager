//
//  RBMessage.h
//  YardBot
//
//  Created by Wes Goodhoofd on 1/9/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RBMessage : NSObject {
    NSDate * publishDate;
    NSString * messageType;
}

@property (nonatomic, strong) NSDate * publishDate;
@property (nonatomic, strong) NSString * messageType;

-(void)process:(NSDictionary*)messageData;
-(NSDictionary*)publish;
-(void)load;
-(void)create;
-(void)addObject:(id)object withKey:(NSString*)key toDictionary:(NSMutableDictionary*)dictionary;

-(NSArray*)propertyKeys;
-(NSString*)getMessageType;

@end
