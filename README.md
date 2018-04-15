# AutomatedCatToy
An arduino powered cat toy
***
***

## Purpose:


I made the mistake of showing my cat a laser pointer one day, and she would not leave me alone when I was trying to work, to the point of knocking my coffee off the table :( 

***

### Description:


This is an automated laser pointer game activated by remote, that she can play with for a while before it automatically shuts off. It is controlled by an Arduino equiped with 2 servos, a laser pointer, and an IR receiver. 

***

### Components:

* setup()
* loop()
* startGame()
* playAutoGame()
* playChime(number of chimes)
* quiver()
* returnHome()
* setColor(color)
* setColorHelper(red, green, blue)
* moveServos(delay)
***

#### Future Plans:

1. Circuit diagram
1. Housing diagram
1. Game mode selection
1. Manual control mode
   1. Starting position selector
   1. Motion activated mode

Eventually I'd like to make a circuit diagram for the Arduino, maybe a diagram of the housing I made for it (or pictures). I'd like to implement a manual control function since the remote has arrow buttons on it (it looks like a tv remote), which would also require a way of selecting game mode (maybe hitting the number and then pound would start the game). I would also like one of the game modes to be motion activated, since I have Arduino compatible motion sensors.
