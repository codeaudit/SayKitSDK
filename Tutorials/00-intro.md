# SayKit Tutorial: Building Blocks of a Fully Conversational App

## Skip to the Good Stuff!
1. [General Plan](#general-plan)
2. [Setup](./01-setup.md)
  * [GUI Setup](./01-setup.md#gui-setup)
  * [Conversation Manager Setup](./01-setup.md#conversation-manager-setup)
3. [Voice Requests](./02-voice-requests.md)
  * [Confirmation Request](./02-voice-requests.md#confirmation-request)
  * [String Request](./02-voice-requests.md#string-request)
  * [String Request (with Followup Request)](./02-voice-requests.md#string-request-with-followup-request)
  * [Select Request](./02-voice-requests.md#select-request)
  * [Select Request (with Aliases)](./02-voice-requests.md#select-request-with-aliases)
  * [SoundBoard (Bonus!)](./02-voice-requests.md#soundboard-bonus)
4. [Command Recognizers](./03-command-recognizers-part-1.md)
  * [Standard Command Recognizers](./03-command-recognizers-part-1.md#standard-command-recognizers)
  * [Followup Requests](./04-command-recognizers-part-2.md#followup-requests)
  * [Custom Command Recognizers](./05-command-recognizers-part-3.md#custom-command-recognizers)
    * [Extending Standard Command Recognizers](./05-command-recognizers-part-3.md#extending-standard-command-recognizers)
    * [Implementing `SAYCustomCommandRecognizer`](./06-command-recognizers-part-4.md#implementing-saycustomcommandrecognizer) 
5. [Conversation Topics](./07-conversation-topics.md)
  * [Setup](./07-conversation-topics.md#setup)
    * [GUI Setup](./07-conversation-topics.md#gui-setup)
    * [Conversation Manager Setup](./07-conversation-topics.md#conversation-manager)
  * [Single Conversation Topic: Product List](./07-conversation-topics.md#single-conversation-topic-product-list)
    * [Command Recognizers](./07-conversation-topics.md#command-recognizers)
    * [Audio Events](./07-conversation-topics.md#audio-events)
  * [Conversation Topic Hierarchy: Product Search](./07-conversation-topics.md#conversation-topic-hierarchy-product-search)
    * [Building the Hierarchy](./07-conversation-topics.md#building-the-hierarchy)
    * [Intercepting Subtopic Events](./07-conversation-topics.md#intercepting-subtopic-events)
6. [Wrapping Up!](./07-conversation-topics.md#wrapping-up)


## General Plan:
In this tutorial we'll walk through how to use some of the most important features of SayKit.

The tutorial workspace, [`SayKitTutorials.xcworkspace`](./SayKitTutorials.xcworkspace), contains two projects: 

- [`SayKit Requests and Recognizers`](./SayKit%20Requests%20and%20Recognizers): This project demonstrates some of SayKit's basic tools within a trivial app skeleton, allowing us to concentrate on the tools themselves.
- [`SayKit Conversation Topics`](./SayKit%20Conversation%20Topics): This one provides the bones of more substanial SayKit app, showing off a simple conversation topic hierarchy.

We begin with `SayKit Requests and Recognizers`. Open it up and play around as you follow along!

[Next - Setup >>](./01-setup.md)
