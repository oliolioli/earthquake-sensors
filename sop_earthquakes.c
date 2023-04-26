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
	int length = readFile("earthquake3", earthquake, 11000);

	// A. Start and end
	// Find the beginning of the earthquake and display the number of the entry. We say that there is an earthquake if the absolute value of the signal exceeds 20.0. (You can try with other thresholds.)
	// Look for the end of the earthquake, and display the number of the entry. The earthquake is said to be over if 200 consecutive values are below the threshold.

	float localMin = 0;
	float localMax = 0;
	float diffLocalMinMax = 0;
	int   posLocalMin = 0;
	int   posLocalMax = 0;
	int   changeOfSign = 0;

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
			printf("Vorzeichenwechsel!\n");
			
			// If we arrive at a second change of sign, we can calculate the difference (min/max)
			if (changeOfSign == 1) {
				// Calculate difference
				diffLocalMinMax = localMax - localMin;

				printf("i = %d. Periode abgeschlossen. LocalMin: %f, localMax: %f\n", i, localMin, localMax);
				printf("Differenz: %f\n", diffLocalMinMax);
				
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


	// B. Energy
	// Calculate the energy of the earthquake, i.e. the sum of the square values (∑x²) between the beginning and the end.

	// C. Several earthquakes
	// Modify your program to detect several earthquakes. For each earthquake, display its beginning, its length, and its energy.

	return 0;
}