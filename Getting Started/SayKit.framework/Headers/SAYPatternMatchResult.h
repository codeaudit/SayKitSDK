//
//  SAYPatternMatchResult.h
//  SayKit
//
//  Created by Adam Larsen on 2015/11/03.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SAYPatternMatchResult : NSObject

NS_ASSUME_NONNULL_BEGIN

@property (nonatomic, copy, readonly) NSDictionary *entities;
@property (nonatomic, strong, readonly, nullable) NSError *error;
@property (nonatomic, copy, readonly, nullable) NSString *transcription;

- (instancetype)initWithEntities:(NSDictionary *)entities andTranscription:(NSString *)transcription NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithError:(NSError *)error NS_DESIGNATED_INITIALIZER;

// Use `initWithEntities:andTranscription:` or `initWithError:` instead.
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
