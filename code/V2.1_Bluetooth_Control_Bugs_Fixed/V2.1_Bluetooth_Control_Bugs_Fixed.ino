/****************************************************************
2025_03_16
Version 2.1 Bluetooth version allows controlling the robot arm via Bluetooth
The relevent inputs are made via Bluetooth Serial
Bugs Fixed - The performance functions are re-arranged for smoother and reliable operation
Performance is tested and verified by Serial Bluetooth Terminal Application and 
BlueDuino Joystick Application on Android
*****************************************************************/

#include <ESP32Servo.h>  // Import the servo library
#include "BluetoothSerial.h"  // Include Bluetooth library

#define num_servos 4  // Number of servos used
Servo servo[num_servos];  // Create servo objects
BluetoothSerial SerialBT; // Bluetooth Serial object

int servo_pins[num_servos] = {25, 26, 32, 33}; // GPIO pins for servos
int initial_pos[num_servos] = {90, 50, 40, 90}; // Initial positions
int current_pos[num_servos];  
int min_pos[num_servos] = {0, 50, 70, 90};  // Min positions
int max_pos[num_servos] = {180, 130, 170, 180};  // Max positions

char command;  // Store received command
unsigned long previousTime = 0;
int stepSize = 5;
int delayTime = 5;

void setup() {
    Serial.begin(9600);
    SerialBT.begin("ESP32_RobotArm"); // Bluetooth name
    
    for (int i = 0; i < num_servos; i++) {
        current_pos[i] = initial_pos[i];  
        servo[i].attach(servo_pins[i]);
        servo[i].write(initial_pos[i]);
        delay(500);
    }
}

void loop() {
    if (SerialBT.available()) {
        command = SerialBT.read();
        Serial.write(command); // Debug via Serial Monitor
        switch (command) {
            case '4': gripper_close(); break;
            case '6': gripper_open(); break;
            case '2': arm_down(); break;
            case '8': arm_up(); break;
            case 'w': shoulder_up(); break;
            case 's': shoulder_down(); break;
            case 'a': base_left(); break;
            case 'd': base_right(); break;
            //Input the given values via Blutooth to esp32 to perform the relevent actions
        }
    }
}

void moveServoUp(int servoIndex) {
    if (current_pos[servoIndex] < max_pos[servoIndex]) {
        current_pos[servoIndex] += stepSize;
        servo[servoIndex].write(current_pos[servoIndex]);
        delay(delayTime);
    }
}

void moveServoDown(int servoIndex) {
    if (current_pos[servoIndex] > min_pos[servoIndex]) {
        current_pos[servoIndex] -= stepSize;
        servo[servoIndex].write(current_pos[servoIndex]);
        delay(delayTime);
    }
}

void base_left() { moveServoDown(0); }
void base_right() { moveServoUp(0); }
void shoulder_down() { moveServoUp(1); }
void shoulder_up() { moveServoDown(1); }
void arm_down() { moveServoDown(2); }
void arm_up() { moveServoUp(2); }
void gripper_close() { moveServoDown(3); }
void gripper_open() { moveServoUp(3); }
