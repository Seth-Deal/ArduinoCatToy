/*
 * Author: Seth Deal
 * Company: Private Use
 * License: MIT
 * Description: Play a game with the cat!
 */

#include <Servo.h>

//servo objects
Servo servoPan;  
Servo servoTilt;

//servo current positions
int servoPanPos = 0;
int servoTiltPos = 0;

//servo starting positions
int servoPanStart = 90;
int servoTiltStart = 90;

//Buzzer
int buzzerPin = 3;

//servo pins
int servoPanPin = 5;
int servoTiltPin = 6;

//Led Pins
int bluePin = 9;
int greenPin = 10;
int redPin = 11;

//servo ranges
int servoPanRange = 90;
int servoTiltRange = 30;

//servo directions
int tiltDirection = 1;
int panDirection = 1;

//time keeping
int MAX_PLAYTIME = 300000; //5 minutes
int NORMAL_DELAY = 50;
int QUIVER_DELAY = 10;
int PAUSE_DELAY = 10000; //10 seconds
int MAX_QUIVER = 5000; //5 seconds
int playTime = 0;
int quiverTime = 0;

//randomness
int randVal = 0;
int quivRand = 5;
int pauseRand = 5;

//counters
void setup() 
{
  //attach servos
  servoPan.attach(servoPanPin);  
  servoTilt.attach(servoTiltPin);

  //attach buzzer
  pinMode(buzzerPin,OUTPUT);

  //attach LED
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
  
  //Serial
  Serial.begin(9600);
}
/*
 * param: void
 * return: void
 * Logic for the main game. Control based on the IR receiver. At the end of each game, return to the 
 * home position.
 */
void loop()
{
  //if signal received, play the game and change the light color
  setColor('g');
  playAutoGame();
  setColor('o');
  returnHome();
  //turn the light off.
}
/*
 * param: void
 * return: void
 * Turn on the laser, play a chime to alert the cat, and keep track of game time. Randomly quiver the
 * laser and pause the laser to make it more interesting for the cat
 */
void playAutoGame(){
  //turn on laser TODO
  playChime(2);
  playTime = 0;
  while(playTime <= MAX_PLAYTIME) {
    //normal movement
    moveServos(NORMAL_DELAY);
    //quiver movement
    randVal = rand() % 100;
    if(randVal <= quivRand){
      quiver(); 
    }
    //pause
    randVal = rand() % 100;
    if(randVal <= pauseRand){
      delay(PAUSE_DELAY);
      playTime += PAUSE_DELAY;
    }
  }
  //turn off laser TODO
}
/*
 * param: numChimes - Number of times to make a chime
 * return: void
 * Play the chime numChimes times
 */
void playChime(int numChimes){
  while(numChimes > 0){
    digitalWrite(buzzerPin, HIGH); // produce sound
    delay(1000);
    digitalWrite(buzzerPin, LOW); // turn it off
    delay(1000);
    numChimes -= 1;
  }
}
/*
 * param: void
 * return: void
 * Quiver the laser for the alloted time with the much shorter quiver delay
 */
void quiver(){
  quiverTime = 0;
  while(quiverTime <= MAX_QUIVER){
    moveServos(QUIVER_DELAY);
  }
}
/*
 * param: void
 * return: void
 * Return the servos to the home position
 */
void returnHome() {
  servoPan.write(servoPanStart); 
  servoTilt.write(servoTiltStart);
}
/*
 * param: color - character value of the color to assign 
 * return: void
 * Switch statement to assign the different values for certain color
 */
void setColor(char color) {
  switch (color) {
  case 'r':
    setColorHelper(255,0,0); //red
    break;
  case 'g':
    setColorHelper(0,255,0); //green
    break;
  case 'b':
    setColorHelper(0,0,255); //blue
    break;
  case 'y':
    setColorHelper(255,255,0); //yellow
    break;
  case 'p':
    setColorHelper(80,0,80); //purple
    break;
  case 'o':
    setColorHelper(0,0,0); //off
    break;
  default:
    // statements
    break;
  }
}
/*
 * param: red - value to set red hue of the LED
 * param: green - value to set green hue of the LED
 * param: blue - value to set blue hue of the LED
 * return: void
 * Use analog write on the led pins for the assigned values
 */
void setColorHelper(int red, int green, int blue){
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

/*
 * param: movementDelay - the delay between one servo movement and the next
 * return: void
 * moves the two servos in the direction defined by the direction variables. if the servos are in the
 * max position as defined by their respective variables, switch the direction of the servos. Increment
 * the playtime.
 */
void moveServos(int movementDelay) {
  if(servoPanPos == (servoPanStart + servoPanRange/2)){
    panDirection = -1;
    Serial.println("Pan going Negative");
  }
  if(servoPanPos == (servoPanStart - servoPanRange/2)){
    panDirection = 1;
    Serial.println("Pan going positive");
  }
  if(servoTiltPos == (servoTiltStart + servoTiltRange/2)){
    tiltDirection = -1;
    Serial.println("Tilt going Negative");
  }
  if(servoTiltPos == (servoTiltStart - servoTiltRange/2)){
    tiltDirection = 1;
    Serial.println("Tilt going positive");
  }
  servoTiltPos = servoTiltPos + tiltDirection;
  servoPanPos = servoPanPos + panDirection;
  servoPan.write(servoPanPos); 
  servoTilt.write(servoTiltPos); 
  delay(movementDelay); 
  playTime += movementDelay;
}
