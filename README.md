heartRateMonitor
================

E190P Project 1: Arduino-controlled Heart Rate Monitor


Objective
---------
Create a system to
 * Detect pulse
 * Measure heart rate
 * Notify if heart rate is outside of acceptable range


Materials
---------
* Reflective Optical Sensor TCRT1000
* MCP6004 Op-Amp
* Resistors: 1k x 2, 150k, 47k x2, 10k, 680k x2, 6.8kx2
* Potentiometer: 5k
* Capacitors: 100 nF x2, 4.7uF x2
* Arduino Uno

Pulse Detection Unit
--------------------
The output of the sensor was passed through 2 stages. The first stage consists of a passive high-passed filter to take out the DC offset, and an active low-passed filter to take out the noise and amplify the signal by 101 times.
The second stage is identical to the first, making the signal more distinct and adding another gain of 101. Overall, the original signal was amplified by about 10000 times. The potentiometer between the 2 stages will help control the gain if needed.
<img src="http://www.rlocman.ru/i/Image/2012/11/30/EasyPulse_1.png" width="300px" height="300px" />
![Arduino Uno](https://www.labviewhacker.com/lib/exe/fetch.php?media=:templates:hardware:arduino:uno:arduino_uno_small.jpg "Arduino Uno")


Python Visualizer (code in repository):
 * Takes data from Arduino as serial input
 * Plots heart rate calculations on graph over time
 * Displays current heart rate reading on the bottom of the screen

<img src="https://dl.dropboxusercontent.com/s/8s65bgnu446ckqr/HeartRateDemo.png" width="300px" height="300px"/x>
