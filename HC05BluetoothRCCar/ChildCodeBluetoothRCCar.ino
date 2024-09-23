/*
  Project Title: RC Car Movement Control via Bluetooth
  Author: Jia Qi Cen Sohen
  Date: 3/24/2024

  Project Description:
  This code is for the child Arduino in an RC car controlled by the parent Arduino via Bluetooth using the HC-05 module. 
  The child Arduino receives serial commands ('1', '2', '3', '4', '5') and controls the motors accordingly to move the car.
  
  Motor Control:
  - '1' moves the car forward.
  - '2' moves the car backward.
  - '3' turns the car left.
  - '4' turns the car right.
  - '5' stops the car.

  Pin Configuration:
  - Pins 5 and 6 control the left motor (forward and backward).
  - Pins 9 and 10 control the right motor (forward and backward).
  - Pins 3 and 11 are used for enabling the motors (speed control).
*/

int left1 = 5;   // Pin controlling the left motor's forward direction
int left2 = 6;   // Pin controlling the left motor's backward direction
int right1 = 9;  // Pin controlling the right motor's forward direction
int right2 = 10; // Pin controlling the right motor's backward direction
int en1 = 3;     // Pin controlling the enable (speed) for the left motor
int en2 = 11;    // Pin controlling the enable (speed) for the right motor

void setup() {
  // Begin serial communication at 9600 baud rate to receive data from the parent Arduino
  Serial.begin(9600);
  
  // Set motor control pins as outputs
  pinMode(left1, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
}

void loop() {
  // Set motor enable pins to HIGH (turn motors on with default speed)
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);

  // Check if data is available from the serial communication (Bluetooth)
  if (Serial.available() > 0) {
    // Read the incoming data (command from parent)
    int data = Serial.read();
    
    // Switch statement to control the motors based on the received command
    switch(data) {
      // Case '1': Move the car forward
      case '1':
        digitalWrite(left1, HIGH);  // Left motor forward
        digitalWrite(right1, HIGH); // Right motor forward
        digitalWrite(left2, LOW);   // Left motor not moving backward
        digitalWrite(right2, LOW);  // Right motor not moving backward
        break;
        
      // Case '2': Move the car backward
      case '2':
        digitalWrite(left1, LOW);   // Left motor not moving forward
        digitalWrite(right1, LOW);  // Right motor not moving forward
        digitalWrite(left2, HIGH);  // Left motor backward
        digitalWrite(right2, HIGH); // Right motor backward
        break;

      // Case '4': Turn the car right
      case '4':
        digitalWrite(left1, HIGH);  // Left motor forward
        digitalWrite(right1, LOW);  // Right motor stops
        digitalWrite(left2, LOW);   // Left motor not moving backward
        digitalWrite(right2, HIGH); // Right motor backward
        break;

      // Case '3': Turn the car left
      case '3':
        digitalWrite(left1, LOW);   // Left motor stops
        digitalWrite(right1, HIGH); // Right motor forward
        digitalWrite(left2, HIGH);  // Left motor backward
        digitalWrite(right2, LOW);  // Right motor not moving backward
        break;

      // Case '5': Stop the car (both motors stop)
      case '5':
        digitalWrite(left1, LOW);   // Left motor off
        digitalWrite(left2, LOW);   // Left motor off
        digitalWrite(right1, LOW);  // Right motor off
        digitalWrite(right2, LOW);  // Right motor off
        break;

      // Default: Do nothing if an unrecognized command is received
      default:
        break;
    }
  }
}
