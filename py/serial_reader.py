import serial
import matplotlib.pyplot as plt

# TODO: need to make this parameter-based instead of hard-coded

ser = serial.Serial("COM6", 115200, timeout=1)
num_pts = 1000
data = []
counter = 0

while counter < num_pts:
    datum = ser.readline()
    data.append(float(datum.decode('utf-8').strip()))
    counter += 1

plt.plot(range(num_pts), data, color="blue")
plt.show()