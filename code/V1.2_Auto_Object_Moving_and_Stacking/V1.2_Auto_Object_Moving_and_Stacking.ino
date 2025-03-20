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

delay(5000);

for (int i = 3; i >=0; i--) {
  servos[i].write(initialPositions[i]);
  delay(300);
}

//Move the Top Object Aside Temporarily
    // Pick operation (Reach the object)
    moveServo(0, 180);   // Rotate base
    delay(500);
    moveSlow(1, 130);   // Open Gripper
    delay(500);
    moveSlow(2, 110);   //Lower Shoulder
    moveSlow(3, 100);   // Extend Arm
    delay(300);
    
    // Place operation
    //Bring the object to the placing location
    moveSlow(1, 80);    // Tighten gripper to grab the object
    moveSlow(2, 50);   // Raise shoulder
    moveSlow(3, 40);   // Shorten Arm
    moveSlow(0, 140);  // Rotate base
    moveSlow(3, 70);   // Lower Arm
    moveSlow(2, 140);   // Lower Shoulder
    delay(300);
    moveServo(1, 130);  // Loosen gripper

    //Back to starting position
    moveServo(2, 50);   // Raise shoulder
    moveServo(1, 90);   // Tighten gripper

//Move the bottom object to the necessary place
    // Pick operation (Reach the object)
    moveServo(0, 180);   // Rotate base
    delay(500);
    moveServo(1, 130);   // Open Gripper
    delay(500);
    moveSlow(2, 130);   //Lower Shoulder
    moveSlow(3, 100);   // Extend Arm
    delay(300);
    
    // Place operation
    //Bring the object to the placing location
    moveSlow(1, 65);    // Tighten gripper to grab the object
    delay(500);
    moveSlow(2, 50);   // Raise shoulder
    moveSlow(3, 40);   // Shorten Arm
    moveSlow(0, 90);   // Rotate base
    moveSlow(3, 70);   // Lower Arm
    moveSlow(2, 140);   // Lower Shoulder
    delay(300);
    moveSlow(1, 130);  // Loosen gripper

    //Back to starting position
    moveServo(2, 50);   // Raise shoulder
    moveServo(1, 90);   // Tighten gripper

//Move the top object(kept aside at 140') to the top of the bottom object(at 180')
    // Pick operation (Reach the object)
    moveServo(0, 140);   // Rotate base
    delay(500);
    moveServo(1, 130);   // Open Gripper
    delay(500);
    moveSlow(2, 130);   //Lower Shoulder
    moveSlow(3, 70);   // Extend Arm
    delay(300);
    
    // Place operation
    //Bring the object to the placing location
    moveSlow(1, 80);    // Tighten gripper to grab the object
    moveServo(2, 50);   // Raise shoulder
    moveServo(3, 40);   // Shorten Arm
    moveServo(0, 90);  // Rotate base
    moveServo(3, 75);   // Lower Arm
    moveSlow(2, 120);   // Lower Shoulder
    delay(300);
    moveSlow(1, 130);  // Loosen gripper

    //Back to starting position
    moveServo(2, 50);   // Raise shoulder
    moveServo(1, 90);   // Tighten gripper








  // Stop servos to prevent jittering
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].detach();
  }

}

void loop() { }


// Function to move a servo incrementally to a given position from the current position
void moveServo(int servoIndex, int to) {

  if (currentPositions[servoIndex] < to)
  {
    for(int i= currentPositions[servoIndex]; i <= to ; i += stepSize )
    {
      servos[servoIndex].write(i);
      delay(delayTime);
    }
  }
  else if (currentPositions[servoIndex] > to)
  {
    for(int i= currentPositions[servoIndex]; i >= to; i -= stepSize )
    {
      servos[servoIndex].write(i);
      delay(delayTime);
    }
  }
  currentPositions[servoIndex] = to ; 
}


// Function to move a servo SLOWLY to a given position from the current position
void moveSlow(int servoIndex, int to) {

  if (currentPositions[servoIndex] < to)
  {
    for(int i= currentPositions[servoIndex]; i <= to ; i += stepSize )
    {
      servos[servoIndex].write(i);
      delay(delayTime+5);
    }
  }
  else if (currentPositions[servoIndex] > to)
  {
    for(int i= currentPositions[servoIndex]; i >= to; i -= stepSize )
    {
      servos[servoIndex].write(i);
      delay(delayTime+5);
    }
  }
  currentPositions[servoIndex] = to ; 
}