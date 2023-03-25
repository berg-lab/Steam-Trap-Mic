# Python Helper Scripts

## Overview
This directory is home to all python helper scripts for debugging the steam traps.

## Descriptions
- **serial_reader.py**: a short script to read the output of serial monitor when connected to a Moteino that is continuously sending voltage readings. This data is plotted and displayed to the screen and can be used to view a general picture of the waveform heard by the Moteino's ultrasonic mic. Required command line argument is `COM_PORT`, which designates which serial port to listen to. Optional command line argument is `duration` (specified by "-d" flag) which designates how many seconds to listen to the serial data, default value is 5. The example below listens to serial port COM5 for 10 seconds:
```
python3 serial_reader.py COM5 -d 10
```

- **wav_converter.py**: a short script to convert a given .wav file into a CSV designating the analog output of the sound in volts. The data is plotted and displayed for a sanity check. After the data is exported to CSV, this CSV can be imported into EasyWaveX to later be emulated with a function generator. To keep things tidy while running this script, place all .wav files into the `/steam_sounds` directory, and export to the `/csvs` directory. Required command line arguments are `input_file` and `output_file`, which designate the .wav file to read and .csv file to export, respectively. The .csv file does not need to exist before running the script, this is simply the name of the file you want to create. The example below reads the file "sample_in.wav" located in the `\steam_sounds` directory and creates a CSV of analog output named "sample_out.csv" located in the `\csvs` directory:
```
python3 wav_converter.py steam_sounds/sample_in.wav csvs/sample_out.csv
```

## Dependencies
These scripts require Python 3. Each of these must be installed to the PYTHONPATH which can be done with pip, as detailed in the [Quick Start](#quick-start) section below. See the dependencies below for each file:
- serial_reader.py
    - matplotlib
    - pyserial
- wav_converter.py
    - audiosegment (repo [here]("https://github.com/MaxStrange/AudioSegment"))
    - matplotlib

## Quick Start
First, make sure the following dependency is installed to your system by running the commands below in a Unix style terminal:
```
sudo apt-get update
sudo apt-get install sox
```

Next you can use the pip install to install the python-specific packages from PyPI:
```
python3 -m pip3 install --upgrade pip3
pip3 install matplotlib pyserial
pip3 install --user audiosegment
```