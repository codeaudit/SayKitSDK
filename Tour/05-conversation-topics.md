# Conversation Topics

At this point, we've know more than enough to be dangerous. We can build apps that ask questions, understand commands, and can make any sound they want.

But where should all of this conversational UI logic code go? If try to build a conversational agent with just a flat `SAYCommandRecognizerCatalog` and a simple `SAYSoundBoard` in our app delegate, we're going have a monolithic monster on our hands as our app grows.

## Keep 'em Separated

We need a better separation of concerns. Not only do we need to keep UI logic distinct from the business logic, but we also need to keep the UI logic underlying distinct app features from each other.

When it comes to graphical UI development, there are well-established patterns to handle this. For example, Apple designed it's UIKit classes to encourage iOS developers to follow the MVC paradigm (Model-View-Controller), so view code is typically well-separated from the rest of the app's data and logic. In addition, the `UIView` class supports a hierarchical structure, so a view is only directly responsible for a describing part of the scene: it can delegate the lower level details to its subviews.

We need something similar, but it should be concerned with the speaker and mircophone, not the display and touch sensors. We need something conversationally-oriented and capable of keeping distinct topics seperate. We need **Conversation Topics**.

## The `SAYConversationTopic` class

In UIKit on iOS, the primary building block for the graphical interface is the `UIView`; the analogous class in SayKit is called the `SAYConversationTopic`. Let's consider what could be considered `UIView`'s three major roles:

1. Declaring visual output: 
2. Handling screen input: 
3. Managing the interface hierarchy: 

The `SAYConversationTopic` has the same roles, but with different audio-specific manifestations.

1. Declaring audio output:
2. Handling voice input:
3. Managing the interface hierarchy:  

## Topics as Command Registries

## Topics as Audio Sources

## Topics as Hierarchies

// talk about root topic connection to sys mgr
