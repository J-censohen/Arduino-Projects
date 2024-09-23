/*Jia Qi Cen Sohen
Child 1
Description: This project demonstrates the communication between an I2C parent and child device. 
The child device receives commands (1 or 2) from the parent device, which controls 
a passive buzzer to play different melodies (Nokia Ringtone and We Wish You a Merry Christmas).
The child device is set to I2C address 8. The code includes melody definitions, note durations,
 and the logic for handling I2C requests from the parent device.
*/

#include <Wire.h> // Include the Wire library for I2C communication

// Define musical note frequencies
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35 
// (Other note definitions go here)

// Define the rest as 0
#define REST      0

int tempo1 = 180; // Tempo for the first melody
int buzzer = 7; // Pin where the buzzer is connected

// Melody 1: Nokia Ringtone
int melody1[] = {
NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, // Note followed by its duration (1/4, 1/8, etc.)
NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4,
NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
NOTE_A4, 2,
};

int notes1 = sizeof(melody1) / sizeof(melody1[0]) / 2; // Calculate the total number of notes
int wholenote1 = (60000 * 4) / tempo1; // Calculate the duration of a whole note based on tempo
int divider1 = 0, noteDuration1 = 0; // Variables for calculating note duration

int tempo2 = 140; // Tempo for the second melody

// Melody 2: We Wish You a Merry Christmas
int melody2[] = {
  NOTE_C5,4, //1st note and its duration
  NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8, // (Other notes go here)
  NOTE_F5,2, REST,4 // Last note and a rest
};

int notes2 = sizeof(melody2) / sizeof(melody2[0]) / 2; // Calculate the total number of notes
int wholenote2 = (60000 * 4) / tempo2; // Calculate the duration of a whole note based on tempo
int divider2 = 0, noteDuration2 = 0; // Variables for calculating note duration

// I2C address for the child device
byte childAddress = 8;
int gotMail = 0;
String response;

void setup() {
  Wire.begin(childAddress); // Initialize the Arduino as a child with address 8
  Wire.onRequest(requestEvent); // Register the function to run when data is requested
  Serial.begin(9600); // Start serial communication at 9600 baud rate
}

void loop() {
  // The main loop is empty as the child only responds when requested
}

// Function that runs when the parent requests data
void requestEvent() {
  while (Wire.available()) { // Loop while data is available
    int c = Wire.read(); // Read data sent from the parent
    if(c == 1){ // If parent sends '1', play Melody 1
      for (int thisNote1 = 0; thisNote1 < notes1 * 2; thisNote1 += 2) {
        divider1 = melody1[thisNote1 + 1]; // Get the note duration
        if (divider1 > 0) {
          noteDuration1 = (wholenote1) / divider1; // Calculate normal note duration
        } else {
          noteDuration1 = (wholenote1) / abs(divider1); // Calculate dotted note duration
          noteDuration1 *= 1.5; // Extend duration by 50% for dotted notes
        }
        tone(buzzer, melody1[thisNote1], noteDuration1 * 0.9); // Play the note for 90% of its duration
        delay(noteDuration1); // Pause between notes
        noTone(buzzer); // Stop the note
      }
    } 
    else if(c == 2){ // If parent sends '2', play Melody 2
      for (int thisNote2 = 0; thisNote2 < notes2 * 2; thisNote2 += 2) {
        divider2 = melody2[thisNote2 + 1]; // Get the note duration
        if (divider2 > 0) {
          noteDuration2 = (wholenote2) / divider2; // Calculate normal note duration
        } else {
          noteDuration2 = (wholenote2) / abs(divider2); // Calculate dotted note duration
          noteDuration2 *= 1.5; // Extend duration by 50% for dotted notes
        }
        tone(buzzer, melody2[thisNote2], noteDuration2 * 0.9); // Play the note for 90% of its duration
        delay(noteDuration2); // Pause between notes
        noTone(buzzer); // Stop the note
      }
    }
  }
}
