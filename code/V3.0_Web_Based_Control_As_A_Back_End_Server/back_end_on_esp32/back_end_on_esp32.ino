
#include <ESP32Servo.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

// WiFi credentials
const char* ssid = "DHARMAPALA";
const char* password = "manju@1967";

// Define the static IP configuration
IPAddress local_ip(192, 168, 1, 4);    // Static IP address
IPAddress gateway(192, 168, 1, 1);     // Gateway (usually your router's IP)
IPAddress subnet(255, 255, 255, 0);    // Subnet mask

// Set up server
WebServer server(80);

// Define the number of servos
#define NUM_SERVOS 4

// Create servo objects
Servo servos[NUM_SERVOS];

// Define the servo pins (choose GPIOs that support PWM)
int servoPins[NUM_SERVOS] = {25, 33, 26, 32};  // Adjust based on your ESP32 board

// Define the initial positions of the servos
int initialPositions[NUM_SERVOS] = {90, 90, 50, 40};

// Define target positions to pick up
int targetPositions1[NUM_SERVOS] = {180, 130, 130, 40};
int targetPositions2[NUM_SERVOS] = {135, 130, 130, 40};
int targetPositions3[NUM_SERVOS] = {45, 130, 130, 40};

// Create an array of pointers (Contains the locations of all the arrays in order)
int* targetArrays[] = {targetPositions1, targetPositions2, targetPositions3};

// Stores the latest servo position
int currentPositions[NUM_SERVOS];  

// Define the incremental step size
int stepSize = 1;  // You can adjust the step size for smoother movement

// Define the delay between steps (in milliseconds)
int delayTime = 5;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi using the static IP configuration
  WiFi.config(local_ip, gateway, subnet);
  WiFi.begin(ssid, password);
  
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected! IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Server started");
  
  //Provides an API end point to web browsers when testing. When testing, 192.168.1.4 (ESP32 IP) is reached, it sends a simple GET request to end point "/". That end point s handled here whn received.
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/plain", "ESP32 is online!");
  });

  //API end point for front end POST requests. Triggers handleSelect() function
  server.on("/select", HTTP_POST, handleSelect);
  
  server.on("/select", HTTP_OPTIONS, []() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "POST, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  server.send(204); // No Content
  });
  

  // Put initial positions into current positions
  for (int i = 0; i < NUM_SERVOS; i++) {
    currentPositions[i] = initialPositions[i];  
  }

  
}

void loop() { 
  server.handleClient(); 
  //Active at all times and triggers the path ---> server.on("/select", HTTP_POST, handleSelect);
  //TRIGGERS handleSelect(); after getting a signal from the front end web site
  }



//*****************FUNCTIONS DEFINED BELOW*******************************************************************************************





//Function to move servos to the given place position from the current position
void moveServo(int servoIndex, int placePosition) {
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

//Function to reach the object at a given position. Position is passed as an array of angles (intArr[])
void pick(int arr[4]){
  for(int i=0; i<4 ; i++)
  {
    moveServo(i,arr[i]);
    delay(300);
  }
}
//Function to bring the objects to the cart
void place(){
    //Bring the object to the placing location
    moveServo(1, 90);   // Tighten gripper to grab the object
    moveServo(2, 50);   // Raise shoulder
    moveServo(0, 90);   // Rotate base
    moveServo(2, 140);  // Lower Shoulder
    moveServo(3, 70);   // Lower Arm
    moveServo(1, 130);  // Loosen gripper

    //Back to starting position
    moveServo(2, 50);   // Raise shoulder
    moveServo(1, 90);   // Tighten gripper
  }

//Function to attach servos
void attachAllServos() {
  for (int i = 0; i < 4; i++) {
    servos[i].attach(servoPins[i]);
  }
  Serial.println("All servos attached.");
}

//Function to detch servos
void detachAllServos() {
  for (int i = 0; i < 4; i++) {
    servos[i].detach();
  }
  Serial.println("All servos detached.");
}

//Function to trigger picking and placing actions after a signal is received by the handleClient()
void handleSelect() {
  Serial.println("Received POST request at /select");

  server.sendHeader("Access-Control-Allow-Origin", "*"); // Allow any origin
  server.sendHeader("Access-Control-Allow-Methods", "POST"); // Allow POST method

  if (server.hasArg("plain") == false) {
    server.send(400, "text/plain", "Body missing");
    return;
  }

  String body = server.arg("plain");

  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, body);

  if (error) {
    server.send(400, "text/plain", "Invalid JSON");
    return;
  }

  int i = doc["product"];  // get product ID

  if (i < 1 || i > 5) {
    server.send(400, "text/plain", "Invalid product ID");
    return;
  }

  attachAllServos();
  pick(targetArrays[i - 1]);
  place();
  detachAllServos();

  server.send(200, "text/plain", "Picking product " + String(i));
}
