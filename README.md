# 4DOF Robot Arm

## Overview
This project is a **4DOF robotic arm** powered by a **NodeMCU 32s ESP32**. It utilizes **four SG90 servos** for movement and is designed for **automatic pick and place operations, object moving and stacking, and Bluetooth control**. Future development aims to implement **full automation via a web interface**.

## Features
- **Automatic Pick & Place**: Pre-programmed object pickup and placement.
- **Object Moving & Stacking**: Moves objects to designated locations.
- **Bluetooth Control**: Operates via an Android app.
- **Web-Based Automation (Future Development)**: Can be extended for remote object picking via a web interface.

## Components Used
- **NodeMCU 32s ESP32 board**
- **4 × MG90 servos**
- **MeArm 4DOF Kit** (for structure)
- **2 × 18650 Li-ion batteries**
- **Step-down buck converter**
- **Breadboard**

## Working Principle
1. The servos control the arm's movement across four degrees of freedom.
2. Commands are sent via **Bluetooth** or **pre-programmed** sequences.
3. The arm picks and places objects based on received input.
4. Future web implementation will allow full automation.

## Code Implementation
The main code consists of:
- **Reading commands via Bluetooth or automated sequences**
- **Controlling servos for smooth movement**
- **Ensuring stable operation with incremental motion control**

## Future Improvements
- **Web-Based Control**: Enable users to control the arm remotely via a website.
- **AI Integration**: Implement object recognition for intelligent sorting.
- **Enhanced Stability**: Improve movement precision with optimized servo control.

## License
This project is open-source under the **MIT License**.

## Author
**Hiran Geeth Dharmapala**

Feel free to contribute or suggest improvements!

