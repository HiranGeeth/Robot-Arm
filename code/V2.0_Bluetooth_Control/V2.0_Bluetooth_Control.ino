/******************************************************
2025_03_15
Version 2.0 Bluetooth version allows controlling the robot arm via Bluetooth
The relevent inputs are made via Bluetooth Serial
*********************************************************/

#include <Servo.h>  //import the servo library 
#define num_servos 4  //number of servos used 
Servo servo[num_servos];  //create servo object 
 
int servo_pins[num_servos] = {2, 3, 4, 5}; //array to store the GPIO pins for the 
servo connections 
 
//Define intial positions for each servo 
int initial_pos[num_servos] = {90, 90, 90, 120}; //servo order: shoulder, forward 
drive arm, vertical drive arm, gripper 
 
//Define the minimum and maximum working ranges for each servo for the robot arm 
int min_pos[num_servos] = {0, 30, 20, 90};  //minimum postion order: shoulder, 
forward drive arm, vertical drive arm, gripper 
int max_pos[num_servos] = {180, 160, 150, 170};  //maximum position order: 
shoulder, forward drive arm, vertical drive arm, gripper 
 
int command;            //Int to store app command state 
unsigned long previousTime = 0; 
float interval = 25; 
 
void setup() { 
  for (int i = 0; i < num_servos; i++){ 
    servo[i].attach(servo_pins[i]); 
    servo[i].write(initial_pos[i]); 
    delay(500); 
  } 
  Serial.begin(9600); 
} 
 
// rotate shoulder to the left 
void shoulder_left(){ 
  if (initial_pos[1] < max_pos[1]){ 
    unsigned long currentTime = millis(); 
    if (currentTime - previousTime >= interval) { 
      previousTime = currentTime; 
      initial_pos[1]++; 
      servo[1].write(initial_pos[1]); 
    } 
  }    
} 
 
// rotate shoulder to the right 
void shoulder_right(){ 
  if (initial_pos[1] > min_pos[1]){ 
 
    unsigned long currentTime = millis(); 
    if (currentTime - previousTime >= interval) { 
      previousTime = currentTime; 
      initial_pos[1]--; 
      servo[1].write(initial_pos[1]); 
    } 
  }    
} 
 
// rotate forward drive arm downwards 
void forward_down(){ 
  if (initial_pos[2] < max_pos[2]){ 
    unsigned long currentTime = millis(); 
    if (currentTime - previousTime >= interval) { 
      previousTime = currentTime; 
      initial_pos[2]++; 
      servo[2].write(initial_pos[2]); 
    } 
  }    
} 
 
// rotate forward drive arm upwards 
void forward_up(){ 
  if (initial_pos[2] > min_pos[2]){ 
    unsigned long currentTime = millis(); 
    if (currentTime - previousTime >= interval) { 
      previousTime = currentTime; 
      initial_pos[2]--; 
      servo[2].write(initial_pos[2]); 
    } 
  }    
} 
 
// rotate vertical drive arm upwards 
void vertical_down(){ 
  if (initial_pos[3] < max_pos[3]){ 
    unsigned long currentTime = millis(); 
    if (currentTime - previousTime >= interval) { 
      previousTime = currentTime; 
      initial_pos[3]++; 
      servo[3].write(initial_pos[3]); 
    } 
  }    
} 
 
// rotate vertical drive arm downwards 
void vertical_up(){ 
  if (initial_pos[3] > min_pos[3]){ 
 
    unsigned long currentTime = millis(); 
    if (currentTime - previousTime >= interval) { 
      previousTime = currentTime; 
      initial_pos[3]--; 
      servo[3].write(initial_pos[3]); 
    } 
  }    
} 
 
//close gripper 
void gripper_close(){ 
  if (initial_pos[4] < max_pos[4]){ 
    unsigned long currentTime = millis(); 
    if (currentTime - previousTime >= interval) { 
      previousTime = currentTime; 
      initial_pos[4]++; 
      servo[4].write(initial_pos[4]); 
    } 
  }    
} 
 
//open gripper 
void gripper_open(){ 
  if (initial_pos[4] > min_pos[4]){ 
    unsigned long currentTime = millis(); 
    if (currentTime - previousTime >= interval) { 
      previousTime = currentTime; 
      initial_pos[4]--; 
      servo[4].write(initial_pos[4]); 
    } 
  }    
} 
 
void loop() { 
 
  if (Serial.available() > 0) { 
    command = Serial.read(); 
    switch (command) { 
      //Robot Arm Controls 
      case 'V': gripper_close(); break; 
      case 'v': gripper_open(); break; 
      case 'C': forward_down(); break; 
      case 'c': forward_up(); break; 
      case 'Z': vertical_up(); break; 
      case 'z': vertical_down(); break; 
      case 'R': shoulder_left(); break; 
      case 'r': shoulder_right(); break; 
    } 
} 
} 
