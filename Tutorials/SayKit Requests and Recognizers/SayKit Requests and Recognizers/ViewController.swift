//
//  ViewController.swift
//  SayKit Requests and Recognizers
//
//  Created by Adam Larsen on 2016/01/26.
//  Copyright © 2016 Conversant Labs. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    @IBOutlet weak var appResultLabel: UILabel!
    
    var soundBoard: SAYSoundBoard?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let commandRegistry = SAYConversationManager.systemManager().commandRegistry as! SAYCommandRecognizerCatalog
        
        // Start with some one-off actions responding to standard commands:
        commandRegistry.addCommandRecognizer(SAYAvailableCommandsCommandRecognizer(responseTarget: self, action: "availableCommandsRequested"))
        
        commandRegistry.addCommandRecognizer(SAYSetSpeechRateCommandRecognizer(responseTarget: self, action: "setSpeechRateRequested:"))    // Note the ":" indicating a method parameter
        
        commandRegistry.addCommandRecognizer(SAYSearchCommandRecognizer(actionBlock: { command in
            if let searchQuery = command.parameters[SAYSearchCommandRecognizerParameterQuery] {
                self.presentResultText("Received command:\n[Search for \(searchQuery)]")
            }
            else {
                /* ... */
            }
        }))
        
        // "Help" command with a clarifying followup request:
        let helpIsAvailable = true
        // Note the action block's signature: we're returning a response now
        commandRegistry.addCommandRecognizer(SAYHelpCommandRecognizer { command -> SAYVoiceRequestResponse in
            if helpIsAvailable {
                // respond with a new voice request
                let followupRequest = SAYStringRequest(promptText: "What would you like help with?", action: { result in
                    self.presentResultText("Received command:\n[Help with \"\(result)\"")
                })
                return SAYVoiceRequestResponse(followupRequest: followupRequest)
            }
            else {
                // no need to follow up, just terminate the request and run the given action block
                return SAYVoiceRequestResponse.terminalResponseWithAction({
                    self.presentResultText("Received command:\n[Help, but none is available]")
                })
            }
        })
        
        // Add a text matcher to the standard "Select" command recognizer:
        let selectRecognizer = SAYSelectCommandRecognizer(actionBlock: { command in
            if let name = command.parameters["name"] {  // Note our custom parameter, "name"
                self.presentResultText("Received command:\n[Choose \(name)!]")
            }
            else if let itemName = command.parameters[SAYSelectCommandRecognizerParameterItemName] {
                self.presentResultText("Received command:\n[Select \(itemName)]")
            }
            else if let itemNumber = command.parameters[SAYSelectCommandRecognizerParameterItemNumber] {
                self.presentResultText("Received command:\n[Select item number \(itemNumber)]")
            }
            else {
                /* ... */
            }
        })
        let pattern = "i choose you @name"  // Note our custom parameter, "name"
        selectRecognizer.addTextMatcher(SAYPatternCommandMatcher(pattern: pattern))
        commandRegistry.addCommandRecognizer(selectRecognizer)
        
        // Custom command recognizer:
        let greetingsRecognizer = SAYCustomCommandRecognizer(customType: "Greeting") { command in
            self.presentResultText("Received command:\n[Greetings!]")
        }
        let patterns = ["hello", "hey", "what's up", "greetings"]
        greetingsRecognizer.addTextMatcher(SAYPatternCommandMatcher(forPatterns: patterns))
        greetingsRecognizer.addTextMatcher(SAYBlockCommandMatcher { text -> SAYCommandSuggestion? in
            return text.containsString("hi") ? SAYCommandSuggestion(confidence: kSAYCommandConfidenceLikely) :
                                               SAYCommandSuggestion(confidence: kSAYCommandConfidenceNone)
        })
        commandRegistry.addCommandRecognizer(greetingsRecognizer)
        
        // Custom command recognizer with feedback prompt:
        let badJokeRecognizer = SAYCustomCommandRecognizer(customType: "KnockKnock") { command -> SAYVoiceRequestResponse in
            let feedbackPrompt = SAYVoicePrompt(message: "Go away!")
            return SAYVoiceRequestResponse(feedbackPrompt: feedbackPrompt, followupRequest: nil, action: {
                    self.presentResultText("Received command:\n[KnockKnock]")
                }
            )
        }
        badJokeRecognizer.addTextMatcher(SAYPatternCommandMatcher(forPattern: "knock knock"))
        commandRegistry.addCommandRecognizer(badJokeRecognizer)
    }
    
    @IBAction func confirmationRequestButtonTapped(sender: AnyObject)
    {
        let request = SAYConfirmationRequest(promptText: "Are you sure?") { result in
            if let doIt = result as? Bool {
                if doIt { self.presentResultText("Received command:\n[Do it!]") }
                else    { self.presentResultText("Received command:\n[Don't do it!]") }
            }
            else {
                /* ... */
            }
        }
        
        SAYConversationManager.systemManager().presentVoiceRequest(request)
    }
    
    @IBAction func stringRequestButtonTapped(sender: AnyObject)
    {
        let request = SAYStringRequest(promptText:"What recipe would you like to search for?") { result in
            if let recipeString = result {
                let followupRequest = self.followupRequestForRecipe(recipeString)
                SAYConversationManager.systemManager().presentVoiceRequest(followupRequest)
            }
            else {
                /* ... */
            }
        }
        
        SAYConversationManager.systemManager().presentVoiceRequest(request)
    }
    
    @IBAction func selectRequestButtonTapped(sender: AnyObject)
    {
        let request = SAYSelectRequest(itemLabels: ["Blue", "Green", "Purple"], promptText: "What color would you like?") { result in
            self.handleSelectionWithResult(result)
        }
        
        SAYConversationManager.systemManager().presentVoiceRequest(request)
    }
    
    @IBAction func selectRequestAliasesButtonTapped(sender: AnyObject)
    {
        let options = [SAYSelectOption(label: "Blue", aliases: ["Ocean"]),
                       SAYSelectOption(label: "Green", aliases: ["Forest", "Emerald"]),
                       SAYSelectOption(label: "Purple")]
        
        let request = SAYSelectRequest(options: options, promptText: "What color would you like?") { result in
            self.handleSelectionWithResult(result)
        }
        
        SAYConversationManager.systemManager().presentVoiceRequest(request)
    }
    
    @IBAction func soundBoardButtonTapped(sender: AnyObject)
    {
        soundBoard?.speakText("Hello world!")
    }
    
    // MARK: Helpers
    
    func availableCommandsRequested()
    {
        presentResultText("Received command:\n[Available Commands]")
    }
    
    func setSpeechRateRequested(command: SAYCommand)
    {
        if let newSpeechRate = command.parameters[SAYSetSpeechRateCommandRecognizerParameterSpeechRate] {
            self.presentResultText("Received command:\n[Set speech rate to \(newSpeechRate)]")
        }
        else {
            /* ... */
        }
    }
    
    private func handleSelectionWithResult(result: SAYSelectResult?)
    {
        if
            let selectedItemName = result?.selectedOption.label,
            let selectedIndex = result?.selectedIndex
        {
            self.presentResultText("Received command:\n[Pick color \(selectedItemName) at index \(selectedIndex)]")
        }
        else {
            /* ... */
        }
    }
    
    private func followupRequestForRecipe(recipe: String) -> SAYConfirmationRequest
    {
        let followupRequest = SAYConfirmationRequest(promptText: "Are you sure you want to search for \"\(recipe)\"?", action: { result in
            if let doIt = result as? Bool {
                if doIt { self.presentResultText("Received command:\n[Search for \(recipe)]") }
                else    { self.presentResultText("Received command:\n[Don't search for \(recipe)]") }
            }
        })
        
        return followupRequest
    }
    
    private func presentResultText(text: String)
    {
        dispatch_async(dispatch_get_main_queue()) {
            self.appResultLabel.text = text
        }
        
        soundBoard?.speakText(text)
    }
}
