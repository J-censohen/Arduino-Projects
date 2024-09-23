/*
  Project Title: Arduino Joystick to Servo Control via UART
  Author: Jia Qi Cen Sohen
  Date: 2/27/2023

  Project Description:
  This project creates a system where a Transmitter Arduino reads the X-axis position of a joystick and 
  sends this position to a Receiver Arduino via UART. The Receiver Arduino uses the transmitted data 
  to adjust the angle of a servo motor accordingly. Additionally, a button press on the Transmitter 
  will reset the servo motor to its default position.

  Components:`
  1. Joystick (connected to the Transmitter Arduino)
  2. Button (connected to the Transmitter Arduino)
  3. Servo motor (connected to the Receiver Arduino)
  4. Two Arduino boards (one for Transmitter, one for Receiver)
  5. UART communication for transmitting joystick position data
  
  Task Breakdown:
  1. Read the joystick's X-axis value and categorize the movement into left, right, or reset.
  2. Send the data via UART ('1', '2', or '3') to the Receiver Arduino.
  3. The Receiver Arduino will control a servo motor based on the received data.

  PARENT CODE
*/

int xPin = A0; // Pin connected to the X-axis of the joystick (analog pin)
int button = 2; // Pin connected to the button (digital pin)

// Variables to store the analog value from the X-axis and the calculated angle
int xValue; // To store value of the X axis
int Xangle = 0; // Store x angle (not currently used)

void setup() {
  pinMode(xPin, INPUT); // Set the X-axis pin as input
  pinMode(button, INPUT); // Set the button pin as input
  Serial.begin(9600); // Start serial communication with a baud rate of 9600
}

void loop() {
  // Read the analog value from the X-axis joystick pin
  xValue = analogRead(xPin);
  
  // Call the function to control the servo based on the joystick position
  servoControl(xValue);
  
  delay(10); // Small delay to avoid overwhelming the receiver
}

// Function to control the servo based on the joystick input
void servoControl(int x){
  // Determine how the joystick will control the servo rotation:
  // If X-axis value is greater than 500, send '1' to the receiver (rotate servo right)
  if(x > 500){
    Serial.write('1'); // Send character '1' via UART to the receiver
  } 
  // If X-axis value is less than 492, send '2' to the receiver (rotate servo left)
  else if(x < 492){
    Serial.write('2'); // Send character '2' via UART to the receiver
  } 
  // If the button is pressed (button pin reads LOW), send '3' to reset the servo position
  else if (digitalRead(button) == LOW){
    Serial.write('3'); // Send character '3' via UART to reset the servo
  }
}
