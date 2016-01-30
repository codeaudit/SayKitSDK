//
//  AppDelegate.swift
//  SayKit Conversation Topics
//
//  Created by Adam Larsen on 2016/01/26.
//  Copyright © 2016 Conversant Labs. All rights reserved.
//

import UIKit

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?

    func application(application: UIApplication, didFinishLaunchingWithOptions launchOptions: [NSObject: AnyObject]?) -> Bool {
        
        // Grab the initial view controller set up by the storyboard
        window = UIWindow(frame: UIScreen.mainScreen().bounds)
        let storyboard = UIStoryboard(name: "Main", bundle: nil)
        let viewController = storyboard.instantiateInitialViewController() as! ViewController
        
        // Wrap initial view controller in a command bar controller
        let commandBarController = SAYCommandBarController()
        commandBarController.contentViewController = viewController
        
        window?.rootViewController = commandBarController
        window?.makeKeyAndVisible()
        
        // Initial setup of the SAYConversationManager, with a Conversation Topic as
        // command registry and main audio source.
        let rootTopic = ProductSearchTopic(eventHandler: viewController)
        let systemManager = SAYConversationManager.systemManager()
        systemManager.commandRegistry = rootTopic
        systemManager.addAudioSource(rootTopic, forTrack:SAYAudioTrackMainIdentifier)
        
        // create the subtopic to handle the list of results
        let listTopic = ProductListTopic(eventHandler: viewController)
        
        // by adding it as a subtopic, we are implicitly doing two things:
        // 1. adding its command recognizers to our collection
        // 2. listening for, and passing on, our subtopic's audio events (potentially with modification: see below)
        rootTopic.addSubtopic(listTopic)
        
        viewController.listTopic = listTopic
        
        // Optional optimization
        SAYAPIKeyManager.sharedInstance().prefetchAPIKeys()
        
        return true
    }

    func applicationWillResignActive(application: UIApplication) {
        // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
        // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
    }

    func applicationDidEnterBackground(application: UIApplication) {
        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    }

    func applicationWillEnterForeground(application: UIApplication) {
        // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
    }

    func applicationDidBecomeActive(application: UIApplication) {
        // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    }

    func applicationWillTerminate(application: UIApplication) {
        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    }


}
