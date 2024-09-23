/*
  Project Title: Arduino Joystick to Servo Control via UART
  Author: Jia Qi Cen Sohen
  Date: 2/27/2023

  Project Description:
  This project creates a system where a Transmitter Arduino reads the X-axis position of a joystick and 
  sends this position to a Receiver Arduino via UART. The Receiver Arduino uses the transmitted data 
  to adjust the angle of a servo motor accordingly. Additionally, a button press on the Transmitter 
  will reset the servo motor to its default position.

  The project could be expanded to include math functions that calculate the angle of rotation based on 
  the joystick's movement, making it more precise for controlling an RC car or other applications.

  Components:
  1. Joystick (connected to the Transmitter Arduino)
  2. Button (connected to the Transmitter Arduino)
  3. Servo motor (connected to the Receiver Arduino)
  4. Two Arduino boards (one for Transmitter, one for Receiver)
  5. UART communication for transmitting joystick position data
  
  Task Breakdown:
  1. Read the joystick's X-axis value and categorize the movement into left, right, or reset.
  2. Send the data via UART ('1', '2', or '3') to the Receiver Arduino.
  3. The Receiver Arduino will control a servo motor based on the received data.

  CHILD CODE
*/

int xPin = A0; // Pin connected to the X-axis of the joystick (analog pin)
int button = 2; // Pin connected to the button (digital pin)

// Variables to store the analog value from the X-axis and the calculated angle
int xValue; // To store value of the X axis
int Xangle = 0; // Store x angle (not currently used)

void setup() {
  pinMode(xPin, INPUT); // Set the X-axis pin as input to read joystick position
  pinMode(button, INPUT); // Set the button pin as input to detect button presses
  Serial.begin(9600); // Start serial communication with a baud rate of 9600
}

void loop() {
  // Read the analog value from the X-axis joystick pin
  xValue = analogRead(xPin); // Capture joystick position
  
  // Call the function to control the servo based on the joystick position
  servoControl(xValue); // Pass the X-axis value to the servo control function
  
  delay(10); // Small delay to avoid overwhelming the receiver
}

// Function to control the servo based on the joystick input
void servoControl(int x) {
  // Determine how the joystick will control the servo rotation:
  
  // If X-axis value is greater than 500, send '1' to the receiver (rotate servo right)
  if (x > 500) {
    Serial.write('1'); // Send character '1' via UART to the receiver for right rotation
  } 
  // If X-axis value is less than 492, send '2' to the receiver (rotate servo left)
  else if (x < 492) {
    Serial.write('2'); // Send character '2' via UART to the receiver for left rotation
  } 
  // If the button is pressed (button pin reads LOW), send '3' to reset the servo position
  else if (digitalRead(button) == LOW) {
    Serial.write('3'); // Send character '3' via UART to reset the servo to default position
  }
}

// How to Use:
// Transmitter Arduino: Connect the joystick's X-axis pin to A0 and the button to digital pin 2. 
// The Serial.write() commands will send data ('1', '2', or '3') to the Receiver Arduino via UART.
// Receiver Arduino: This will receive the commands and control a servo motor. You would need a separate script for this.
