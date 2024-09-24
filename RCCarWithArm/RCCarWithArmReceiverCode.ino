/*
Task: This code is used to receive data from the Bluetooth controller and control a car with an attached robot arm. 
      The car's motors and the arm's joints/gripper are controlled based on incoming serial commands. Servo motors 
      handle the arm's movement, while the car is controlled using H-bridge motor signals.

RECEIVER CODE
*/

#include <Servo.h> // Include Servo library

// Pin assignments for car motors, Bluetooth module, and servo joints
int in1 = 2, in2 = 4, in3 = 7, in4 = 8, BT = 13;
int joint1Pin = 9, joint2Pin = 10, joint3Pin = 11, gripperPin = 3, servoPowerPin = 12;

// Initial angles for the arm joints and gripper
int j1Angle = 90, j2Angle = 110, j3Angle = 120, gripperAngle = 150;  

// Declare Servo objects for each arm joint and gripper
Servo joint1;
Servo joint2; 
Servo joint3; 
Servo gripper;

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud

  // Setup motor pins as output for the car's movement
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  pinMode(BT, OUTPUT); // Bluetooth power indicator pin
  pinMode(servoPowerPin, OUTPUT); // Servo power control pin

  // Attach the servos to their respective pins
  joint1.attach(joint1Pin);
  joint2.attach(joint2Pin);
  joint3.attach(joint3Pin);
  gripper.attach(gripperPin);

  // Set the initial positions of the joints and gripper
  joint1.write(j1Angle);
  joint2.write(j2Angle);
  joint3.write(j3Angle);
  gripper.write(gripperAngle);
}

// Function to control the car's motors
void motors(int sig1, int sig2, int sig3, int sig4){
  digitalWrite(in1, sig1); // Control motor 1 (forward/backward)
  digitalWrite(in2, sig2); // Control motor 2 (forward/backward)
  digitalWrite(in3, sig3); // Control motor 3 (turning)
  digitalWrite(in4, sig4); // Control motor 4 (turning)
}

// Function to enforce limits on servo angles to avoid over-rotation
void limits(){
  if(j1Angle > 180) j1Angle = 180; // Max angle for joint 1
  if(j1Angle < 0) j1Angle = 0;     // Min angle for joint 1
  if(j2Angle > 180) j2Angle = 180; // Max angle for joint 2
  if(j2Angle < 0) j2Angle = 0;     // Min angle for joint 2
  if(j3Angle > 180) j3Angle = 180; // Max angle for joint 3
  if(j3Angle < 0) j3Angle = 0;     // Min angle for joint 3
}

// Function to read serial data and control the car and arm accordingly
void controlData(){
  if(Serial.available() > 0){ // Check if there is data available
    int data = Serial.read(); // Read the incoming data

    // Control car movement or arm based on the received data
    switch(data){
      case '1': 
        motors(0, 255, 0, 255);  // Move forward
        break;
      case '2': 
        motors(255, 0, 255, 0);  // Move backward
        break;
      case '3': 
        motors(0, 255, 255, 0);  // Turn right
        break;
      case '4': 
        motors(255, 0, 0, 255);  // Turn left
        break;
      case '5':
        motors(255, 255, 255, 255); // Stop all motors (neutral)
        break;
      case 'a':
        j1Angle--;  // Decrease joint 1 angle (move joint 1)
        break;
      case 'b':
        j1Angle++;  // Increase joint 1 angle
        break;
      case 'c':
        j2Angle--;  // Decrease joint 2 angle (move joint 2)
        break;
      case 'd':
        j2Angle++;  // Increase joint 2 angle
        break;
      case 'e':
        j3Angle--;  // Decrease joint 3 angle (move joint 3)
        break;
      case 'f':
        j3Angle++;  // Increase joint 3 angle
        break;
      case 'g':
        gripperAngle = 150; // Close gripper
        break;
      case 'h':
        gripperAngle = 180; // Open gripper
        break;
      default:
        break;
    }
  }
}

// Main loop: continuously read control data and adjust motor/servo positions
void loop() {
  digitalWrite(BT, HIGH); // Ensure Bluetooth is powered
  digitalWrite(servoPowerPin, HIGH); // Ensure servos are powered

  // Write the current angles to the servos for the arm and gripper
  joint1.write(j1Angle);
  joint2.write(j2Angle);
  joint3.write(j3Angle);
  gripper.write(gripperAngle);

  limits();       // Ensure the joint angles stay within allowed limits
  controlData();  // Process any incoming serial data and act accordingly
}
