//
//  SAYAudioEvent.h
//  SayKit
//
//  Created by Greg Nicholas on 7/1/15.
//  Copyright (c) 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SAYOperation.h"

// TODO: revisit concept of event copying. seems relevant with signal composition

NS_ASSUME_NONNULL_BEGIN

typedef SAYOperation SAYAudioOperation;

/**
 *  A `SAYAudioEvent` represents a piece of audible information to be conveyed to the user.
 */
@protocol SAYAudioEvent <NSObject>

/**
 *  A series of operations that contain the actual logic capable of presenting the event to the user.
 *
 *  @return Array of `SAYAudioOperation` instances
 */
- (NSArray <SAYAudioOperation *> *)operations;

@end

NS_ASSUME_NONNULL_END
