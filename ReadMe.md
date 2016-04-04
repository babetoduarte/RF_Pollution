# RF Pollution IoT Sensor Node

This repository holds the code for a Radio Frequency Pollution sensor node. The project is build using PlatformIO as an IoT Framework, it runs on the NodeMCU v2 development module which implements a ESP8266-12E chip.

The code is written using the Arduino C/C++ language, and implements the following libraries:

    - ESP
    - ESP8266WiFi
    - PubSubClient

A custom RF sensing circuit will be built and its decoded sensing output will be connected to the NodeMCU's digital input pins. This way, for every measurement the Node will only have to probe its digital inputs, and report a predefined signal measurement to the MQTT broker according to which pin presents a signal:

![NodeMCU Pinout Diagram](babetoduarte.github.com/RF_Pollution/img/NodeMCU_Pinout.png)
