#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


int main(int argc, char** argv) {
	/*
	 *INPUT: Read in first command line argument
	 */
	bool supressPrint = 1;
	bool scientificNotation = 0;
	unsigned long long int input= 0;
	if (argv[1][1] == 'x' || argv[1][1] == 'X') {
		argv[1][1] = '0';   
		input = strtoll(argv[1], NULL, 16);
	} else if (argv[1][1] == 'b' || argv[1][1] == 'B') {
		argv[1][1] = '0';
		input = strtoll(argv[1], NULL, 2);
	} else {
		input = strtoll(argv[1], NULL, 10);
	}

	
	if (argc > 2) {
		for (int i = 2; i < argc; i++) {
			if (!strcmp(argv[i], "-p") ||
			!strcmp(argv[i], "-P") ||
			!strcmp(argv[i], "-print") ||
			!strcmp(argv[i], "-Print")) {
				supressPrint = 0;
			} else if 
			(!strcmp(argv[i], "-e") ||
			!strcmp(argv[i], "-E")){
				scientificNotation = 1;
			}
		}
	}
	
	if (!supressPrint) printf("input string: %s\n\
input value: %llu\n", argv[1], input);


	/*
	 * Isolate Negative, Exponent, and Mantissa
	 */
	char bitString[33];
	char expString[9];
	char manString[24];

	bitString[32] = '\0';
	expString[8] = '\0';
	manString[23] = '\0';	

	unsigned long long int inCopy = input;
	for (int i = 31; i > -1; i--) {
		if (inCopy & 1)
			bitString[i] = '1';
		else
			bitString[i] = '0';

		inCopy >>= 1;
	}

	for (int i = 0; i < 8; i++) {
		expString[i]  = bitString[i+1];
	}

	for (int i = 0; i < 23; i++) {
		manString[i]  = bitString[i+9];
	}




if (!supressPrint) printf("\n1) Input Binary Breakdown\n\
___________________________________________\n\
|%c       |%s|%s|\n\
|Negative|Exponent|Mantissa               |\n\
|________|________|_______________________|\n\n",
bitString[0], expString, manString);



	if (!supressPrint) printf("2) Properties:\n");
	//check if negative
	bool isNeg;
	if (bitString[0] == '1') {
		isNeg = 1;
		if (!supressPrint) printf("Negative: True\n");
	} else {
		isNeg = 0;
		if (!supressPrint) printf("Negative: False\n");
	}



	/*
	 * Exponent
	 */
	int expMask = 0b01111111100000000000000000000000;
	long long int unbiasedExp = ((input & expMask)>>23);
	long long int trueExp = ((input & expMask)>>23) - 127;
	if (!supressPrint) printf("Exponent: %lld - 127 = %lld\n\n", unbiasedExp, trueExp);

	/*
	 * Normalize the string
	 * Add leading 1
	 * 128 leading before binary point
	 * 128 after binary point
	 */
	if (!supressPrint) printf("3a) Add Padding\n");
	char leadingManString[258];
	leadingManString[257] = '\0';
	for (int i = 0; i < 257; i++) {
		//if (i % 4 == 0 && i != 0) printf(" ");
		if (i == 127) {
			leadingManString[i] = '1';
		} else	if (i == 128) {
			leadingManString[i] = '.';
		} else if (i < 152 && i > 128) {
			leadingManString[i] = manString[i-129];
		} else {
			leadingManString[i] = '0';
		}
		if (!supressPrint) printf("%c", leadingManString[i]);
	}
	
	/*
	 * Move the binary point
	 */
	char finalString[258];
	finalString[257] = '\0';
	finalString[0] = '0';
	unsigned int binaryPoint = 128+trueExp;
	//printf("\nBinary Point: %u\n", binaryPoint);
	bool afterBinaryPoint = 0;
	bool placedBinaryPoint = 0;
	for (int i = 0; i < 257; i++) {
		if (i == 128) afterBinaryPoint = 1;
		if (i == binaryPoint) {
			finalString[i] = '.';
			placedBinaryPoint = 1;
		} else {
			if (i < 128 && !placedBinaryPoint)
				finalString[i] = leadingManString[i];
			else if (i < 128 && placedBinaryPoint) 
				finalString[i] = leadingManString[i-1];
			else if (i > 128 && placedBinaryPoint)
				finalString[i] = leadingManString[i];
			else
				finalString[i] = leadingManString[i+1];
		}
	}

	if (!supressPrint) printf("\n3b) Move Binary Point\n%s\n\n", finalString);


	/*
	 * Convert to two strings
	 * One with the whole number component
	 * One with the fractional component
	 */
	
	char wholeString[258];
	char fracString[258];
	wholeString[257] = '\0';
	fracString[257] = '\0';
	afterBinaryPoint = 0;
	int locBinaryPoint;

	for (int i = 0; i < 257; i++) {
		if (finalString[i] == '.') {
			afterBinaryPoint = 1;
			locBinaryPoint = i;
		}
		if (!afterBinaryPoint) {
			wholeString[i] = finalString[i];
			wholeString[i+1] = '\0';
		}
		else {
			fracString[i-locBinaryPoint] = finalString[i+1];
		}
	}

	if (!supressPrint) printf("4a) Separate Whole Component\n%s\n", wholeString);
	if (!supressPrint) printf("4b) Separate Fractional Component\n%s\n", fracString);

	unsigned long long int wholeNumber = 0;
	double fracNumber = 0.0;
	unsigned int wholeLength, fracLength;
	wholeLength = strlen(wholeString);
	fracLength = strlen(fracString);

	wholeNumber = strtoull(wholeString, NULL, 2);
	
	for (int i = 0; i < fracLength; i++) {
		if (fracString[i] == '1') {
			fracNumber += (double)1.0/((double)(pow(2,i+1)));
		} else {
			continue;
		}
	}

	if (!supressPrint) printf("\n5a) Comput Whole Component\n%llu\n", wholeNumber);
	if (!supressPrint) printf("5b) Compute Fractional Component \n%.128lf\n", fracNumber);
	if (!supressPrint) printf("\nConverted Output: ");

	double finalAnswer = (double)wholeNumber + fracNumber;
	if (isNeg) finalAnswer *= -1;
	if (!scientificNotation){
		printf("%.24lf", finalAnswer);
	} else {
		printf("%e", finalAnswer);
	}
	
	
	return 0;
}
