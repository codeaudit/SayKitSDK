---
layout: default
title: SayKit Tutorial
---

# SayKit Tutorial

## Building Blocks of a Fully Conversational App

#### Skip to:
1. [General Plan](#general-plan)
2. [Setup]({{ "/tutorial/01-setup" | prepend: site.baseurl }})
  * [GUI Setup]({{ "/tutorial/01-setup#gui-setup" | prepend: site.baseurl }})
  * [Conversation Manager Setup]({{ "/tutorial/01-setup#conversation-manager-setup" | prepend: site.baseurl }})
  * [SoundBoard]({{ "/tutorial/01-setup#soundboard" | prepend: site.baseurl }})
3. [Voice Requests]({{ "/tutorial/02-voice-requests" | prepend: site.baseurl }})
  * [Confirmation Request]({{ "/tutorial/02-voice-requests#confirmation-request" | prepend: site.baseurl }})
  * [String Request]({{ "/tutorial/02-voice-requests#string-request" | prepend: site.baseurl }})
  * [Select Request]({{ "/tutorial/02-voice-requests#select-request" | prepend: site.baseurl }})
  * [Voice Request Responses and Turn-Taking]({{ "/tutorial/03-voice-request-responses" | prepend: site.baseurl }})
    - [Responder and Responses]({{ "/tutorial/03-voice-request-responses#responder-and-responses" | prepend: site.baseurl }})
    - [Select Request with Turn-Taking]({{ "/tutorial/03-voice-request-responses#select-request-with-turn-taking" | prepend: site.baseurl }})
    - [Success Responder]({{ "/tutorial/03-voice-request-responses#success-responder" | prepend: site.baseurl }})
    - [Invalid Responder]({{ "/tutorial/03-voice-request-responses#invalid-responder" | prepend: site.baseurl }})
    - [Failure Action]({{ "/tutorial/03-voice-request-responses#failure-action" | prepend: site.baseurl }})
4. [Command Recognizers]({{ "/tutorial/04-command-recognizers-part-1" | prepend: site.baseurl }})
  * [Standard Command Recognizers]({{ "/tutorial/04-command-recognizers-part-1#standard-command-recognizers" | prepend: site.baseurl }})
  * [Followup Requests]({{ "/tutorial/05-command-recognizers-part-2#followup-requests" | prepend: site.baseurl }})
  * [Custom Command Recognizers]({{ "/tutorial/06-command-recognizers-part-3#custom-command-recognizers" | prepend: site.baseurl }})
    - [Extending Standard Command Recognizers]({{ "/tutorial/06-command-recognizers-part-3#extending-standard-command-recognizers" | prepend: site.baseurl }})
    - [Using `SAYCustomCommandRecognizer`]({{ "/tutorial/07-command-recognizers-part-4#using-saycustomcommandrecognizer" | prepend: site.baseurl }}) 
5. [Conversation Topics]({{ "/tutorial/08-conversation-topics" | prepend: site.baseurl }})
  * [Setup]({{ "/tutorial/08-conversation-topics#setup" | prepend: site.baseurl }})
    - [GUI Setup]({{ "/tutorial/08-conversation-topics#gui-setup" | prepend: site.baseurl }})
    - [Conversation Manager Setup]({{ "/tutorial/08-conversation-topics#conversation-manager" | prepend: site.baseurl }})
  * [Single Conversation Topic: Product List]({{ "/tutorial/08-conversation-topics#single-conversation-topic-product-list" | prepend: site.baseurl }})
    - [Command Recognizers]({{ "/tutorial/08-conversation-topics#command-recognizers" | prepend: site.baseurl }})
    - [Audio Events]({{ "/tutorial/08-conversation-topics#audio-events" | prepend: site.baseurl }})
  * [Conversation Topic Hierarchy: Product Search]({{ "/tutorial/08-conversation-topics#conversation-topic-hierarchy-product-search" | prepend: site.baseurl }})
    - [Building the Hierarchy]({{ "/tutorial/08-conversation-topics#building-the-hierarchy" | prepend: site.baseurl }})
    - [Intercepting Subtopic Audio]({{ "/tutorial/08-conversation-topics#intercepting-subtopic-audio" | prepend: site.baseurl }})
6. [Wrapping Up!]({{ "/tutorial/08-conversation-topics#wrapping-up" | prepend: site.baseurl }})


## <a name="general-plan"></a> General Plan
In this tutorial we'll walk through how to use some of the most important features of SayKit.

You can access all of this code in our Tutorial Demos, [posted withour Developer Preview on Github](https://github.com/ConversantLabs/SayKitSDK/tree/master/Tutorial%20Demos/). Download the repository to follow along.

The tutorial workspace, _SayKitTutorials.xcworkspace_, contains two projects: 

- _SayKit Requests and Recognizers_: This project demonstrates some of SayKit's basic tools within a trivial app skeleton, allowing us to concentrate on the tools themselves.
- _SayKit Conversation Topics_: This one provides the bones of more substancial SayKit app, showing off a simple conversation topic hierarchy.

We begin with _SayKit Requests and Recognizers_. Open it up and play around as you follow along!

[Next - Setup >>]({{ "/tutorial/01-setup/" | prepend: site.baseurl }})
