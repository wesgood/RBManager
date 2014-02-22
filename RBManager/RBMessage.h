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

/*!
 * Assign values from a dictionary to the object properties
 * \param messageData dictionary of key-values
 */
-(void)process:(NSDictionary*)messageData;
/*!
 * Do any additional processing when the object is created.
 */
-(void)load;
/*!
 * Populate the message object with default values
 */
-(void)setDefaults;
/*!
 * Generate a dictionary from the properties of this object
 * \returns NSDictionary representation of the message
 */
-(NSDictionary*)publish;

-(NSArray*)propertyKeys;

@end
