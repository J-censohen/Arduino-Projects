// Jia Qi Cen Sohen
// PARENT CODE

/*
  Project: Arduino I2C Controlled Audio System
  Description:
    This system uses the I2C protocol to control audio output in multiple "rooms," represented by child Arduinos, using passive buzzers. 
    The parent Arduino communicates with up to three child Arduinos, where each child can play different tunes based on instructions from the parent. 
    The parent sends commands to select a child and specify a tune, with each child having at least 2 different songs. 

    Components:
    - Parent Arduino
    - 3 Child Arduinos
    - Passive buzzers connected to each child Arduino

  Functionality:
    1. The parent Arduino prompts the user to select a child (1-3).
    2. After selecting the child, the parent asks the user to choose a tune (1-2).
    3. The parent then sends this information to the appropriate child to play the selected tune on its buzzer.
*/

#include <Wire.h>  // Include the Wire library for I2C communication

int childAddress1 = 8;  // I2C address of the first child
int childAddress2 = 7;  // I2C address of the second child
int childAddress3 = 6;  // I2C address of the third child
int answerSize = 10;    // Size of the response expected from the child
const int numQuestions = 2;  // Number of questions the parent will ask
int answer;            // Variable to store the user's child selection
int message;           // Variable to store the song choice to send to the child

void setup() {
  Wire.begin();        // Initialize the Arduino as a parent (master) for I2C communication
  Serial.begin(9600);  // Start serial communication with the user through the monitor
  Serial.println("I2C Parent Demonstration");
}

void loop() {

  // Ask the user to select which child they want to send a command to
  Serial.println("Which Child do you want to choose? (1-3)");
  while (Serial.available() == 0) { }  // Wait for user input
  answer = Serial.parseInt();  // Read the user's input

  // Based on the user's choice, send the song selection to the appropriate child
  if (answer == 1) {
    Serial.println("Which song do you want to choose? (1-2)");
    while (Serial.available() == 0) { }
    message = Serial.parseInt();  // Get the song selection from the user
    Wire.beginTransmission(childAddress1);  // Start transmission to child 1
    Wire.write(message);  // Send the song selection to child 1
    Wire.endTransmission();  // End the transmission
    delay(1000);  // Wait for 1 second before moving to the next step
  }

  if (answer == 2) {
    Serial.println("Which song do you want to choose? (1-2)");
    while (Serial.available() == 0) { }
    message = Serial.parseInt();  // Get the song selection from the user
    Wire.beginTransmission(childAddress2);  // Start transmission to child 2
    Wire.write(message);  // Send the song selection to child 2
    Wire.endTransmission();  // End the transmission
    delay(1000);  // Wait for 1 second before moving to the next step
  }

  if (answer == 3) {
    Serial.println("Which song do you want to choose? (1-2)");
    while (Serial.available() == 0) { }
    message = Serial.parseInt();  // Get the song selection from the user
    Wire.beginTransmission(childAddress3);  // Start transmission to child 3
    Wire.write(message);  // Send the song selection to child 3
    Wire.endTransmission();  // End the transmission
    delay(1000);  // Wait for 1 second before moving to the next step
  }
}

