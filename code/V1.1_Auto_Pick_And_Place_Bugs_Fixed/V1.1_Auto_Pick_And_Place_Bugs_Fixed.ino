/**********************************************
2025_03_13
Version 1.1 facilitates picking an object and placing at the place position at pre-determined servo angles
Bugs Fixed -Protecting the initial angles array during operation by duplicating
A more stable and reliable operation has achieved
Fixed bugs in the manufacturer given programme of operation
***********************************************/

#include <ESP32Servo.h>

// Define the number of servos
#define NUM_SERVOS 4

// Create servo objects
Servo servos[NUM_SERVOS];

// Define the servo pins (choose GPIOs that support PWM)
int servoPins[NUM_SERVOS] = {25, 33, 26, 32};  // Adjust based on your ESP32 board

// Define the initial positions of the servos
int initialPositions[NUM_SERVOS] = {90, 90, 50, 40};

// Define target positions to pick up
int targetPositions[NUM_SERVOS] = {180, 130, 130, 40};

// Stores the latest servo position
int currentPositions[NUM_SERVOS];  

// Define the incremental step size
int stepSize = 1;  // You can adjust the step size for smoother movement

// Define the delay between steps (in milliseconds)
int delayTime = 5;

void setup() {

  // Start with initial positions
for (int i = 0; i < NUM_SERVOS; i++) {
  currentPositions[i] = initialPositions[i];  
}

  // Attach each servo to its corresponding pin
  for (int i = 3; i >=0; i--) {
    servos[i].attach(servoPins[i], 500, 2500); // Min and max pulse width for ESP32 servos
  }

for (int i = 3; i >=0; i--) {
  servos[i].write(initialPositions[i]);
  delay(300);
}

  // Pick operation (Reach the object)
  moveServo(0, 180);   // Rotate base
  delay(500);

  moveServo(1, 130);   // Open Gripper
  delay(500);

  moveServo(2, 130);   //Lower Shoulder
  

  // Place operation
  
  //Bring the object to the placing location
  moveServoBack(1, 90);   // Tighten gripper to grab the object
  moveServoBack(2, 50);   // Raise shoulder
  moveServoBack(0, 90);   // Rotate base
  moveServoBack(2, 140);  // Lower Shoulder
  moveServoBack(3, 70);   // Lower Arm
  moveServoBack(1, 130);  // Loosen gripper

  //Back to starting position
  moveServoBack(2, 50);   // Raise shoulder
  moveServoBack(1, 90);   // Tighten gripper

  // Stop servos to prevent jittering
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].detach();
  }

}

void loop() { }


// Function to move a servo incrementally to a target position (object pick up position)
void moveServo(int servoIndex, int targetPosition) {

  if (initialPositions[servoIndex] < targetPosition)
  {
    for(int i= initialPositions[servoIndex]; i <= targetPosition; i += stepSize )
    {
      servos[servoIndex].write(i);
      delay(delayTime);
    }
  }
  else if (initialPositions[servoIndex] > targetPosition)
  {
    for(int i= initialPositions[servoIndex]; i >= targetPosition; i -= stepSize )
    {
      servos[servoIndex].write(i);
      delay(delayTime);
    }
  }
  currentPositions[servoIndex] = targetPosition; 
}

//Function to move servos to the placing position from the target (pick up) position
void moveServoBack(int servoIndex, int placePosition) {
  if (currentPositions[servoIndex] < placePosition) {
    for (int i = currentPositions[servoIndex]; i <= placePosition; i += stepSize) {
      servos[servoIndex].write(i);
      delay(delayTime);
    }
  } 
  else if (currentPositions[servoIndex] > placePosition) {
    for (int i = currentPositions[servoIndex]; i >= placePosition; i -= stepSize) {
      servos[servoIndex].write(i);
      delay(delayTime);
    }
  }
  currentPositions[servoIndex] = placePosition;  // Update real-time position
}
