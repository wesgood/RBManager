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
}

@property (nonatomic, strong) NSDate * publishDate;

-(void)process:(NSDictionary*)messageData;

-(void)load;
-(void)setDefaults;

-(NSDictionary*)publish;

-(NSArray*)propertyKeys;

@end
