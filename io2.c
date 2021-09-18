#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>



int main(int argc, char** argv) {
	/*
	 *INPUT: Read in first command line argument
	 */
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
	 
	printf("input string: %s\n\
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

	unsigned long long int inputCopy = input;
	long long unsigned int inCopy = input;
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




printf("\n1) Input Binary Breakdown\n\
___________________________________________\n\
|%c       |%s|%s|\n\
|Negative|Exponent|Mantissa               |\n\
|________|________|_______________________|\n\n",
bitString[0], expString, manString);



	printf("2) Properties:\n");
	//check if negative
	bool isNeg;
	if (bitString[0] == '1') {
		isNeg = 1;
		printf("Negative: True\n");
	} else {
		isNeg = 0;
		printf("Negative: False\n");
	}



	/*
	 * Exponent
	 */
	int expMask = 0b01111111100000000000000000000000;
	long long int unbiasedExp = ((input & expMask)>>23);
	long long int trueExp = ((input & expMask)>>23) - 127;
	printf("Exponent: %lld - 127 = %lld\n\n", unbiasedExp, trueExp);

	/*
	 * Normalize the string
	 * Add leading 1
	 * 128 leading before binary point
	 * 128 after binary point
	 */
	printf("3a) Add Padding\n");
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
		printf("%c", leadingManString[i]);
	}
	

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

	printf("\n3b) Move Binary Point\n\n%s\n", finalString);

	int asdf = strlen(finalString);
	printf("Strlen %d\n", asdf);
	return 0;
}