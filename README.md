# earthquake-sensors #

A seismograph measures the ground movements continuously, but the interesting events - the earthquakes – are rare. With a program, we would like to find these events automatically.

We have the files of 3 earthquakes, and one file that contains several earthquakes.

## A. Start and end ##
Find the beginning of the earthquake and display the number of the entry. We say that there is an earthquake if the absolute value of the signal exceeds 20.0. (You can try with other thresholds.)

Look for the end of the earthquake, and display the number of the entry. The earthquake is said to be over if 200 consecutive values are below the threshold.

## B. Energy ##
Calculate the energy of the earthquake, i.e. the sum of the square values (∑x²) between the beginning and the end.

## C. Several earthquakes ##
Modify your program to detect several earthquakes. For each earthquake, display its beginning, its length, and its energy.


(Exercise from https://sop.course-unifr.ch/#earthquakes)
