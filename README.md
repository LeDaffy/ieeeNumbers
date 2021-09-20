# ieeeNumbers

Simple program to convert IEEE floating point numbers to their decimal representation.

## Usage
Example

Input: `./ieee2dec 0xc14e0000`

Output: `-30.500000000000000000000000`

Input: `./ieee2dec 0x37551216 -e`

Output: `1.270000e-005`

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
