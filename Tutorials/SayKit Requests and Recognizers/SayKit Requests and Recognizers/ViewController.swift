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
        
        commandRegistry = SAYConversationManager.systemManager().commandRegistry as! SAYCommandRecognizerCatalog
        
        commandRegistry.addCommandRecognizer(SAYAvailableCommandsCommandRecognizer(responseTarget: self, action: "availableCommandsRequested"))
        
        commandRegistry.addCommandRecognizer(SAYSearchCommandRecognizer(responseTarget: self, action: "searchRequested:"))
        
        commandRegistry.addCommandRecognizer(SAYSearchCommandRecognizer(actionBlock: { command in
            if let searchQuery = command.parameters[SAYSearchCommandRecognizerParameterQuery] {
                self.updateAppResultLabelWithText("Received command:\n[Search for \(searchQuery)]")
            }
            else {
                /* ... */
            }
        }))
        
        let greetingsRecognizer = SAYCustomCommandRecognizer(customType: "Greeting") { command in
            self.updateAppResultLabelWithText("Received command:\n[Greetings!]")
        }
        let patterns = ["hello", "hey", "what's up"]
        greetingsRecognizer.addTextMatcher(SAYPatternCommandMatcher(forPatterns: patterns))
        commandRegistry.addCommandRecognizer(greetingsRecognizer)
        
        let extendedSelectRecognizer = SAYSelectCommandRecognizer(actionBlock: { command in
            if let name = command.parameters["name"] {
                self.updateAppResultLabelWithText("Received command:\n[Choose \(name)!]")
            }
            else {
                /* ... */
            }
        })
        let pattern = "i choose you @name"
        extendedSelectRecognizer.addTextMatcher(SAYPatternCommandMatcher(pattern: pattern))
        commandRegistry.addCommandRecognizer(extendedSelectRecognizer)
        
        commandRegistry.addCommandRecognizer(SAYSelectCommandRecognizer { command -> SAYVoiceRequestResponse in
            if let selectedName = command.parameters[SAYSelectCommandRecognizerParameterItemName] as? String {
                let matchingNames = self.namesMatchingSelection(selectedName)
                if matchingNames.count > 0 {
                    // respond with a new voice request
                    let request = SAYSelectRequest(itemLabels: matchingNames, promptText: "Which one?", action: { result in
                        if let followupName = result?.selectedOption.label {
                            self.updateAppResultLabelWithText("Received command:\n[Choose \(followupName)!]")
                        }
                        else {
                            /* ... */
                        }
                    })
                    return SAYVoiceRequestResponse(followupRequest:request);
                }
                else {
                    // no need to follow up, just terminate the request and run the given action block
                    return SAYVoiceRequestResponse.terminalResponseWithAction() {
                        self.updateAppResultLabelWithText("Received command:\n[Choose \(selectedName)!]")
                    };
                }
            }
            else {
                return SAYVoiceRequestResponse.terminalResponseWithAction() {
                    self.updateAppResultLabelWithText("Couldn't get a name match")
                };
            }
        })
    }
    
    @IBAction func confirmationRequestButtonTapped(sender: AnyObject)
    {
        let request = SAYConfirmationRequest(promptText: "Are you sure?") { result in
            if let doIt = result as? Bool {
                if doIt { self.updateAppResultLabelWithText("Received comand:\n[Do it!]") }
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
    
    func searchRequested(command: SAYCommand)
    {
        if let searchQuery = command.parameters[SAYSearchCommandRecognizerParameterQuery] {
            self.updateAppResultLabelWithText("Received command:\n[Search for \(searchQuery)]")
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
    
    private func namesMatchingSelection(query: String) -> [String]
    {
        /* ...do some actual app logic to find a match... */
        return ["Toby Pikachu", "Susan Pikachu"]
    }
    
    private func updateAppResultLabelWithText(text: String)
    {
        dispatch_async(dispatch_get_main_queue()) {
            self.appResultLabel.text = text
        }
    }
    
    private var commandRegistry: SAYCommandRecognizerCatalog!
}