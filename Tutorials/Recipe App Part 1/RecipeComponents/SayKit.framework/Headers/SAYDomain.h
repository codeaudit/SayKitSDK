//
//  SAYDomain.h
//  SayKit
//
//  Created by Adam Larsen on 2015/12/11.
//  Copyright © 2015 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SAYTextResolver;
@class SAYDomain;

NS_ASSUME_NONNULL_BEGIN

@interface SAYDomain : NSObject

@property (nonatomic, copy, readonly) NSArray<id<SAYTextResolver> > *resolvers;
@property (nonatomic, copy, readonly) NSArray<SAYDomain *> *subdomains;
@property (nonatomic, copy, readonly) NSArray<id<SAYTextResolver> > *subdomainResolvers;

- (void)registerResolver:(id<SAYTextResolver>)resolver;
- (void)registerResolver:(id<SAYTextResolver>)resolver withTag:(NSString *)tag;

- (void)deregisterResolverWithTag:(NSString *)tag;
- (void)deregisterAllResolvers;

- (void)addSubdomain:(SAYDomain *)domain;
- (void)addSubdomain:(SAYDomain *)domain withTag:(NSString *)tag;

- (void)removeSubdomainWithTag:(NSString *)tag;

@end

// basic struct of domain + string tag
@interface SAYTaggedDomain : NSObject

@property (nonatomic, copy, readonly, nullable) NSString *tag;
@property (nonatomic, strong, readonly) SAYDomain *domain;

- (instancetype)initWithTag:(NSString * __nullable)tag domain:(SAYDomain *)domain;

@end

NS_ASSUME_NONNULL_END
