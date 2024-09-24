// Author: Jia Qi Cen Sohen
// Date: 5/12/2024
// Project: SCARA Manipulator Interpolation Testing
// Description: This program controls a SCARA manipulator using inverse kinematics.
//              It calculates joint angles to move the TCP (Tool Center Point) to specific coordinates.
//              The goTo function moves the SCARA arm from point to point, and interpolation testing is included to create smooth movement between points.

#include <math.h>
#include <Servo.h>

// Declare servo objects for the two joints
Servo joint1;
Servo joint2;

void setup() {
  // Attach servos to pins 9 and 10
  joint1.attach(9);
  joint2.attach(10);
}

// Variables to track previous and current joint angles
float joint1Prev = 90, joint2Prev = 90, joint1Angle = 0, joint2Angle = 0;

// Lengths of the SCARA manipulator's arms
float a1 = 2.406, a3 = 2.594;

// Function to calculate the angle for joint 1 using inverse kinematics
float theta0(float x, float y, float r){
  float phi2 = atan(y / x);  // Calculate the angle to the point (x, y)
  float phi1 = acos(((a3 * a3) - (a1 * a1) - (r * r)) / (-2 * a1 * r)); // Law of cosines for the first arm
  return ((phi2 + phi1) * (180 / M_PI)); // Convert from radians to degrees
}

// Function to calculate the angle for joint 2 using inverse kinematics
float theta1(float x, float y, float r){
  float phi3 = acos(((r * r) - (a1 * a1) - (a3 * a3)) / (-2 * a3 * a1)); // Law of cosines for the second arm
  return ((M_PI - phi3) * (180 / M_PI)); // Convert from radians to degrees
}

// Function to move the SCARA arm to a specified (x, y) coordinate
void goTo(float x, float y, int speed, int waitTime){
  float r = sqrt((x * x) + (y * y)); // Calculate the distance to the point (x, y)
  
  // If the x-coordinate is positive, calculate joint angles normally
  if(x >= 0){
    joint1Angle = (180 - theta0(x, y, r)); // Calculate joint 1 angle
    joint2Angle = (90 + theta1(x, y, r));  // Calculate joint 2 angle
  } 
  // If the x-coordinate is negative, adjust calculations to account for reflection
  else if(x < 0) {
    joint1Angle = (theta0(-x, y, r)); // Reflect joint 1
    joint2Angle = (90 - theta1(-x, y, r)); // Adjust joint 2 angle
  }

  // Gradually move joint 1 from its previous position to the new position
  if(joint1Angle > joint1Prev){
    for(joint1Prev; joint1Prev <= joint1Angle; joint1Prev++){
      joint1.write(joint1Prev); // Write new angle to servo
      delay(speed); // Delay to control the speed of movement
    }
  } 
  // Move joint 1 backwards if the new angle is smaller than the previous one
  else if (joint1Angle < joint1Prev){
    for(joint1Prev; joint1Prev >= joint1Angle; joint1Prev--){
      joint1.write(joint1Prev);
      delay(speed);
    }
  }

  // Gradually move joint 2 from its previous position to the new position
  if(joint2Angle > joint2Prev){
    for(joint2Prev; joint2Prev <= joint2Angle; joint2Prev++){
      joint2.write(joint2Prev);
      delay(speed);
    }
  } 
  // Move joint 2 backwards if the new angle is smaller than the previous one
  else if (joint2Angle < joint2Prev){
    for(joint2Prev; joint2Prev >= joint2Angle; joint2Prev--){
      joint2.write(joint2Prev);
      delay(speed);
    }
  }
  
  // Wait for the manipulator to stabilize after movement
  delay(waitTime);
}

// Function to interpolate between two points (x1, y1) and (x2, y2) - currently unfinished
void interpolate(float x1, float y1, float x2, float y2){
  float set1 = 1, set2 = 15; // Variables used for interpolation (not yet implemented)
  
  // If x2 is greater than x1, move gradually along the x-axis
  if(x2 > x1){
    for(float i = x1; i <= x2; i = i + 0.1){
      // Interpolation logic to be added here
    }
  }
}

// Main loop to test SCARA movement by moving the TCP along a path
void loop() {
  // Move from (0, 4) to (2.5, 4) in increments of 0.1
  for(float i = 0; i <= 2.5; i = i + 0.1){
    goTo(i, 4, 1, 15);
  }
  
  // Move from (2.5, 4) back to (0, 4) in increments of 0.1
  for(float i = 2.5; i >= 0; i = i - 0.1){
    goTo(i, 4, 1, 15);
  }
} 
