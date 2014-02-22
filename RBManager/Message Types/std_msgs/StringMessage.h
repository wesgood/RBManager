//
//  BoolMessage.h
//  YardBot
//
//  Created by Wes Goodhoofd on 2/3/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBMessage.h"

@interface StringMessage : RBMessage {
    NSString * data;
}
@property (nonatomic, strong) NSString * data;

@end
