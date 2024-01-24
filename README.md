# Check sensor data for earthquakes #
A seismograph measures the ground movements continuously, but the interesting events - the earthquakes – are rare. With this program, we would like to find these events automatically.

![](https://github.com/oliolioli/earthquake-sensors/blob/main/earthquake1.png)


## Find start and end of an earthquake ##
Finds the beginning of the earthquake and displays the number of the entry. We say that there is an earthquake if the absolute value of the **signal exceeds 20.0**.

Looks for the end of the earthquake, and displays the number of the entry. The earthquake is said to be over if 200 consecutive values are below the threshold.

## Calculate energy ##
Calculates the energy of the earthquake, i.e. the sum of the square values (∑x²) between the beginning and the end.

## Detect several earthquakes ##
Detects several earthquakes. For each earthquake, it displays its beginning, its length, and its energy.


![](https://github.com/oliolioli/earthquake-sensors/blob/main/earthquake2.png)
![](https://github.com/oliolioli/earthquake-sensors/blob/main/earthquake3.png)

(Originally an exercise done at University of Fribourg: https://sop.course-unifr.ch/#earthquakes)
