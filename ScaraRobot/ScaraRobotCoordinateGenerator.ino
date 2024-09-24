// Author: Jia Qi Cen Sohen
// Date: 5/9/2024
// Project: SCARA Manipulator Toolpath Generator
// Description: This program generates x and y coordinates from mouse input,
//              which are used to control the TCP (Tool Center Point) of a SCARA manipulator.
//              The coordinates are printed as arrays of float values for use in inverse kinematics calculations.

void setup() {
  // Set canvas size to 500x500 pixels
  size(500,500); 

  // Draw outer circle (simulating SCARA workspace boundary)
  arc(0, 0, 1000, 1000, 0, 2 * PI); 

  // Draw inner circle (simulating a restricted workspace boundary)
  arc(0, 0, 550, 550, 0, 2 * PI); 

  // Print program information in the console
  println("COORDINATE TOOLPATH GENERATOR - COPY PASTE INTO DESIGNATED SPOT IN PROGRAM CODE");
  println("");
}

// Variables to store generated coordinates
String x = ""; // Holds x coordinates as a string
String y = ""; // Holds y coordinates as a string
String lastX = ""; // Stores the last x coordinate
String lastY = ""; // Stores the last y coordinate
int count = 0; // Counter to keep track of the number of points

void draw() {
  // Check if the left mouse button is pressed
  if (mousePressed && (mouseButton == LEFT)) {
    // Draw a small circle at the current mouse position
    circle(mouseX, mouseY, 15);

    // Convert mouse position to coordinates (scaled down by 100)
    float xPos = mouseX / 100.0;
    float yPos = mouseY / 100.0;

    // Update the last x and y positions
    lastX = String.valueOf(xPos);
    lastY = String.valueOf(yPos);

    // Append current x and y coordinates to the respective strings
    x = x + String.valueOf(xPos) + ", ";
    y = y + String.valueOf(yPos) + ", ";

    // Increment the point counter
    count++;

    // Introduce a small delay to avoid rapid input
    delay(50);
  }

  // Check if the right mouse button is pressed
  if (mousePressed && (mouseButton == RIGHT)) {
    // Print the total number of points
    println("");
    println("int items = " + String.valueOf(count + 1) + ";");

    // Print the array of x coordinates
    println("float x[" + String.valueOf(count + 1) + "] = {" + x + lastX + "};");

    // Print the array of y coordinates
    print("float y[" + String.valueOf(count + 1) + "] = {" + y + lastY + "};");

    // Delay to prevent multiple output on a single right-click
    delay(1000);
  }
}
