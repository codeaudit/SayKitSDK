# Handling User Commands

One of the major benefits of a conversational UI is giving users the ability to issue commands using plain old human languages. Users are not required to tap around their screens to accomplish a task: they can simply tell the app what they want done.

While that might be great news for users, it opens up a whole world of complexity for developers. Managing this complexity is one of SayKit’s primary goals.

While basic verbal user commands could be implemented in SayKit with a simple `StringRequest` hooked up to a callback to acting on the resulting text, as an application grows, this approach would quickly become untenable. SayKit encourages a more scalable approach by offering a full command processing pipeline to act as a mediator between speech recognition and application logic.

## Command Processing Pipeline

SayKit’s user command processing pipeline is similar in spirit to UIKit’s UIEvent processing paradigm. Like UIKit, the process is split between recognition and delivery phases. Unlike UIKit, SayKit’s pipeline is general enough to handle all kinds of command sources and responders, not just GUI- or device-centric ones.

[insert high-level pipeline for example command].

### SAYCommand

`SAYCommand` is a simple class with two properties: **type** and **parameters**. Commands are differentiated by their **type**, and commands can have any number of unstructured arguments associated with them, stored in the **parameters** dictionary. This class provides the common currency for the resolution, dispatch, and enactment of user commands.

### Command Resolution

The resolution phase of the command pipeline revolves around two data types: the `CommandResolver` protocol and `CommandEnumerator` class.

A `CommandResolver` class has only one duty to perform: transforming an input value (in the case of verbal commands: a string) into a list of potential interpretations in the form of `SAYCommand`s. Verbal input comes with much more uncertainty about user intent than other types of input (e.g. screen taps), so the resolution process can yield multiple valid interpretations.

This list of potential commands is packaged as a `CommandEnumerator`, not a simple static collection type. The `CommandEnumerator` is a specialization of the `NSEnumerator` class, which provides accessors to a collection of `SAYCommand`s. This extra level of indirection allows for the resolution phase to perform its calculations in a lazy manner, if desired. Intent recognition can be a fairly involved process, sometimes including involved language processing or even server-side utilities. By only exposing an enumerator, costly processing on ultimately discarded results can be avoided altogether.

### Command Dispatching

Once a set of potential commands are identified, it is time to find an agent to act on one of them. The central mediators here are the `CommandResponder` protocol and `CommandDispatcher` class.

The `CommandResponder` protocol describes an interface for declaring an ability to handle a particular command type, and then actually accepting a command with which to take action. Much like UIKit’s `UIResponder` class, the `CommandResponder` has a reference to a **nextResponder**, which in effect, forms a responder chain. Unlike UIKit’s version of a responder chain, a SayKit responder chain has no relationship with the application’s view hierarchy (although it could -- see [Managing Command Context](#managing-command-context) for details.

The `CommandDispatcher` class defines a simple search strategy to match the best potential command with the best responder for the job. It cycles through each command from the provided `CommandEnumerator` and for each one, it walks down the responder chain until it finds a responder able to act on the command. Once that responder is found, the command is dispatched to it and the search ends.

[insert diagram of command search]

### System Dispatcher

For convenience, a special system dispatcher is available in all SayKit apps. By default, its **firstResponder** is a `CommandResponderRegistry`, which is a simple collection of functions that accept commands, each one indexed by command type.

[insert code example of registering dispatch commands]

## Verbal Command Processing

Nothing in SayKit’s core command processing paradigm is explicitly bound to handle voice-based commands, although this is its most common use case. To tailor the pipeline for voice interaction, SayKit provides the `VerbalCommandRequest` class. Like any voice-based interaction, a subclass of `VoiceRequest` is used to mediate the interaction: `VerbalCommandRequest`.

`VerbalCommandRequests` are rarely initiated directly because their component commandResolver and commandDispatcher properties are typically application-level systems. Instead, SayKit provides a default factory to manage the references to these systems, the `VerbalCommandRequestManager`, that constructs the requests. This manager is itself customizable, so few applications will have a need to use other means to build `VerbalCommandRequest`s.

[insert diagram of typical VerbalCommandRequest pipeline]

### Resolution

The default `VerbalCommandRequestManager` uses a two-phase command resolver, concatenating the results of each into a single `CommandEnumerator`.

#### Standard library commands
SayKit has a set of standard library commands that are automatically considered as possible resolutions. Some examples include:

| Command type         | Parameters                    |
|----------------------|-------------------------------|
| search               | query: String, filter: String |
| increase_speech_rate | *none*                        |
| cancel               | *none*                        |

[insert a link to the document of “standard library” commands]

If any standard commands appear to be likely candidates for the user intent, they will be included in the result.

#### Custom text resolution

A developer-supplied resolver of type `TextCommandResolver` is then consulted, which is a special kind of `CommandResolver` that maps strings to a `CommandEnumerator`.

While any developer-supplied class that conforms to `TextCommandResolver` can be used here, the default `VerbalCommandRequestManager` comes equipped with a simple implementation: a `TextResolutionRegistry`. This registry accepts functions that map a string to either a SAYCommand or nil. All registered functions will become part of the resolution process, and any non-nil results will be included in the resulting command enumeration.

[insert example code of registering a command]

A particularly useful tool for resolving text is the `PatternResolver`. This can simplify the above example to:

[insert alternative of above code with patterns instead of manual string processing]

### Responding

The default VerbalCommandRequestManager is configured to send its resolved commands to the system dispatcher, [detailed above](#system-dispatcher).

[insert consolidated example of above code examples to show a full pipeline impl]

## Managing Command Context

For simple apps, the default flat registries involved with text resolution and command responding is a good model. However, as an application’s functionality grows, its set of valid application contexts (or states) grow as well. Different states interpret and respond to commands differently.

In graphical applications, this kind of context management is implicit in the view hierarchy. Virtually all user interactions are restricted to which controls are on the screen. In voice applications, the developer must be much more diligent in controlling command interpretations and responses based on the context.

[insert discussion of context management...]

### Mirroring view hierarchies

For SayKit apps with visual components, oftentimes these contexts will map well to the view hierarchy present on screen. To aid in synchronizing these logical hierarchies, SayKit offers tools to relate command contexts with UIKit structures that manage application hierarchy (think `UIViewController` and `UIStoryboard`).

[insert more details...]

## Command Bar

SayKit includes the `CommandBar`, a `UIView` that gives users an interface to trigger `VerbalCommandRequests` directly. Its corresponding `UIViewController`, the `CommandBarController`, has a **requestManager** (typically the default `VerbalCommandRequestManager`) which is used to spawn new request sessions.

[insert screenshot of command bar]

In addition, the `CommandBarController` can be used to provide a visible menu of available commands in the current application context. Choosing a command will instantiate a SAYCommand of the corresponding type and send it directly to the **requestManager**'s command dispatcher.
