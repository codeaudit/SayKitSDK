//
//  SAYConversationTopic.h
//  SayKit
//
//  Created by Greg Nicholas on 1/12/16.
//  Copyright © 2016 Conversant Labs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SAYVerbalCommandRegistry.h"
#import "SAYAudioEventSource.h"

@class SAYVerbalCommandRecognizer;
@class SAYAudioTrack;

NS_ASSUME_NONNULL_BEGIN

@interface SAYConversationTopic : NSObject <SAYVerbalCommandRegistry, SAYAudioEventSource>

@property (nonatomic, readonly) NSArray <SAYVerbalCommandRecognizer *> *commandRecognizers;

- (void)addCommandRecognizer:(SAYVerbalCommandRecognizer *)commandRecognizer;
- (void)removeCommandRecognizer:(SAYVerbalCommandRecognizer *)commandRecognizer;

@property (nonatomic, readonly) NSArray <SAYConversationTopic *> *subtopics;

- (void)addSubtopic:(SAYConversationTopic *)topic;
- (void)removeSubtopic:(SAYConversationTopic *)topic;
- (void)removeAllSubtopics;

// Can be called by outside collaborators to cause a topic to say something (e.g. a controller), but it is recommended that a SAYConversationTopic subclass expose methods with more semantic meanings as surrogate for this direct method call.
//  (For example, collaborator would call
//        [topic speakHelpMessage]
//    instead of
//        [topic postEvents:[SAYSpeechEvent eventWithUtteranceString:@"... help message ..."])
- (void)postEvents:(SAYAudioEventSequence *)eventSequence;

// called when a subtopic posts a new audio event. not intended to be used by collaborators, but instead as a subclassing overriding point for topics that want to customize the sequencing of their subtopics' audio out
- (void)subtopic:(SAYConversationTopic *)subtopic
   didPostEventSequence:(SAYAudioEventSequence *)sequence;

@end

NS_ASSUME_NONNULL_END
