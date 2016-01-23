# SayKit Tour

> Welcome to the developer preview tour! We'll be fleshing out this document and including more extensive developer guides as we prepare this developer preview for full public release.
> 
> For now, enjoy your tour, and feel free to drop us a line to let us know what you think.

## So, you want to have a talking app...

At the most basic level, a conversational UI has only two requirements: a way to listen to user speech and a way to speak back to the user.

On the surface, that’s not much:

1. Grab a speech recognizer library
2. Grab speech synthesizer library
3. ?
4. Profit!

There are plenty of off-the shelf solutions to steps 1 & 2. Step 3 though? Now that's a different story. 

Once you know what the user said, **what do you do with it**? How you extract meaning from it? Who should be responsible for responding to the user's commands? Should different agents to handle different types of commands? How should you design that?

What if you **want your app to carry on a dialogue with the user**? How do you design that without creating a complete rats nest of conditionals and callbacks? If you want your app to have a conversational feel, how will you avoid making it sound like machine reading from a script?

If your app is non-trivial, **how will you organize all of this**? If you have a complex visual hierarchy, how will you integrate this new audio interface with it? How will you ensure different areas play nicely with each other and share the speaker? How will you keep it DRY and avoid repeating logic in your visual and audio UIs?

SayKit is here to help you answer all of these questions (and many more). Continue with your tour to learn more.

[Next - Overview >>](./01-overview.md)
