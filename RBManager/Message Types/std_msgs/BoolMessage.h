//
//  BoolMessage.h
//  YardBot
//
//  Created by Wes Goodhoofd on 2/3/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBMessage.h"

@interface BoolMessage : RBMessage {
    NSNumber * data;
}
@property (nonatomic, strong) NSNumber * data;

@end
