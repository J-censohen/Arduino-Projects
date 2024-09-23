/*
  Project Title: HC-05 Bluetooth Module Child Code
  Author: Jia Qi Cen Sohen
  Date: 3/22/2024

  Project Description:
  This code sets up an Arduino as the child or receiver in a Bluetooth communication system using the HC-05 module.
  The child receives control signals ('1' or '0') from the parent device and responds by turning the onboard LED on or off.
  Specifically:
  - When the child receives '1', the LED turns on.
  - When the child receives '0', the LED turns off.

  Components:
  1. HC-05 Bluetooth Module
  2. Arduino board (child/receiver)
  3. Onboard LED (used for visual feedback)
*/

#include <SoftwareSerial.h> // Include SoftwareSerial library for Bluetooth communication

// Declare & initialize a software serial for the Bluetooth module
// RX pin is connected to pin 10, and TX pin is connected to pin 11
SoftwareSerial BTSerial(10, 11);  // (RX, TX)
// NOTE: Connect the BT module wires as follows:
// TXD lead goes to RX pin (10) and RXD goes to TX pin (11)

void setup() {
  // Initialize the onboard LED (connected to the LED_BUILTIN pin)
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize BTSerial communication at a baud rate of 9600
  BTSerial.begin(9600);
}

void loop() {
  // Check if there is any data available from the Bluetooth module
  if (BTSerial.available()) {
    // Read the incoming data
    char received = BTSerial.read();

    // If the received character is '1', turn the onboard LED on
    if (received == '1') {
      digitalWrite(LED_BUILTIN, HIGH);
    } 
    // If the received character is not '1' (e.g., '0'), turn the onboard LED off
    else {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}
