/* 
Please do not change the name of this file. 

Name (of all group members):
Date:
Program runs (yes or no, because): 
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
	int length = readFile("earthquake1", earthquake, 11000);
	
	// earthquake now contains the values of the "earthquake1" file
	// (11000 entries total, length of entries used, the other entries are not initialized)

	return 0;
}
