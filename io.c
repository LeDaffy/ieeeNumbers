#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>



int main(int argc, char** argv) {
	/*
	 *INPUT: Read in first command line argument
	 */
	long long unsigned input= 0;
	if (argv[1][1] == 'x') {
		argv[1][1] = '0';   
		input = strtoll(argv[1], NULL, 16);
	} else if (argv[1][1] == 'b') {
		argv[1][1] = '0';
		input = strtoll(argv[1], NULL, 2);
	} else {
		input = strtoll(argv[1], NULL, 10);
	}
	 
	//printf("input: %s\n\n", argv[1]);


	/*
	 * Isolate Negative, Exponent, and Mantissa
	 */
	int negMask = 0b10000000000000000000000000000000;
	int expMask = 0b01111111100000000000000000000000;
	int manMask = 0b00000000011111111111111111111111;

	char bitString[33];
	bool isNeg;
	char expString[9];
	char manString[24];

	bitString[32] = '\0';
	expString[8] = '\0';
	manString[23] = '\0';	

	

	

	/*
	 * Convert input into bit strings
	 */
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
		manString[i]  = bitString[i+1];
	}




printf("\nInput Binary Breakdown\n\
___________________________________________\n\
|%c       |%s|%s|\n\
|Negative|Exponent|Mantissa               |\n\
|________|________|_______________________|\n\n",
bitString[0], expString, manString);




	/*
	 * Detect negative bit
	 */
	if (bitString[0] == '1') {
		isNeg = 1;
		printf("Negative: True\n\n");
	} else {
		isNeg = 0;
		printf("Negative: False\n\n");
	}
	


	/*
	 * Exponent
	 */
	long long unsigned int unbiasedExp = ((input & expMask)>>23);
	long long unsigned int trueExp = ((input & expMask)>>23) - 127;
	printf("Exponent: %llu - 127 = %llu\n\n", unbiasedExp, trueExp);


	/*
	 * Mantissa //FIXME: Add zeroes for long exponents
	 * 0xd0b10301 provides insights mantissa is correct but encountering overflow issues
	 */
	for (int i = 0; i < 24; i++) {
		manString[i] = bitString[i+9];
	}
	

	char normManstring[129];
	normManstring[128] = '\0';

	normManstring[0] = '1';
	for (int i = 1; i<128; i++) {
		if (i == trueExp+1) {
			normManstring[i] = '.';
		} else if (i < trueExp + 1) {
			if (i > 22) {
				normManstring[i] = '0';
			} else {
				normManstring[i] = manString[i-1];
			}
		} else {
			if (i > 22) {
				normManstring[i] = '0';
			} else {
				normManstring[i] = manString[i-2];
			}
			
		}
		
	}

	printf("Normalized Mantissa = 1.%s\n", manString);
	printf("Exponent Adjusted Mantissa: %s\n\n", normManstring);




	char whole[24];
	char frac[24];
	bool isFrac = 0;
	

	for (int i = 0; i < 23; i++) {
		if (normManstring[i] == '.') {
			isFrac = 1;
		}
		if (isFrac == 0) {
			whole[i] = normManstring[i];
		} else if (isFrac) {
			whole[i] = '\0';
		}
	}

	long long unsigned int binaryPoint = strlen(whole);
	//printf("Strlen %d\n", binaryPoint);
	isFrac = 0;

	for (int i = 0; i < 23; i++) {
		frac[i] = normManstring[i+binaryPoint+1];
	}
	frac[23] = '\0';

	//printf("Whole: %s\nFractional: %s\n", whole, frac);
	long long unsigned int fracLen = strlen(frac);
	long long unsigned int wholeLen = strlen(whole);

	double fracNum = 0.0;
	for (int i = 0; i<fracLen; i++) {
		if (frac[i] == '1'){
			fracNum += 1/pow(2,i+1);
		}
	}
	
	//printf("fracNum: %lf\n", fracNum);

	char* ptr;
	unsigned long long  int wholeInt = 0;
	char wholeSeg[256];

	for (int i = 0; i < 128; i++) {
		wholeSeg[i] = '0';
	}
	wholeSeg[128] = '\0';

	int strLength = strlen(wholeSeg);
	printf("The number of zeroes is %d and the string is \n %s \n\n", strLength, wholeSeg);	

	
	strcat(wholeSeg, whole);
	strLength = strlen(wholeSeg);

	printf("The whole number string is now %s, and the length is %d", wholeSeg, strLength);
wholeInt = strtoull(whole, &ptr, 2); double finalNum = fracNum + wholeInt;
	if (isNeg) {
		finalNum *= -1;
	}


	printf("Whole component: %llu\n", wholeInt);
	printf("Fractional component: %lf\n", fracNum);
	printf("Final Value = %lf\n", finalNum);
	
	
	

	


	

	return 0;
}
