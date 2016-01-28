//
//  ViewController.swift
//  SayKit Conversation Topics
//
//  Created by Adam Larsen on 2016/01/26.
//  Copyright © 2016 Conversant Labs. All rights reserved.
//

import UIKit

class ViewController: UIViewController, ProductTopicEventHandler {
   
    @IBOutlet weak var appResultLabel: UILabel!
    
    var listTopic: ProductListTopic?    
    
    // MARK: ProductTopicEventHandler Protocol Methods
    
    func handlePrevious()
    {
        updateAppResultLabelWithText("Received List Topic Command:\n[Previous]")
    }
    
    func handleNext()
    {
        updateAppResultLabelWithText("Received List Topic Command:\n[Next]")
    }
    
    func handleSelect()
    {
        updateAppResultLabelWithText("Received List Topic Command:\n[Select]")
    }
    
    func handlePlay()
    {
        updateAppResultLabelWithText("Received List Topic Command:\n[Play]")        
        listTopic?.speakProductTitles(["Apples", "Waffles", "Pancakes", "Toast", "Bananas"])
    }
    
    func handleSearch(command: SAYCommand)
    {
        if let searchQuery = command.parameters[SAYSearchCommandRecognizerParameterQuery] as? String {
            let matchingItems = self.searchAppUsingQuery(searchQuery)
            listTopic?.speakProductTitles(matchingItems)
            updateAppResultLabelWithText("Received Search Topic Command:\n[Search for \(searchQuery)]")
        }
        else {
            /* ... */
        }
    }
 
    // MARK: Helpers
    
    private func searchAppUsingQuery(query: String) -> [String]
    {
        /* ...do some actual app logic to process the query... */
        return ["Waffles", "Pancakes", "Toast"]
    }
    
    private func updateAppResultLabelWithText(text: String)
    {
        dispatch_async(dispatch_get_main_queue()) {
            self.appResultLabel.text = text
        }
    }
}
