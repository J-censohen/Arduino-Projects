/*
  Project Title: RC Car Control via Bluetooth with Joystick
  Author: Jia Qi Cen Sohen
  Date: 3/23/24

  Project Description:
  This code is for controlling an RC car via Bluetooth using the HC-05 module. It reads the X and Y-axis values 
  from a joystick connected to an Arduino and sends control signals via serial communication. Based on the joystick 
  position, different commands ('1', '2', '3', '4', or '5') are sent to control the movement of the car.

  Controls:
  - '1' is sent when the joystick is pushed left.
  - '2' is sent when the joystick is pushed right.
  - '3' is sent when the joystick is pushed down.
  - '4' is sent when the joystick is pushed up.
  - '5' is sent when the joystick is in the neutral (center) position.
*/

int yRead = A2, xRead = A1; // Define the pins for Y-axis (A2) and X-axis (A1) of the joystick

void setup() {
  pinMode(yRead, INPUT); // Set Y-axis pin as input
  pinMode(xRead, INPUT); // Set X-axis pin as input
  Serial.begin(9600);    // Initialize serial communication at a baud rate of 9600 for Bluetooth communication
}

void loop() {
  // Check if the joystick is pushed to the left (X-axis value < 400)
  if (analogRead(xRead) < 400) {
    Serial.write("1"); // Send '1' via Bluetooth (move left)
  }
  // Check if the joystick is pushed to the right (X-axis value > 600)
  else if (analogRead(xRead) > 600) {
    Serial.write("2"); // Send '2' via Bluetooth (move right)
  }
  // Check if the joystick is pushed down (Y-axis value < 400)
  else if (analogRead(yRead) < 400) {
    Serial.write("3"); // Send '3' via Bluetooth (move backward)
  }
  // Check if the joystick is pushed up (Y-axis value > 600)
  else if (analogRead(yRead) > 600) {
    Serial.write("4"); // Send '4' via Bluetooth (move forward)
  }
  // If the joystick is in the neutral position (X and Y values between 400 and 600)
  else {
    Serial.write("5"); // Send '5' via Bluetooth (stop)
  }

  delay(200); // Small delay to avoid flooding the receiver with data
}
