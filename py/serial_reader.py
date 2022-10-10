import serial
import matplotlib.pyplot as plt
import sys

# USAGE: python3 py/serial_reader.py <COM_PORT> <NUM_POINTS>

com_port = sys.argv[1]
num_pts = sys.argv[2] if len(sys.argv) > 2 else 1000
ser = serial.Serial(com_port, 115200, timeout=1)
data = []
counter = 0

while counter < num_pts:
    datum = float(ser.readline().decode('utf-8').strip())
    data.append(datum)
    counter += 1

plt.plot(range(num_pts), data, color="blue")
plt.show()