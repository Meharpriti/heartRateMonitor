#Python script to display heart rate as a moving graph

import serial
import numpy as np
from matplotlib import pyplot as plt

ser = serial.Serial('COM4', 9600) #get serial data from Arduino
plt.ion()
ydata = [0] * 50
ax1 = plt.axes()
ax1.set_xlabel('Time elapsed')
ax1.set_ylabel('Average Heartbeats Per Minute')
line, = plt.plot(ydata)
plt.ylim([0,200])
num = 0
while True:
    data = ser.readline().split()[-1] #Get number from serial data
    #print data
    try:
        num = float(data)
    except ValueError:
        print "Need valid data"
        continue
    ydata.append(num)
    ax1.set_xlabel('Current Heartrate is: ' + data)
    del ydata[0]
    line.set_xdata(np.arange(len(ydata)))
    line.set_ydata(ydata)  # update the data
    plt.draw() # update the plot
    
    
