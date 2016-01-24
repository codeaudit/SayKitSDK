# Conversation Topics

At this point, we've know more than enough to be dangerous. We can build apps that ask questions, understand commands, and can make any sound they want.

But where should all of this conversational UI logic code go? If try to build a conversational agent with just a flat `SAYCommandRecognizerCatalog` and a simple `SAYSoundBoard` in our app delegate, we're going have a monolithic monster on our hands as our app grows.

## Keep 'em Separated

We need a better separation of concerns. Not only do we need to keep UI logic distinct from the business logic, but we also need to keep the UI logic underlying distinct app features from each other.

When it comes to graphical UI development, there are well-established patterns to handle this. For example, Apple designed it's UIKit classes to encourage iOS developers to follow the MVC paradigm (Model-View-Controller), so view code is typically well-separated from the rest of the app's data and logic. In addition, the `UIView` class supports a hierarchical structure, so a view is only directly responsible for a describing part of the scene: it can delegate the lower level details to its subviews.

We need something similar, but it should be concerned with the speaker and mircophone, not the display and touch sensors. We need something conversationally-oriented and capable of keeping distinct topics seperate. We need **Conversation Topics**.

## The `SAYConversationTopic` class

Staying with UIKit for a moment, let's highlight what could be considered `UIView`'s three major roles:

1. Handling screen input: configuring touch event-recognizing behavior (taps, gestures, etc.)
2. Declaring visual output: drawing their visual content to their frame on screen
3. Managing the interface hierarchy: composing subviews capable of handling lower-level UI concerns

With those capabilities, a `UIView` instance is able to fulfill its limited duties as the link between the user and application for a particular rectangle of screen real estate. No more, no less.

The `SAYConversationTopic` has similar roles, but with audio-specific manifestations:

1. Handling voice input: configuring voice command-recognizing behavior
2. Declaring audio output: posting their audio content as an event sequence
3. Managing the interface hierarchy: composing subtopics capable of handling lower-level UI concerns

To learn more, let's discuss each of these roles in turn.

### Handling Voice Input

*Summary: Topics conform to SAYCommandRegistry, so they can be plugged into the conversation manager. They can define the recognizers relevant to their topic*


### Topics as Audio Sources

*Summary: Topics confirm to SAYAudioEventSource, so again they can be plugged into the conversation manager. They say only whats relevant to their topic*

### Topics as Hierarchies

*Summary: Topics manage their subtopics. On the command recognizer side, they simply forward their subtopic's recognizers as their own. On the audio source side, they listen to their subtopic's events and compose them together with their own events into a single sequence. The root of the hierarchy is plugged into the conversation manager, which composes the whole tree, producing a single command registry and posting a single uadio event sequence.*
