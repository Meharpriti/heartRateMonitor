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
The pulse detection unit relies on the concept of pulse oximetry to capture the expansion of blood vessels as a pulse; the reflective sensor will be able to detect each pulse as distinct occurrences. The output of the reflective sensor is passed through 2 stages. The first stage consists of a passive high-pass filter to remove the DC offset, and an active low-pass filter to remove noise and amplify the signal with a gain of 101.
The second stage is identical to the first, making the signal more distinct and adding another gain of 101. Overall, the original signal is amplified by about 10000. The potentiometer between the 2 stages helps to control the gain if needed.

Original concept from: http://embedded-lab.com/blog/?p=5508

<img src="http://www.rlocman.ru/i/Image/2012/11/30/EasyPulse_1.png" width="280px" height="217px" />


Arduino Heart Rate Measurement & Alarm System
----------------------
The Arduino Uno is used to process the output of the pulse detection unit.

![Arduino Uno](https://www.labviewhacker.com/lib/exe/fetch.php?media=:templates:hardware:arduino:uno:arduino_uno_small.jpg "Arduino Uno")

The basic Arduino code works by taking the output from the pulse detection circuit as a digital input. This works because the output is in the form of distinct impulses, such that the digital pin can distinguish between high and low voltages to get 0s and 1s.

The Arduino code takes the digital input and calculates a running average, in which the time between each pulse holds 50% weight in determinine the new average heart rate. The basic calculation of heart rate is:

* Period = time between current beat and last beat
* Frequency (i.e., beats per second) = 1/Period
* Beats per minute = 60 * Frequency
* Average beats per minute = (old BPM average + last calculated BPM)/2

The code begins by ignoring the first few beats (about 5 or 6), because they tend to be erratic. Then, every time it reads a high impulse, it records the time at which it occurred, and compares it against the time of the last pulse. The difference in these times is the period, so 60/period gives us a beats per minute calculation for the last two beats. The most recent beat becomes the new "last pulse" against which the next pulse will be compared, and the BPM calculation is averaged with the old average BPM calculated. The Arduino is then told to read until the current pulse goes low again, at which point it will go back to the main loop and keep reading until there is a new pulse.

The alarm system consist of a 100 Ohm resistor and a speaker, connected to the Arduino as shown. 

<img src="http://arduino.cc/en/uploads/Tutorial/speaker_bb.png"/>

The Arduino sounds an alarm if one of 3 conditions is met:
   * If the heart rate goes above a certain threshold (150 BPM)
   * If the heart rate goes below a certain threshold (30 BPM)
   * If no pulse is detected after several seconds


Python Visualizer
------------------
 * Takes data from Arduino as serial input
 * Plots heart rate calculations on graph over time
 * Displays current heart rate reading on the bottom of the screen

<img src="https://dl.dropboxusercontent.com/s/8s65bgnu446ckqr/HeartRateDemo.png" width="300px" height="300px"/x>
