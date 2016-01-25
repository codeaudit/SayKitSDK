//
//  ViewController.swift
//  RecipeAppPart1
//
//  Created by Adam Larsen on 1/22/16.
//  Copyright © 2016 Conversant Labs. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var appResultLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        commandRegistry = SAYConversationManager.systemManager().commandRegistry as! SAYCommandRecognizerCatalog
        
        commandRegistry.addCommandRecognizer(SAYAvailableCommandsCommandRecognizer(responseTarget: self, action: "handleAvailableCommands"))
        
        commandRegistry.addCommandRecognizer(SAYSearchCommandRecognizer(actionBlock: { command in
            let searchQuery = command.parameters[SAYSearchCommandRecognizerParameterQuery]
            self.updateAppResultLabelWithText("Received command:\n[Search for \(searchQuery)]")
        }))
        
        let selectRecognizer = SAYSelectCommandRecognizer(actionBlock: { command in
            if let name = command.parameters["name"] {
                self.updateAppResultLabelWithText("Received command:\n[Choose \(name)!]")
            }
            else {
                /* ... */
            }
        })
        let pattern = "i choose you @name"
        selectRecognizer.addTextMatcher(SAYPatternCommandMatcher(pattern: pattern))
        commandRegistry.addCommandRecognizer(selectRecognizer)
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
        let request = SAYSelectRequest(itemLabels: ["Chocolate Butterscotch Cookies", "Beef Lasagna", "Tuna Casserole"], promptText: "Which of your saved recipes would you like to review?") { result in
            self.handleSelectionWithResult(result)
        }
        
        SAYConversationManager.systemManager().presentVoiceRequest(request)
    }
    
    @IBAction func selectedRequestAliasesButtonTapped(sender: AnyObject)
    {
        let options = [SAYSelectOption(label: "Chocolate Butterscotch Cookies", aliases: ["Grandma's Cookies"]),
                       SAYSelectOption(label: "Beef Lasagna", aliases: ["Pasta", "My Favorite Dish"]),
                       SAYSelectOption(label: "Tuna Casserole")]
        
        let request = SAYSelectRequest(options: options, promptText: "Which of your saved recipes would you like to review?") { result in
            self.handleSelectionWithResult(result)
        }
        
        SAYConversationManager.systemManager().presentVoiceRequest(request)
    }
    
    // MARK: Helpers
    
    func handleAvailableCommands()
    {
        updateAppResultLabelWithText("Received command:\n[Available Commands]")
    }
    
    private func handleSelectionWithResult(result: SAYSelectResult?)
    {
        if
            let selectedItemName = result?.selectedOption.label,
            let selectedIndex = result?.selectedIndex
        {
            self.updateAppResultLabelWithText("Received command:\n[Details for Recipe #\(selectedIndex): \(selectedItemName)]")
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
    
    private var commandRegistry: SAYCommandRecognizerCatalog!
}
