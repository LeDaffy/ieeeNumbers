#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


void printHelp();
int main(int argc, char **argv) {
	if (argc == 1) {
		printHelp();
		exit(EXIT_FAILURE);
	}
	double input = 0.0;
	unsigned long long int wholePart = 0;
	double fracPart = 0.0;
	char inputString[256];

	input  = strtod(argv[1], NULL);

	printf("Input (double) = %lf\n", input);	
	wholePart = (unsigned long long int)floor(input);
	fracPart = input - wholePart;

	printf("Whole: %llu\nDecimal: %lf\n", wholePart, fracPart);
	return 0;
}

void printHelp() {
	printf("dec2ieee Help:\n\
input:\n\
	Decimal Number\n\
options:\n\
	-h prints output as hex\n\
	-b prints output as binary\n\
output:\n\
	IEEE Floating point representation\n");
	return;
}
