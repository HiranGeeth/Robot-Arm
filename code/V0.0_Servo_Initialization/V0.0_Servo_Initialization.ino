/********************************************************************
2025_03_08
Servo Initialization programme used to check the performance of individual servos
Supplimentary tool for individual inspection
********************************************************************/

#include <ESP32Servo.h>

Servo myservo;  
int pos = 0;    

void setup() {
  myservo.attach(33);  // Attach the servo to GPIO pin
}

void loop() {
  // Move from 0 to 180 degrees
  for (pos = 90; pos <= 180; pos += 1) {  
    myservo.write(pos);
    delay(pos/20);  // Adjust for smoother motion
  }
  delay(1000); // Pause at the end

  // Move from 180 to 0 degrees
  for (pos = 180; pos >= 90; pos -= 1) {  
    myservo.write(pos);
    delay(pos/20);
  }
  delay(1000);
}