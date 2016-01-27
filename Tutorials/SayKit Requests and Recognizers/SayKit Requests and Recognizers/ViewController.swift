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
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let commandRegistry = SAYConversationManager.systemManager().commandRegistry as! SAYCommandRecognizerCatalog
        
        // Start with some one-off actions responding to standard commands:
        commandRegistry.addCommandRecognizer(SAYAvailableCommandsCommandRecognizer(responseTarget: self, action: "availableCommandsRequested"))
        
        commandRegistry.addCommandRecognizer(SAYSetSpeechRateCommandRecognizer(responseTarget: self, action: "setSpeechRateRequested:"))    // Note the ":" indicating a method parameter
        
        commandRegistry.addCommandRecognizer(SAYSearchCommandRecognizer(actionBlock: { command in
            if let searchQuery = command.parameters[SAYSearchCommandRecognizerParameterQuery] {
                self.updateAppResultLabelWithText("Received command:\n[Search for \(searchQuery)]")
            }
            else {
                /* ... */
            }
        }))
        
        // "Help" command with a clarifying followup request:
        commandRegistry.addCommandRecognizer(SAYHelpCommandRecognizer { command -> SAYVoiceRequestResponse in
            let followupRequest = SAYStringRequest(promptText: "What would you like help with?", action: { result in
                self.updateAppResultLabelWithText("Received command:\n[Help with \"\(result)\"")
            })
            return SAYVoiceRequestResponse(followupRequest: followupRequest)
        })
        
        // Add a text matcher to the standard "Select" command recognizer:
        let selectRecognizer = SAYSelectCommandRecognizer(actionBlock: { command in
            if let name = command.parameters["name"] {  // Note our custom parameter, "name"
                self.updateAppResultLabelWithText("Received command:\n[Choose \(name)!]")
            }
            else if let itemName = command.parameters[SAYSelectCommandRecognizerParameterItemName] {
                self.updateAppResultLabelWithText("Received command:\n[Select \(itemName)]")
            }
            else if let itemNumber = command.parameters[SAYSelectCommandRecognizerParameterItemNumber] {
                self.updateAppResultLabelWithText("Received command:\n[Select item number \(itemNumber)]")
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
            self.updateAppResultLabelWithText("Received command:\n[Greetings!]")
        }
        let patterns = ["hello", "hey", "what's up", "greetings"]
        greetingsRecognizer.addTextMatcher(SAYPatternCommandMatcher(forPatterns: patterns))
        commandRegistry.addCommandRecognizer(greetingsRecognizer)
    }
    
    @IBAction func confirmationRequestButtonTapped(sender: AnyObject)
    {
        let request = SAYConfirmationRequest(promptText: "Are you sure?") { result in
            if let doIt = result as? Bool {
                if doIt { self.updateAppResultLabelWithText("Received command:\n[Do it!]") }
                else    { self.updateAppResultLabelWithText("Received command:\n[Don't do it!]") }
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
                self.updateAppResultLabelWithText("Received command:\n[Search for \(recipeString)]")
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
        let soundBoard = SAYSoundBoard()
        
        let manager = SAYConversationManager.systemManager()
        manager.addAudioSource(soundBoard, forTrack: SAYAudioTrackMainIdentifier)
        
        soundBoard.speakText("Hello world!")
    }
    
    // MARK: Helpers
    
    func availableCommandsRequested()
    {
        updateAppResultLabelWithText("Received command:\n[Available Commands]")
    }
    
    func setSpeechRateRequested(command: SAYCommand)
    {
        if let newSpeechRate = command.parameters[SAYSetSpeechRateCommandRecognizerParameterSpeechRate] {
            self.updateAppResultLabelWithText("Received command:\n[Set speech rate to \(newSpeechRate)]")
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
            self.updateAppResultLabelWithText("Received command:\n[Pick color #\(selectedIndex): \(selectedItemName)]")
        }
        else {
            /* ... */
        }
    }
    
    private func updateAppResultLabelWithText(text: String)
    {
        dispatch_async(dispatch_get_main_queue()) {
            self.appResultLabel.text = text
        }
    }
}
