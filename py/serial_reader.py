import argparse
import matplotlib.pyplot as plt
import serial
import time

# USAGE: python3 py/serial_reader.py <COM_PORT> -d <NUM_SECS>

# read command line arguments
parser = argparse.ArgumentParser(description="Plot the values received from Moteino over serial.")
parser.add_argument("COM_PORT", type=str, nargs=1, help="Designated COM port to listen on (i.e. COM5 on Windows)")
parser.add_argument("-d, --duration", dest="num_secs", type=int, nargs=1, default=5, help="Number of seconds to listen for serial data")
args = parser.parse_args()

# initialize serial
com_port = args.com_port[0]
ser = serial.Serial(com_port, 115200, timeout=1)
ser.readline()

# start loop
num_secs = args.num_secs
start = time.time()
t = time.time() - start
data = []
datum = 0
while t < num_secs:
    # try to get a reading
    try:
        datum = float(ser.readline().decode('utf-8').strip())
    # use last recorded datum if nothing received
    except ValueError: pass
    data.append((datum, t))
    t = time.time() - start

# plot the voltage data received vs time
plt.xlabel("Time since start (s)")
plt.ylabel("Voltage")
plt.plot([t for (d,t) in data], [d for (d,t) in data], color="blue")
plt.show()