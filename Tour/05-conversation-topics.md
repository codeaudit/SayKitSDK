# Conversation Topics

Let's talk for a moment about mobile app design.

Most apps are built upon patterns that revolve around graphical interfaces. iOS applications typically follow the MVC paradigm: Model-**View**-Controller. While other developers may prefer alternative patterns, such as MVVM (Model-**View**-**View**Model). Still, the view is a top-level component in all of the well-known patterns, so view code is typically well-separated from the rest of the app's data and logic.

Since there's no established off-the-shelf design patterns for audio interfaces, conversational apps tend to evolve with a more ad hoc structure. As the apps grow, the seams start to show and the code becomes difficult to maintain.

If the app has multi-modal interface (both visual and audio), a more MVC-style architecture is typical, but the audio interface code still tends to seep all over the place.

One of SayKit's major goals is to make writing well-structured audio UI code as natural as visual UI code. Conversant Labs doesn't have the [Gang of Four](https://en.wikipedia.org/wiki/Design_Patterns) on the payroll, so we're not trying to invent a new universal-modality design pattern, but we do hope to provide tools to support conversational apps that are modular, maintainable, and intuitive.

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
