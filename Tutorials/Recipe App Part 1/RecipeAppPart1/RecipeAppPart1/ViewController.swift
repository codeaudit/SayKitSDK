//
//  ViewController.swift
//  RecipeAppPart1
//
//  Created by Adam Larsen on 1/22/16.
//  Copyright © 2016 Conversant Labs. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var recognizedSpeechLabel: UILabel!
    @IBOutlet weak var appResultLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    @IBAction func stringRequestButtonTapped(sender: AnyObject)
    {
        let request = SAYStringRequest(promptText:"What recipe would you like to search for?") { result in
            if let recipeString = result {
                self.updateRecognizedSpeechLabelWithText(recipeString)
                self.updateAppResultLabelWithText("Received command:\n[Search for \(recipeString)]")
            }
            else {
                /* ... */
            }
        }
        
        SAYVoiceRequestPresenter.defaultPresenter().presentRequest(request)
    }

    @IBAction func selectRequestButtonTapped(sender: AnyObject)
    {
        let request = SAYSelectRequest(itemLabels: ["Chocolate Butterscotch Cookies", "Beef Lasagna", "Tuna Casserole"], promptText: "Which of your saved recipes would you like to review?") { result in
            self.handleSelectionWithResult(result)
        }
        
        SAYVoiceRequestPresenter.defaultPresenter().presentRequest(request)
    }
    
    @IBAction func selectedRequestAliasesButtonTapped(sender: AnyObject)
    {
        let options = [SAYSelectOption(label: "Chocolate Butterscotch Cookies", aliases: ["Grandma's Cookies"]),
                       SAYSelectOption(label: "Beef Lasagna", aliases: ["Pasta", "My Favorite Dish"]),
                       SAYSelectOption(label: "Tuna Casserole")]
        
        let request = SAYSelectRequest(options: options, promptText: "Which of your saved recipes would you like to review?") { result in
            self.handleSelectionWithResult(result)
        }
        
        SAYVoiceRequestPresenter.defaultPresenter().presentRequest(request)
    }
    
    // MARK: Helpers
    
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
    
    private func updateRecognizedSpeechLabelWithText(text: String)
    {
        dispatch_async(dispatch_get_main_queue()) {
            self.recognizedSpeechLabel.text = "\"\(text)\""
        }
    }
}
