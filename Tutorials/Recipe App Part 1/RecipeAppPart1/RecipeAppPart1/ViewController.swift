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
                self.updateAppResultLabelWithText("Received command: [Search for \(recipeString)]")
            }
            else {
                /* ...handle error... */
            }
        }
        
        SAYVoiceRequestPresenter.defaultPresenter().presentRequest(request)
    }

    @IBAction func selectRequestButtonTapped(sender: AnyObject)
    {

    }
    
    // MARK: Helpers
    
    func updateAppResultLabelWithText(text: String)
    {
        dispatch_async(dispatch_get_main_queue()) {
            self.appResultLabel.text = text
        }
    }
    
    func updateRecognizedSpeechLabelWithText(text: String)
    {
        dispatch_async(dispatch_get_main_queue()) {
            self.recognizedSpeechLabel.text = "\"\(text)\""
        }
    }
}

