# Voice Requests

In SayKit applications, all voice input from the user revolves around the `VoiceRequest` class. 

`VoiceRequest` instances are able to declare a question to prompt the user, define a visual interface, control activation of the microphone, direct the recognition of speech, and perform many other duties.

SayKit includes a collection of pre-built `VoiceRequest` types to handle many common use cases. To skip ahead to see what’s available out-of-the-box, see [Built-in Requests](#built-in-requests). To get more details about how a `VoiceRequest` works, continue reading.

## Request Lifecycle

[insert VR Figure 1: overview of lifecycle that doesn't include too much collaborator detail]

## Anatomy of a Request

[insert VR Figure 2: class diagram]

### Components

The behavior of a request is defined almost entirely by its component classes, which include the following.

#### VoiceRequestViewController

While a voice request is underway, its **viewController** is presented to the screen. The `VoiceRequestViewController` class provides an GUI that communicates the request’s purpose, gives feedback about the ongoing microphone activity, and provides interactive control over the session.

In addition to displaying these basics, the `VoiceRequestViewController` can act as a container for another view controller. By setting the **contentViewController** property on its **viewController**, a request ensures a supplemental view will appear on-screen while the request is active. For example, the built-in `SelectRequest` uses this feature to insert a `UITableView` onto the screen to display potential responses to the user.

[insert VR Figure 3: screen shot of a basic VRVC]

#### VoiceRequestSoundBoard

The request’s **soundBoard** is the auditory equivalent to its visual **viewController**. It is able to play sounds related to a request, for instance, speaking a prompt to ask the user a question or playing a tone when the microphone has been deactivated.

#### SpeechRecognitionService

Through its **recognitionService** component, a request defines how communication with a (typically server-side) speech recognition service will be handled. SayKit already has a speech recognizer built-in, but an alternative can be used by including a third-party service with an interface conforming to the `SpeechRecognitionService` protocol.

#### VoiceRequestResponder

When recognized speech (or an error) returns from the recognition service, it is passed along to the **responder**, which takes action on the result. The `VoiceRequestResponder` protocol is completely open-ended, defining only one method which returns no value: `voiceRequest:receivedData:error:`. It is often the **responder**’s duty to end the request’s lifecycle after responding to this message.

Due to this close interaction with the lifecycle and its request-specific logic, a `VoiceRequestResponder` class is typically not very reusable. Its implementation is often bound tightly to the type of `VoiceRequest` it serves.

### Other Collaborators

The `VoiceRequestPresenter` class is responsible for preparing and providing application resources necessary to execute a request. These resources include:
- a `SpeechRecognitionManager` for controlling a session with the **recognitionService**
- a `UIViewController` upon which the **viewController** is presented
- an `AudioTrack` for the **soundBoard** to post events to

While active, a request has its presenter property set to the instance of `VoiceRequestPresenter` that activated it.

## Built-in Requests

### ConfirmationRequest

Voice applications often have a need to ask the user simple yes-or-no questions, often to confirm an impending action. SayKit offers the `ConfirmationRequest` class for this purpose. It will reduce a wide variety of affirmative (e.g. “yes”, “sure”, “OK”) or negative responses (e.g. “no”, “nope”, “nah”) into a simple Boolean value. In addition, its **viewController** includes buttons to allow the user to respond silently with a tap.

```swift
let request = SAYConfirmationRequest(promptText:"Are you sure?") { result in
    result?.confirmed == true ? print("You're sure!") : print("You're not sure!")
}
```

### SelectRequest

When the application needs to ask the user to make a selection from a set of choices, the `SelectRequest` can be used. Its **viewController** includes a visual table of the choices from which a selection can be made with a tap. In addition to accepting verbatim responses from a set, choices can be customized to provide more robust interpretation (e.g. providing a set of aliases for each choice). Refer to the `SelectOption` class documentation for more details.

```swift
let options = [SAYSelectOption(label:"Cash", aliases:["Dollars", "Bills"]),
               SAYSelectOption(label:"Credit", aliases:["Visa", "Card", "Charge"])]

let request = SAYSelectRequest(options:options, promptText:"How would you like to pay?") { result in
    if let paymentMethod = result?.selectedOption?.label {
		print("You have chosen to pay with \(paymentMethod)")
	}
}
```

### VoiceCommandRequest

To allow the user to speak a direct command to the application, a `VoiceCommandRequest` can be initiated. Interpreting open-ended user speech into a command for the application to carry out is an involved topic, which is discussed at length in the [User Commands section](../handling-user-commands/).

### StringRequest
To prompt the user for any kind of open-ended short speech, use the `StringRequest` class. Any intelligible speech input will be reduced to a simple string.

```swift
let request = SAYStringRequest(promptText:"What is your destination address?") { result in
    if let address = result?.transcription {
    	print("Your destination address is \(address)")
	}
}
```

### NumericalRequest

Similarly, to prompt the user for a strictly numerical response (e.g. "one", "third"), use the `NumericalRequest` class. This request is designed to handle both number (e.g. "two", "three point one") and ordinal (e.g. "first", "fourth") responses. The result of a `NumericalRequest` is an `NSNumber` instance.

```swift
let request = SAYNumericalRequest(promptText:"What is the zip code?") { result in
	if let zipCode = result?.number {
		print("The zip code is \(zipCode)")
	}
}
```

### PatternMatchRequest
If the user’s speech input should follow a particular form, a `PatternMatchRequest` can be used. By declaring a set of patterns for it to handle, the request can both constrain acceptable responses to speech matching the patterns and isolate and extract values from that speech. If the user issues speech that does not match an expected pattern, the prompt will repeat until they do. These requests use a special templating format, which is described more fully here [insert link when section is complete].

```swift
let prompt = "What move would you like to make? (e.g. Bishop to F 7)"
let templates = ["@piece to @row @column:Number",
    			 "@piece to row @row and column @column:Number",
   				 "Move @piece to column @column:Number row @row"]

let request = SAYPatternMatchRequest(promptText:prompt, templates:templates) { result in
    if
        let entities = result?.entities,
        let piece = entities["piece"],
        let row = entities["row"],
        let column = entities["column"]
    {
        print("Moving your \(piece) to row \(row), column \(column)")
    }
}
```

## Extending Voice Requests

The standard SayKit `VoiceRequest` subclasses can handle a wide variety of use cases. If, however, a more custom request is needed, the composable nature of the `VoiceRequest` class makes it easy to extend an existing request type by just swapping out a component.

In addition to swapping out components, the `VoiceRequest` class offers two customizable methods that it calls itself when the request lifecycle begins and ends. The `didActivate` and `willDeactivate` methods can be overridden to serve any purpose, though they are most often used to set up or tear down custom components. UIKit developers can think of them as analogous to `UIViewController`’s `viewDidAppear:` and `viewWillDisappear:` methods.

### Common extension scenarios

The following are a few common reasons to extending the `VoiceRequest` class, along with implementation suggestions.

#### Adding custom speech processing

To customize how recognized speech is processed, simply set a new **responder** that conforms to the `VoiceRequestResponder` protocol. 

The **responder** can do anything it wishes with the results of speech recognition, from performing simple string matching to employing complex natural language understanding techniques. To fulfill its requirements as a component of `VoiceRequest`, however, two important considerations must be made:

First, note that the recognized speech provided to the `voiceRequest:receivedData:error:` method is of type id. This is because the request’s **recognitionService** and responder are directly uncoupled, but must deal in the same type of speech recognition data. The request forwards the result fetched from the **recogntionService** directly to the **responder**. As a result, when replacing either of these components, ensure that the types match up. Check the documentation for each `VoiceRequest` subclass to verify what result data type it uses.

Secondly, in many cases, the responder represents the the last step in the request lifecycle. As a result, it has the responsibility to trigger the dismissal of the request when appropriate. In some cases, failing to take an action to affect the lifecycle can put the request into an permanently idle (but still presented) state.

#### Changing the presented view

A custom visual component can be added to a presented request by setting the **contentViewController** property on the request’s **viewController**. The associated subview is displayed front-and-center in the request’s view.

Oftentimes, this subview will have interactive components that allow the user to respond to a request with a touch event. The custom view controller can interpret these events as appropriate and integrate them into the voice request flow as needed. One common pattern is to add functionality to the associated **responder** instance to handle these events in addition to the received speech recognition data. This way, both voice and graphical UI event handling are localized in the same place.

For example, consider a `VoiceRequest` subclass called `RatingRequest`, which asks the user for a rating from 1 to 10. This request could display a `UIPickerView` to allow for touch interaction. Here’s one approach to designing this class:

[insert VR Figure 4: class diagram that includes `UIPickerViewDelegate` hooked to a `PickNumberResponder` class extending the `VoiceRequestResponder` protocol]

#### Changing feedback sounds

A `VoiceRequest`‘s user interface has a relatively sparse audio output, which makes sense considering silence is needed for proper speech recognition. However, there are a few places where sounds are produced: namely when the microphone turns on/off and when prompt text is spoken. The default **soundBoard** equipped to all `VoiceRequest` instances is very flexible, offering customizable properties for setting microphone tone sound files and the ability to speak any prompt string passed to it.

A custom `VoiceRequestSoundBoard` subclass can always be substituted for the default **soundBoard**, if more advanced customization is necessary.
Dialogue Trees

Many voice interactions actually consist of a back-and-forth dialogue between the application and the user. In SayKit terms, a dialogue can be composed by chaining together multiple requests. By including conditionals in the response handling logic, the dialogue becomes dynamic and directs the user on a path through a dialogue tree.

In forthcoming releases of SayKit, additional tools will be provided to help build these dialogue trees. While implementing a complex dialogue structure is possible by imperatively chaining requests, a more declarative approach is significantly more maintainable.

[Next - Audio Production](../audio-production/)
