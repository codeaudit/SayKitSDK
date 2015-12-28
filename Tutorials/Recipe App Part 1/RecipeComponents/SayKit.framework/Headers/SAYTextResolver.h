//
//  SAYTextResolver.h
//  SayKit
//
//  Created by Adam Larsen on 2015/12/11.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SAYCommandProcessingTypes.h"

NS_ASSUME_NONNULL_BEGIN

@protocol SAYTextResolver <NSObject>

@property (nonatomic, copy, readonly) SAYTextResolverBlock resolverBlock;

@end

NS_ASSUME_NONNULL_END
