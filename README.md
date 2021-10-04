# ieeeNumbers

Simple program to convert IEEE floating point numbers to their decimal representation.

## Usage
Example

Input: `./ieee2dec 0xc14e0000`

Output: `-30.500000000000000000000000`

Input: `./ieee2dec 0x37551216 -e`

Output: `1.270000e-005`

Input: `./ieee2dec 0x37551216 -p`

Output: ```input string: 0037551216
input value: 928322070

1) Input Binary Breakdown
___________________________________________
|0       |01101110|10101010001001000010110|
|Negative|Exponent|Mantissa               |
|________|________|_______________________|

2) Properties:
Negative: False
Exponent: 110 - 127 = -17

3a) Add Padding
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001.10101010001001000010110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
3b) Move Binary Point
000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.0000000000000000110101010001001000010110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

4a) Separate Whole Component
000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
4b) Separate Fractional Component
0000000000000000110101010001001000010110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

5a) Comput Whole Component
0
5b) Compute Fractional Component
0.00001270000029762741200000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

Converted Output: 0.000012700000297627412000```

Arguments:
1. IEEE floating point number reprented as hex with leading 0x or as binary with leading 0b

Options:

`-print`: Print conversion steps

`-e`: Output as scientific notation, useful for small numbers

## Compiling
Clang:

`clang ieee2dec.c -lm -o ieee2dec`

GCC:

`gcc ieee2dec.c -lm -o ieee2dec`
