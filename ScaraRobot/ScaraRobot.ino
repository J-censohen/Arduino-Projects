/*
Author: Jia Qi Cen Sohen
Date: 5/15/2024

Task: Allow the SCARA manipulator to interpolate between specified X and Y coordinates, creating smooth movement 
between points using inverse kinematics equations. The program calculates joint angles to move the TCP (Tool Center Point)
from one point to another, with control over speed and delay for smooth transitions.
*/

#include <math.h>                                                           // Include math library for inverse trig functions
#include <Servo.h>                                                          // Include servo library for easier control over the servo motors

Servo joint1;                                                               // Declare first joint as object in the program
Servo joint2;                                                               // Declare second joint as object in the program

void setup() {
  joint1.attach(9);                                                         // Initialize joint 1 servo on pin 9
  joint2.attach(10);                                                        // Initialize joint 2 servo on pin 10
}

float joint1Prev = 90, joint2Prev = 90, joint1Angle = 0, joint2Angle = 0;   // Variables for previous and current joint angles
float a1 = 2.406, a3 = 2.594;                                               // Length constants for SCARA arms

float theta0(float x, float y, float r){                                    // Function to calculate theta 0 using inverse kinematics
  float phi2 = atan(y / x);                                                 // Calculate angle to the point (equation 3)
  float phi1 = acos(((a3 * a3) - (a1 * a1) - (r * r)) / (-2 * a1 * r));     // Calculate using cosine law (equation 4)
  return((phi2 + phi1) * (180 / M_PI));                                     // Return result in degrees (equation 2)
}

float theta1(float x, float y, float r){                                    // Function to calculate theta 1 using inverse kinematics
  float phi3 = acos(((r * r) - (a1 * a1) - (a3 * a3)) / (-2 * a3 * a1));    // Calculate using cosine law (equation 6)
  return((M_PI - phi3) * (180 / M_PI));                                     // Return result in degrees (equation 5)
}

void goTo(float x, float y, int speed, int waitTime){
  /*
  goTo(); function provides control over the servo motors to move them gradually instead of instantly to avoid damaging hardware.
  This function calculates joint angles using the inverse kinematic equations, then adjusts the servo positions in small increments.
  */
  float r = sqrt((x * x) + (y * y));                                        // Calculate the radial distance to the point (x, y)
  
  if(x >= 0){                                                               // If X is positive or zero, calculate angles accordingly
    joint1Angle = (180 - theta0(x, y, r));                                  
    joint2Angle = (90 + theta1(x, y, r));                                   
  } else {                                                                  // If X is negative, adjust calculations for the arm's reflection
    joint1Angle = (theta0(-x, y, r));
    joint2Angle = (90 - theta1(-x, y, r));
  }

  // Gradually move joint 1 to the new angle with controlled speed
  if(joint1Angle > joint1Prev){
    for(joint1Prev; joint1Prev <= joint1Angle; joint1Prev++){
      joint1.write(joint1Prev);
      delay(speed);
    }
  } else if (joint1Angle < joint1Prev){
    for(joint1Prev; joint1Prev >= joint1Angle; joint1Prev--){
      joint1.write(joint1Prev);
      delay(speed);
    }
  }

  // Gradually move joint 2 to the new angle with controlled speed
  if(joint2Angle > joint2Prev){
    for(joint2Prev; joint2Prev <= joint2Angle; joint2Prev++){
      joint2.write(joint2Prev);
      delay(speed);
    }
  } else if (joint2Angle < joint2Prev){
    for(joint2Prev; joint2Prev >= joint2Angle; joint2Prev--){
      joint2.write(joint2Prev);
      delay(speed);
    }
  }

  delay(waitTime);                                                          // Wait after movement to stabilize the SCARA arm
}

void interpolate(float x1, float y1, float x2, float y2){
  /*
  The interpolate(); function allows for smooth movement between two points by breaking the path into small steps.
  Instead of moving directly from one point to the next, the arm follows a linear path using small increments along both axes.
  */
  const float set1 = 1, set2 = 1;                                           // Set delay times for controlled motion
  const float limit = 20;                                                   // Number of interpolation steps
  
  float dy = (y2 - y1) / limit;                                             // Calculate change in Y divided by number of steps
  float dx = (x2 - x1) / limit;                                             // Calculate change in X divided by number of steps
  
  for(float i = 0; i <= limit; i++){                                        // Loop through each step to interpolate between points
    goTo(x1 + dx * i, y1 + dy * i, set1, set2);                             // Move the SCARA arm to each interpolated point
  }
}

// Arrays holding X and Y coordinates for movement sequence (from Processing program)
float x[] = {1.0, 2.0, 3.0, 2.5, 1.5};                                      // Example X coordinates (replace with actual values)
float y[] = {4.0, 3.0, 2.0, 3.5, 4.5};                                      // Example Y coordinates (replace with actual values)
int items = sizeof(x) / sizeof(x[0]) - 1;                                   // Calculate number of points in the array

void loop() {
  // Interpolate between each consecutive pair of points in the arrays
  for(int i = 0; i < items; i++){
    interpolate(x[i], y[i], x[i + 1], y[i + 1]);                            // Move smoothly from point to point
  }
  
  goTo(x[0], y[0], 5, 200);                                                 // Return to the first point after completing the path
}
