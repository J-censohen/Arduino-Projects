// PARENT CODE
/*
  Description:
  This code allows the parent Arduino to send a custom message to the child Arduino via I2C.
  After sending the message, the parent sends polling requests to check if the child is ready with a response.
  The child responds with either the prepared message or a "not ready yet" message, depending on the state of the child's "gotMail" flag.
*/

#include <Wire.h> // Include the Wire library to use I2C communication

byte childAddress = 8;  // I2C address of the child Arduino (set to 8)
byte answerSize = 15;   // Expected size of the child's response (15 characters)
String message;         // Variable to store the custom message from the parent

void setup() {
  Wire.begin();         // Initialize the parent Arduino as an I2C master (no address required)
  Serial.begin(9600);   // Initialize serial communication at 9600 baud rate for user interaction
}

void loop() {
  // Ask the user to input a custom message via the Serial Monitor
  Serial.println("What is your message?");
  message = "";  // Clear the message to ensure new messages don't concatenate with previous ones

  // Wait for the user to type a message into the Serial Monitor
  while(Serial.available() == 0) { }
  message = Serial.readString();  // Read the user's message as a string

  // Begin I2C transmission to the child device with the address 8
  Wire.beginTransmission(childAddress);
  Wire.write(message.c_str());    // Send the user's message as a C-string (char array)
  Wire.endTransmission();         // End the I2C transmission

  delay(5000);  // Wait for 5 seconds before polling the child for a response

  // Request a response from the child Arduino, expecting a message of `answerSize` bytes
  Wire.requestFrom(childAddress, answerSize); 

  // While data is available from the child, read and print each character
  while (Wire.available()) {
    char c = Wire.read();  // Receive a byte as a character
    Serial.print(c);       // Print the character to the Serial Monitor
  }
  Serial.println();  // Add a new line after the response is printed

  delay(5000);  // Wait for 5 seconds before the next loop iteration
}
