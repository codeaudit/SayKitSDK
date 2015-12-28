//
//  SAYDomainRegistry.h
//  SayKit
//
//  Created by Adam Larsen on 2015/12/11.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SAYTextCommandResolver.h"

@class SAYDomain;

NS_ASSUME_NONNULL_BEGIN

@interface SAYDomainRegistry : NSObject <SAYTextCommandResolver>

- (void)addDomain:(SAYDomain *)domain;
- (void)addDomain:(SAYDomain *)domain withTag:(NSString *)tag;

- (void)removeDomainWithTag:(NSString *)tag;
- (void)removeAllDomains;

@end

NS_ASSUME_NONNULL_END
