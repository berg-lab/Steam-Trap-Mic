# Franklin Energy Steam Project - Mic Shield Firmware

## Overview
We are building a device which will monitor ultrasonic auditory data of steam traps involved with heating systems. Upon completion, the goal of this device is to be able to recognize what a failing steam trap sounds like, and broadcast an alert when a fault is detected. By catching these faults early on, we can save energy that would otherwise be wasted through silent, incorrect temperature regulation caused by the broken piece. This repo itself holds the firmware for this steam trap accessory, along with some test files and schematics of the accessory itself.

## Navigation
- **[firmware](firmware/)** - directory for all source files of the device firmware, as well as some test files.
- **[py](py/)** - directory for all python helper scripts, such as reading and processing serial data.
- **[schematic](schematic/)** - directory for visual documentation on the device's custom board design.

## Dependencies
(Need minimum version for python and arduino here). See the dependencies below for each file:
- py/serial_reader.py
    - pyserial
    - matplotlib

## Deployment
First, make sure all dependencies are installed by running the commands below in a terminal:
```
python3 -m pip3 install --upgrade pip3
pip3 install pyserial matplotlib
```
To upload the firmware onto the device, make sure it is connected to your computer through a COM port. In the Arduino IDE, open the project and select this port, which should be labeled with "Moteino M0" under `Tools > Port`. Finally, click "Upload" to transfer the code to the device and begin running the main loop.

## Testing
### `test_sweep.ino`
This test repeatedly prints the analog reading from the microphone to serial. By running `py/serial_reader.py` the analog data can be read, parsed, and plotted for visualization. This test is meant to view the range of frequencies from surrounding sounds, including a full sweep from low to high frequency.
