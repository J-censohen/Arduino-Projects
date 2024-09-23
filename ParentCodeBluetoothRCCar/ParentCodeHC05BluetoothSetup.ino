/*
  Project Title: HC-05 Bluetooth Module Parent Code
  Author: Jia Qi Cen Sohen
  Date: 3/22/2024

  Project Description:
  This code sets up an Arduino as a parent controller that communicates with a Bluetooth module (HC-05).
  It continuously sends control signals ('1' and '0') to indicate specific actions or commands. 
  The signals are transmitted every 2 seconds, allowing a connected device (the child or receiver) to respond to these commands.
*/

#include <SoftwareSerial.h> // Include the SoftwareSerial library to enable serial communication on other pins

// Declare & initialize a software serial for the Bluetooth module
// RX pin is connected to pin 10, and TX pin is connected to pin 11
SoftwareSerial BTSerial(10, 11);  // (RX, TX)
// NOTE: Connect the BT module wires as follows:
// TXD lead goes to RX pin (10) and RXD goes to TX pin (11)

void setup() {
  // Initialize the BTSerial communication at a baud rate of 9600
  BTSerial.begin(9600);
}

void loop() {
  // Transmit '1' to the Bluetooth module every 2 seconds to indicate a control signal
  BTSerial.write('1'); // Send command '1' to indicate an action
  delay(2000); // Wait for 2 seconds
  
  // Transmit '0' to the Bluetooth module every 2 seconds to indicate a stop signal
  BTSerial.write('0'); // Send command '0' to stop the action
  delay(2000); // Wait for 2 seconds before repeating
}
