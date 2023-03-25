import audiosegment
import csv
import matplotlib.pyplot as plt
import sys

# USAGE: py wav_converter.py steam_sounds/<input_file_name>.wav csvs/<output_file_name>.csv

audiofile = sys.argv[1]
outfile = sys.argv[2]
seg = audiosegment.from_file(audiofile)
sample_rate = 1000
resampled = seg.resample(sample_rate_Hz=sample_rate, channels=1) # input is microvolts
samples_microv = resampled.get_array_of_samples()
samples_v = [x/1_000_000 for x in samples_microv]
plt.plot(samples_v)
plt.show()
with open(outfile, "w", newline="") as f:
    # hard params
    writer = csv.writer(f)
    writer.writerow(["data length", len(samples_v)])
    writer.writerow(["frequency", sample_rate])
    writer.writerow(["amp", 20])
    writer.writerow(["offset", 0])
    writer.writerow(["phase", 0])

    # data reading  
    new_array = [[0, x] for x in samples_v]
    writer.writerow(["xpos", "value"])
    writer.writerows(new_array)
