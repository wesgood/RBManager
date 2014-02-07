//
//  RBMessage.m
//  YardBot
//
//  Created by Wes Goodhoofd on 1/9/2014.
//  Copyright (c) 2014 Wes Goodhoofd. All rights reserved.
//

#import "RBMessage.h"
#import <objc/runtime.h>

@implementation RBMessage
@synthesize publishDate;

-(id)init {
    self = [super init];
    if (self) {
        [self setDefaults];
    }
    return self;
}

-(void)process:(NSDictionary*)messageData {
    // put dictionary values into object
    self.publishDate = [NSDate date];
    
    for (NSString * key in [messageData allKeys]) {
        id value = [messageData objectForKey:key];
        
        id objectProperty = [self valueForKey:key];
        if ([objectProperty isKindOfClass:[RBMessage class]])
            [objectProperty process:value];
        else
            [self setValue:value forKey:key];
    }
    
    [self load];
}

-(void)load {
    // override when the message is populated
}
-(void)setDefaults {
    // assign default values to certain properties
}

/* usually overridden */
-(NSDictionary*)publish {
    NSMutableDictionary * data = [[NSMutableDictionary alloc] init];
    NSArray * properties = [self propertyKeys];
    
    for (NSString* key in properties) {
        id object = [self valueForKey:key];
        if ([object isKindOfClass:[RBMessage class]])
            [data setObject:[(RBMessage*)object publish] forKey:key];
        else if (object)
            [data setObject:object forKey:key];
    }
    return data;
}

-(NSArray*)propertyKeys {
    unsigned count;
    objc_property_t *properties = class_copyPropertyList([self class], &count);
    
    NSMutableArray *rv = [NSMutableArray array];
    
    unsigned i;
    for (i = 0; i < count; i++)
    {
        objc_property_t property = properties[i];
        NSString *name = [NSString stringWithUTF8String:property_getName(property)];
        [rv addObject:name];
    }
    
    free(properties);
    
    return rv;
}
@end
