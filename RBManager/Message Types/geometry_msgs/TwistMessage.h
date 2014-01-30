//
//  TwistMessage.h
//  YardBot
//
//  Created by Wes Goodhoofd on 1/11/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBMessage.h"
#import "VectorMessage.h"

@interface TwistMessage : RBMessage {
    VectorMessage * linear;
    VectorMessage * angular;
}

@property (nonatomic, strong) VectorMessage * linear;
@property (nonatomic, strong) VectorMessage * angular;

@end
