# Developer Guide

## So, you want to have a talking app...

At the most basic level, a conversational UI has only two requirements: a way to listen to user speech and a way to speak back to the user.

[diagram of general user speech to application speech flow]

On the surface, that’s not much:

1. Plug in speech recognizer library
2. Plug in speech synthesizer library
3. ?
4. Profit!

Not surprisingly, there are a lot of considerations packed into Step 3. Among these include: natural language understanding, application context management, responding to commands, audio and graphical UI synchronization, accessibility concerns, competing speech agents, and dialogue trees. SayKit offers a framework to manage all of these concerns, along with many more, so developers can spend more time concentrating on the user experience.
