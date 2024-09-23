// CHILD CODE
/*
  Description:
  This code allows the child Arduino to respond to messages from the parent Arduino via I2C communication.
  The child keeps track of a "gotMail" flag which determines if it has a prepared message to send to the parent.
  When the user presses a button on the child Arduino, the flag is toggled, and the child sends either a pre-set message ("nice nice") or "null" based on the flag's state.
*/

#include <Wire.h>  // Include the Wire library to handle I2C communication

byte childAddress = 8;    // Set the I2C address for the child Arduino
int gotMail = 0;          // Flag to track if a message is ready (1 means message ready, 0 means not ready)
String response;          // Variable to store the response message (unused here)
int answer;               // Variable to store answers from the parent (unused here)
int buttonPin = 2;        // Pin for the button to toggle the gotMail flag
int buttonState = 0;      // Variable to track the current state of the button

void setup() {
  Wire.begin(childAddress);  // Initialize the child Arduino as an I2C slave with the address 8
  Wire.onReceive(receiveEvent);  // Register the function to handle receiving data from the parent
  Wire.onRequest(requestEvent);  // Register the function to handle sending data to the parent upon request
  Serial.begin(9600);  // Initialize serial communication for debugging and feedback

  // Set the button pin as an input to detect button presses
  pinMode(buttonPin, INPUT);
}

void loop() {
  // Read the current state of the button (HIGH if pressed, LOW otherwise)
  buttonState = digitalRead(buttonPin);

  // If the button is pressed, increment the gotMail flag
  if (buttonState == HIGH) {
    gotMail = gotMail + 1;  // Increase the value of gotMail by 1
  }
}

/* 
  Function to handle the event when data is received from the parent Arduino.
  This function is automatically triggered by the I2C communication when the parent sends a message.
*/
void receiveEvent(int howMany) {
  Serial.println("CHILD: Receive Event.");  // Print a message to indicate the child received data
  gotMail = 1;  // Set the gotMail flag to 1, indicating a message is ready

  // While data is available from the parent, read and print it
  while (Wire.available()) {
    char c = Wire.read();  // Read the received byte
    Serial.print(c);       // Print the received byte to the Serial Monitor
  }
  Serial.println();  // Add a newline after the received message is printed
}

/*
  Function to handle the event when the parent requests data from the child.
  This function is automatically triggered by the I2C communication when the parent requests data.
*/
void requestEvent() {
  // Check if the gotMail flag is set (odd means ready, even means not ready)
  if (gotMail % 2 == 1) {
    // If gotMail is odd, send the message "nice nice" as a response to the parent
    Wire.write("nice nice");  // Send the string "nice nice" to the parent
    Wire.write('\n');  // Send a newline character to terminate the response
  } else {
    // If gotMail is even, send "null" indicating no message is ready
    Wire.write("null");  // Send the string "null" to the parent
  }
}
