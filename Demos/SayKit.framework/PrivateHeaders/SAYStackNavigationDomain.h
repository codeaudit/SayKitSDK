//
//  SAYStackNavigationDomain.h
//  SayKit
//
//  Created by Adam Larsen on 2015/10/27.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SAYVoiceDomain.h"

@class SAYVoiceIntentResolver;

NS_ASSUME_NONNULL_BEGIN

@interface SAYStackNavigationDomain : NSObject <SAYVoiceDomain>

+ (NSArray<SAYVoiceIntentResolver *> *)voiceIntentResolvers;

@end

NS_ASSUME_NONNULL_END
