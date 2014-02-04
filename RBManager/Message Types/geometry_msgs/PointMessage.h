//
//  PointMessage.h
//  YardBot
//
//  Created by Wes Goodhoofd on 2/3/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBMessage.h"

@interface PointMessage : RBMessage {
    NSNumber * x;
    NSNumber * y;
    NSNumber * z;
}

@property (nonatomic, strong) NSNumber * x;
@property (nonatomic, strong) NSNumber * y;
@property (nonatomic, strong) NSNumber * z;

@end
