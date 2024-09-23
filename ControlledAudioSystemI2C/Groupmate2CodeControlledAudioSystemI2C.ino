/*Groupmate 2's Work*/

#include <Wire.h>
//mahir 
const int buzzer = 7;
int message;
int childAddress = 6;
int c;
int C = 262, D = 294, E = 330, F = 349,G1 = 98, rest = 0;
int G2 = 392, A = 440, a = 466, B = 494, G = 49, C1 = 523;


void setup() {
  Wire.begin(childAddress);
  Wire.onReceive(receiveEvent);
  pinMode(buzzer, OUTPUT);
}


void childMelody1(){
  Note(C,670,670);
  Note(C,670,670);
  Note(D,1340,670);
  Note(B,670,670);
  Note(B,670,670);
}




void childMelody2(){
  Note(A,1340,670);
  Note(E,335,670);
  Note(E,335,670);
  Note(E,335,670);
  Note(E,335,670);
  Note(A,1340,670);
}


void Note(int freq, int pause, int pause2){
  tone(buzzer, freq);
  delay(pause);
  noTone(buzzer);
  delay(pause2);
}


void loop(){
    if(message == 1){
      Serial.println("Playing melody 1!");
       Serial.println("Playing melody 1!");
      childMelody1();


       }
   


      if (message == 2){
      Serial.println("Playing melody 2!");
      childMelody2();


       }


   
 
  Serial.println(); // Print a newline at the end of the message


}




void receiveEvent(int howMany) {
  while (Wire.available()) { // Loop while there are bytes to read
    char c = Wire.read(); // Read a byte as a character
     message += c;
}}






