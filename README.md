
#  Car Race Project

Autonomous + Remote-Controlled Arduino Car  
**Competition Date:** 10 May 2025  

## Features
- Line following via IR sensors
- Ultrasonic obstacle detection with buzzer + stop
- LED feedback when sensors detect edges
- Dual motor PWM control for smooth turns
- Remote control through serial/bluetooth commands

## Code
The `car_race.ino` file contains the Arduino sketch used during the competition.  
Feel free to fork and improve!

## Photos

![photo_6_2025-09-19_20-57-05](https://github.com/user-attachments/assets/19ce3665-1d26-4ad5-8150-53f14123834f)

## Components Used

- **Arduino Uno** (main controller)
- **L298N Motor Driver** (dual H-bridge)
- **2x DC Motors + Wheels** (for drive)
- **IR Sensors** (line following, connected to A2 and A3)
- **Ultrasonic Sensor (HC-SR04)** (obstacle detection)
- **Buzzer** (sound alert)
- **LED** (status indicator)
- **Bluetooth Module (HC-05 or HC-06)** (wireless remote control)
- Battery pack + chassis + jumper wires
