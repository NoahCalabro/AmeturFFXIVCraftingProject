This is a project meant to try to create a code to help in the crafting system of the video game Final Fantasy 14 (FFXIV).

It is meant to take information about the player and the crafting recipe that they are intending to use, and return back the best series of steps. 

The major parts of crafting in FFXIV involve three values, Progress, Quality, and Durability. 
Progress is how far the recipe is to being completed, and it's necessary to get it to a certain value in order for the object to be crafted.
Quality is a value that determines the chance of the object to be high quality. It's not necessary to get a high value to create the object, but a high quality object is usually worith it. 
Duability is a value that determines how many actions the player can take. If it hits zero before Progress reaches a set value, the crafting fails. 
Progress and Quality start at at zero, and Durability starts at some value determined by the crafting recipe. 

The project is meant to find a sequence of actions that can be taken that will reach a the required amount of Pregress for the recipe while maximizing the Quality value.
Once it establishes information about the player and recipe, it then performs a call to a function All_Skills, which holds every possible action that the player can take, and recursively calls itself for them.

This works well for low level crafting, but with how it currently works, higher levels seem to go on for a long time, which isn't good for the users. However, given that other programs like this exist, like Teamcraft
I know it should be possible to create something like this. 
