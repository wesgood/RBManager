//
//  HeaderMessage.h
//  YardBot
//
//  Created by Wes Goodhoofd on 2/11/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBMessage.h"
#import "StampMessage.h"

@interface HeaderMessage : RBMessage {
    NSString * frame_id;
    NSNumber * seq;
    
    StampMessage * stamp;    
}

@property (nonatomic, strong) NSNumber * seq;
@property (nonatomic, strong) NSString * frame_id;
@property (nonatomic, strong) StampMessage * stamp;

@end
