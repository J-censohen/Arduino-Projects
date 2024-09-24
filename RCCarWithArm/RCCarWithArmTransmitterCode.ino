/*  
Task: This code is used to control a Bluetooth car with a robot arm attached. The controller switches between drive mode 
      (for controlling the car's movements) and arm mode (for controlling the arm). The joystick inputs are read to 
      control either the car or the robot arm. Data is sent over Bluetooth to the car using Serial communication.

TRANSMITTER CODE
*/

int left1 = A0, left2 = A1, right1 = A2, right2 = A3, button = 11, arm = 12, drive = 13;  // Pin assignments for joysticks and control signals

void setup() {
  Serial.begin(9600);                               // Start serial communication at 9600 baud
  pinMode(left1, INPUT);                            // Set left joystick (axis 1) as input
  pinMode(left2, INPUT);                            // Set left joystick (axis 2) as input
  pinMode(right1, INPUT);                           // Set right joystick (axis 1) as input
  pinMode(right2, INPUT);                           // Set right joystick (axis 2) as input
  pinMode(button, INPUT);                           // Set mode toggle button as input
  pinMode(arm, OUTPUT);                             // Set arm control pin as output
  pinMode(drive, OUTPUT);                           // Set drive control pin as output
}

int upper = 550, lower = 480, toggle = 0;           // Thresholds for joystick control and mode toggle variable

void loop(){
  delay(20);                                        // Small delay for processing stabilization

  if(digitalRead(button) == HIGH){                  // Check if toggle button is pressed to switch modes
    delay(200);                                     // Debounce delay to prevent double toggling
    toggle++;                                       // Increase toggle counter
  }

  if(toggle % 2 == 1){                              // If toggle is odd, set to drive mode
    // Drive mode
    digitalWrite(drive, HIGH);                      // Activate drive system, deactivate arm system
    digitalWrite(arm, LOW);
    int fb = analogRead(left2);                     // Read forward/backward from left joystick (y-axis)
    int lr = analogRead(right2);                    // Read left/right from right joystick (x-axis)

    // Send serial commands based on joystick input for car movement
    if(fb > upper) Serial.write("1");               // Move forward
    if(fb < lower) Serial.write("2");               // Move backward
    if(lr > upper + 100) Serial.write("3");         // Turn right
    if(lr < lower - 100) Serial.write("4");         // Turn left
    if(fb < upper && fb > lower && lr < upper && lr > lower) Serial.write("5"); // Neutral position (no movement)
  } 
  else if (toggle % 2 == 0){                        // If toggle is even, set to arm mode
    // Arm mode
    digitalWrite(arm, HIGH);                        // Activate arm system, deactivate drive system
    digitalWrite(drive, LOW);
    int j1 = analogRead(left2);                     // Read joint 1 (y-axis of left joystick)
    int j2 = analogRead(left1);                     // Read joint 2 (x-axis of left joystick)
    int j3 = analogRead(right1);                    // Read joint 3 (x-axis of right joystick)
    int gr = analogRead(right2);                    // Read gripper control (y-axis of right joystick)

    // Send serial commands based on joystick input for robot arm control
    if(j1 > upper) Serial.write("a");               // Move joint 1 upwards
    if(j1 < lower) Serial.write("b");               // Move joint 1 downwards
    if(j2 > upper) Serial.write("c");               // Move joint 2 right
    if(j2 < lower) Serial.write("d");               // Move joint 2 left
    if(j3 > upper) Serial.write("e");               // Move joint 3 upwards
    if(j3 < lower) Serial.write("f");               // Move joint 3 downwards
    if(gr > 1000) Serial.write("g");                // Close gripper
    if(gr < 100) Serial.write("h");                 // Open gripper
  }
}
