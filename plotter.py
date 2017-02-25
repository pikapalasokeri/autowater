#!/usr/bin/python

import matplotlib.pyplot as plt
import sys

print sys.argv
if len(sys.argv) < 2:
    print "Usage: plotter.py <file path>"
    exit(0)

filePath = sys.argv[1]



voltageData = []
with open(filePath) as f:
    for line in f:
        if ("humidityVoltage: " in line
            or "humidityValue: " in line):
            tokens = line.split(" ")
            humidityVoltage = float(tokens[-1])
            voltageData.append(humidityVoltage)

plt.plot(voltageData, '.-k')
plt.show()

