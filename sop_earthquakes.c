/* 
Please do not change the name of this file. 

Name (of all group members): Olivier Meier
Date: 25.4.22
Program runs (yes or no, because): yes
*/

// Libraries
#include <stdio.h>
#include <stdlib.h>


// Functions
int readFile(char * nameOfFile, double * tableToFill, int length) {
	// Open the file
	FILE * file = fopen(nameOfFile, "r");
	if (file == NULL) {
		fprintf(stderr, "Error: unable to open the file '%s'\n", nameOfFile);
		exit(1);
	}

	// Read line by line
	int n = 0;
	char buffer[100];
	while (fgets(buffer, 100, file) != NULL) {
		if (n >= length) break;
		tableToFill[n] = atof(buffer);
		n = n + 1;
	}

	// Close the file and return the number of lines read
	fclose(file);
	return n;
}


// Main
int main(int argc, char * argv[]) {
	double earthquake[11000];

	// earthquake now contains the values of the "earthquake1" file
	// (11000 entries total, length of entries used, the other entries are not initialized)
	int length = readFile("earthquake-multiple", earthquake, 11000);

	// Find the beginning of the earthquake and display the number of the entry. We say that there is an earthquake if the absolute value of the signal exceeds 20.0. (You can try with other thresholds.)
	// Look for the end of the earthquake, and display the number of the entry. The earthquake is said to be over if 200 consecutive values are below the threshold.

	float localMin = 0;
	float localMax = 0;
	float diffLocalMinMax = 0;
	int   posLocalMin = 0;
	int   posLocalMax = 0;
	int   changeOfSign = 0;

	int   beginOfEarthQuake = 0;
	int   earthquakeOver = 0;
	int   endOfEarthQuake = 0;

	double earthquakeEnergy = 0;
	int    tmpEnergy = 0;

	// Now search local minimum and maximum
	for (int i=0; i<=length; ++i) {

		if (earthquake[i] < 0) {
			// pick most negative value of all negative values (=local mininmum)
			if (earthquake[i] < localMin) { localMin = earthquake[i]; }
		} else if (earthquake[i] > 0) {
			// pick most positive value of all positive values (=local maximum)
			if (earthquake[i] > localMax) { localMax = earthquake[i]; }
		}

		// If sign gets changed, we set state change of sign (or if we arrive at end of file)
		if ((earthquake[i] > 0 && earthquake[i+1] < 0) || (earthquake[i] < 0 && earthquake[i+1] > 0) || i > length - 2) {
			//printf("Vorzeichenwechsel!\n");
			
			// If we arrive at a second change of sign, we can calculate the difference (min/max)
			if (changeOfSign == 1) {
				// Calculate difference
				diffLocalMinMax = localMax - localMin;

				/*
					printf("i = %d. Periode abgeschlossen. LocalMin: %f, localMax: %f\n", i, localMin, localMax);
					printf("Differenz: %f\n", diffLocalMinMax);
				*/

				// Find the beginning of the earthquake (if the absolute value of the signal exceeds 20.0) 
				// and display the number of the entry. 
				if (diffLocalMinMax > 20 && beginOfEarthQuake == 0) {
						beginOfEarthQuake = i;
						printf("Eartquake begins at: %d\n", i);
				}

				// Look for the end of the earthquake, and display the number of the entry. 
				// The earthquake is said to be over if 200 consecutive values are below the threshold.
				if (beginOfEarthQuake > 0 && diffLocalMinMax < 20) {

					if (earthquakeOver == 199) {
						endOfEarthQuake = i;
						printf("Eartquake stops at: %d\n", endOfEarthQuake);
						printf("Earthquakes length: %d\n", endOfEarthQuake - beginOfEarthQuake);

						// Calculate the energy of the earthquake, i.e. the sum of the square values (∑x²) between the beginning and the end.
						for (int i=beginOfEarthQuake; i<=endOfEarthQuake; ++i) {
							tmpEnergy = (int)earthquake[i];
							earthquakeEnergy += tmpEnergy^2;
						}
						printf("Earthquakes total energy: %.2f\n---\n", earthquakeEnergy);

						// Reset the counter and earthquake specific data and begin all over
						earthquakeOver = 0;
						beginOfEarthQuake = 0;
						endOfEarthQuake = 0;
						earthquakeEnergy = 0;

					} else {
						earthquakeOver++;
					}

				}				

				// Reset changeOfSign to rebegin the counting of local min/max
				changeOfSign = 0;
				
				// Reset local min/max
				localMax = 0;
				localMin = 0;
			} else {
				changeOfSign = 1;
			}
			
		}
	}

	return 0;
}