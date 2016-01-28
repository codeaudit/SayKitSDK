# SayKit Tutorial: Building Blocks of a Fully Conversational App

## Skip to the Good Stuff!
1. [General Plan](#general-plan)
2. [Setup](./01-setup.md)
  1. [GUI Setup](./01-setup.md#gui-setup)
  2. [Conversation Manager Setup](./01-setup.md#conversation-manager-setup)
3. [Command Recognizers](./02-command-recognizers.md)
  1. [Standard Command Recognizers](./02-command-recognizers.md#standard-command-recognizers)
  2. [Followup Requests](./02-command-recognizers.md#followup-requests)
  3. [Custom Command Recognizers](./02-command-recognizers.md#custom-command-recognizers)
4. [Voice Requests](./03-voice-requests.md)
  1. [Confirmation Request](./03-voice-requests.md#confirmation-request)
  2. [String Request](./03-voice-requests.md#string-request)
  3. [Select Request](./03-voice-requests.md#select-request)
  4. [Select Request (with Aliases)](./03-voice-requests.md#select-request-with-aliases)
  5. [SoundBoard (Bonus!)](./03-voice-requests.md#soundboard-bonus)
5. [Conversation Topics](./04-conversation-topics.md)
  1. [Setup](./04-conversation-topics.md#setup)
    1. [GUI Setup](./04-conversation-topics.md#gui-setup)
    2. [Conversation Manager Setup](./04-conversation-topics.md#gui-setup#conversation-manager)
  2. [Single Conversation Topic: Product List](./04-conversation-topics.md#single-conversation-topic-product-list)
    1. [Command Recognizers](./04-conversation-topics.md#command-recognizers)
    2. [Audio Events](./04-conversation-topics.md#audio-events)
  3. [Conversation Topic Hierarchy: Product Search](./04-conversation-topics.md#conversation-topic-hierarchy-product-search)
    1. [Building the Hierarchy](./04-conversation-topics.md#building-the-hierarchy)
    2. [Prefacing Subtopic Events](./04-conversation-topics.md#prefacing-subtopic-events)
6. [Wrapping Up!](./04-conversation-topics.md#wrapping-up)


## General Plan:
In this tutorial we'll walk through how to use some of the most important features of SayKit.

The tutorial workspace, [`SayKitTutorials.xcworkspace`](./SayKitTutorials.xcworkspace), contains two projects: [`SayKit Requests and Recognizers`](./SayKit%20Requests%20and%20Recognizers) and [`SayKit Conversation Topics`](./SayKit%20Conversation%20Topics). The first project demonstrates the use of several standard voice requests and command recognizers, while the second provides an example of a simple Conversation Topic hierarchy. 

We begin with `SayKit Requests and Recognizers`. Open it up and play around as you follow along!

[Next - Setup >>](./01-setup.md)