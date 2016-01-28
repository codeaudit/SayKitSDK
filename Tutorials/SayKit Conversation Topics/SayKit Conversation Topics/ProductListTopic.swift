//
//  ProductListTopic.swift
//  RecipeAppPart1
//
//  Created by Adam Larsen on 2016/01/26.
//  Copyright © 2016 Conversant Labs. All rights reserved.
//

import Foundation

class ProductListTopic: SAYConversationTopic
{
    let eventHandler: ProductTopicEventHandler
    
    init(eventHandler: ProductTopicEventHandler)
    {
        self.eventHandler = eventHandler
     
        super.init()
        
        // add a recognizer for "play" commands, to begin reading the items in the list
        self.addCommandRecognizer(SAYPlayCommandRecognizer(responseTarget:eventHandler,
            action:"handlePlay"))
        
        // add a recognizer for "previous" commands, to go back in the list
        self.addCommandRecognizer(SAYPreviousCommandRecognizer(responseTarget:eventHandler,
            action:"handlePrevious"))
        
        // add a recognizer to "next" commands, to go forward in the list
        self.addCommandRecognizer(SAYNextCommandRecognizer(responseTarget:eventHandler,
            action:"handleNext"))
        
        // add a recognizer for "select" commands, to select an item in the list
        self.addCommandRecognizer(SAYSelectCommandRecognizer(responseTarget:eventHandler,
            action:"handleSelect"))
    }
    
    func speakProductTitles(titles: [String])
    {
        let sequence = SAYAudioEventSequence()
        for title in titles {
            sequence.addEvent(SAYSpeechEvent(utteranceString: title))
        }
        
        // this is a method defined on the `SAYConversationTopic` base class that posts events to listeners
        self.postEvents(sequence)
    }
}

protocol ProductTopicEventHandler: class
{
    func handlePlay()
    func handlePrevious()
    func handleNext()
    func handleSelect()
    
    func handleSearch(command: SAYCommand)
}
