# Franklin Energy Steam Project - Stream Trap Monitor Firmware

## Overview
We are building a device which will monitor ultrasonic auditory data of steam traps involved with heating systems. Upon completion, the goal of this device is to be able to recognize what a failing steam trap sounds like, and broadcast an alert when a fault is detected. By catching these faults early on, we can save energy that would otherwise be wasted through silent, incorrect temperature regulation caused by the broken piece. This repo itself holds the firmware for this steam trap accessory, along with some test files and schematics of the accessory itself.

## Navigation
- **[firmware](firmware/)** - directory for all source files of the device firmware, as well as some test files.
- **[py](py/)** - directory for all python helper scripts, such as reading and processing serial data.
- **[schematic](schematic/)** - directory for visual documentation on the device's custom board design.

## Contributing
For contributing to the source code of this project, please create your own branch and use a pull request to get these changes onto the main branch. To begin development of your own local branch, run the following git CLI commands from terminal:
```
git clone https://github.com/berg-lab/Steam-Trap-Mic.git
cd Steam-Trap-Mic
git checkout -b your_branch_name
```
From here, you can make local changes to your branch and experiment with different code. Once the repo is in a good state to save and checkpoint, add all of your changes into a commit and push them to your branch on the remote repository:
```
git add .
git commit -m "commit message describing changes here"
git push -u origin your_branch_name
```
These new changes will now be visible to everyone with access to the repo on the web. This process should be done any time a significant change is made! _Note: the -u flag sets the designated push location as the default for the current local branch, so any subsequent pushes can be done with just the command_ `git push`.

To get your changes onto the main branch, please use a pull request. **AVOID PUSHING DIRECTLY TO MAIN.** You can open a pull request on Github by going to the "Pull requests" tab in the repo and clicking "New pull request." From here, select "main" for base and your branch for compare. Making sure all merge conflicts are resolved, and click "Create pull request." Once this pull request is reviewed, it can be merged to the main branch of production.

Lastly, because there are multiple people working on the repository, there will be changes made to main often, which need to be reflected on your local branch. You can bring these new changes onto your branch with one command: `git pull`. **ALWAYS PULL BEFORE YOU PUSH.** This will avoid merge conflicts which can occur if your pull requests do not contain the most recent changes made to main.

## Deployment
To upload the firmware onto the device, make sure it is connected to your computer through a COM port. In the Arduino IDE, open the project and select this port, which should be labeled with "Moteino M0" under `Tools > Port`. Finally, click "Upload" to transfer the code to the device and begin running the main loop.
