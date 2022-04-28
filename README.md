# Hoymiles-DTU-Simulation

Simulates a Hoymiles DTU and communicates with Hoymiles micro inverters like HM-600
This project was originally from a thread in https://www.mikrocontroller.net/topic/525778.
Some interested guys took together to sniff the communication between Hoymiles DTU and their microinverters, and to get
values from the inverter like actual voltage, current and power of the inverter.
On lumapu's repo https://github.com/lumapu/ahoy you can find some different ways to get these informations depending on preferred hardware:
- a Python script for the Raspberry pi
- a pure ESP version fpr ESP8266 like Wemos D1 mini or ESP32
- a small version for the Arduino Nano

My goal was to have one version for Arduinos as well ESP microcontrollers. 
The project is developed in the Arduino IDE, so the main file is the .ino file.

And last, I'm german and my english is very poor. And the comments in the code is mostly in german.
