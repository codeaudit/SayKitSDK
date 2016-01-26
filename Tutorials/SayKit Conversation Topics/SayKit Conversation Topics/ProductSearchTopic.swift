//
//  ProductSearchTopic.swift
//  RecipeAppPart1
//
//  Created by Adam Larsen on 2016/01/26.
//  Copyright © 2016 Conversant Labs. All rights reserved.
//

import Foundation

class ProductSearchTopic: SAYConversationTopic
{
    let eventHandler: ProductTopicEventHandler
    
    init(eventHandler: ProductTopicEventHandler)
    {
        self.eventHandler = eventHandler
        
        super.init()
        
        // set up the search recognizer
        self.addCommandRecognizer(SAYSearchCommandRecognizer(responseTarget: eventHandler,
            action: "handleSearch:"))
        
        // create the subtopic to handle the list of results
        let listTopic = ProductListTopic(eventHandler: eventHandler)
        
        // by adding it as a subtopic, we are implicitly doing two things:
        // 1. adding its command recognizers to our collection
        // 2. listening for, and passing on, our subtopic's audio events (potentially with modification: see below)
        self.addSubtopic(listTopic)
    }

    // This is a base SAYConversationTopic function that is called to pass on a subtopics'
    // audio events. Override it to modify the message.
    override func subtopic(subtopic: SAYConversationTopic,
        didPostEventSequence incomingSeq: SAYAudioEventSequence) {
            
            // preface the message with this introduction
            let prefaceEvent = SAYSpeechEvent(utteranceString: "Here's what I found matching your query:")
            let outgoingSeq = SAYAudioEventSequence(events:[prefaceEvent])
            
            // the incoming sequence is our subtopic's list of search results
            // add them to our outgoing sequence
            outgoingSeq.appendSequence(incomingSeq)
            
            self.postEvents(outgoingSeq)
    }
}
