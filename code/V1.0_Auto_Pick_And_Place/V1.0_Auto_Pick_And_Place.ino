/************************************************************************
2025_03_10
Version 1.0 facilitates picking an object and placing at the place position at predetermined servo angles
*************************************************************************/

#include <ESP32Servo.h>

// Define the number of servos
#define NUM_SERVOS 4

// Create servo objects
Servo servos[NUM_SERVOS];

// Define the servo pins (choose GPIOs that support PWM)
int servoPins[NUM_SERVOS] = { 25, 33, 26, 32 };  // Adjust based on your ESP32 board

// Define the initial positions of the servos
int initialPositions[NUM_SERVOS] = { 90, 90, 50, 40 };

// Define target positions to pick up
int targetPositions[NUM_SERVOS] = { 180, 130, 130, 40 };

// Define the incremental step size
int stepSize = 1;  // You can adjust the step size for smoother movement

// Define the delay between steps (in milliseconds)
int delayTime = 5;

void setup() {
  // Attach each servo to its corresponding pin
  for (int i = 3; i >= 0; i--) {
    servos[i].attach(servoPins[i], 500, 2500);  // Min and max pulse width for ESP32 servos
  }

  for (int i = 3; i >= 0; i--) {
    servos[i].write(initialPositions[i]);
    delay(300);
  }

  // Pick operation (Reach the object)
  moveServo(0, 180);  // Rotate base
  delay(500);

  moveServo(1, 130);  // Open Gripper
  delay(500);

  moveServo(2, 130);  //Lower Shoulder


  // Place operation

  //Bring the object to the required location
  moveServoBack(1, 90);   // Tighten gripper to grab the object
  moveServoBack(2, 50);   // Raise shoulder
  moveServoBack(0, 90);   // Rotate base
  moveServoBack(2, 140);  // Lower Shoulder
  moveServoBack(3, 70);   // Lower Arm
  moveServoBack(1, 130);  // Loosen gripper

  //Back to starting position
  moveServoBack(2, 50);  // Raise shoulder
  moveServoBack(1, 90);  // Tighten gripper

  // Stop servos to prevent jittering
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].detach();
  }
}

void loop() {}


// Function to move a servo incrementally to a target position
void moveServo(int servoIndex, int targetPosition) {
  while (initialPositions[servoIndex] != targetPosition) {
    if (initialPositions[servoIndex] < targetPosition) {
      initialPositions[servoIndex] += stepSize;
    } else if (initialPositions[servoIndex] > targetPosition) {
      initialPositions[servoIndex] -= stepSize;
    }
    servos[servoIndex].write(initialPositions[servoIndex]);
    delay(delayTime);
  }
}

//Function to move servos to the inital positions (At this point, initial positions array have edited into target positions by the action of moveServo() function)
void moveServoBack(int servoIndex, int placePosition) {
  while (initialPositions[servoIndex] != placePosition) {
    if (initialPositions[servoIndex] < placePosition) {
      initialPositions[servoIndex] += stepSize;
    } else if (initialPositions[servoIndex] > placePosition) {
      initialPositions[servoIndex] -= stepSize;
    }
    servos[servoIndex].write(initialPositions[servoIndex]);
    delay(delayTime);
  }
}
