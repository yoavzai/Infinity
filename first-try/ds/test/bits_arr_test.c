#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "bits_arr.h"
#include "test_functions.h"

#define SIZE sizeof(bitsarr_t)*8

bitsarr_t input = 1UL << (SIZE - 1);
/* input in binary is 1000........0000 */

void TestFlip()
{
	VerifySizeT(BitsArrFlip(input, -1), input, "Flip");
	VerifySizeT(BitsArrFlip(input, 0), input + 1, "Flip");
	VerifySizeT(BitsArrFlip(input, SIZE - 1), 0, "Flip");
	VerifySizeT(BitsArrFlip(input, SIZE), input, "Flip");
	printf("\n");
}

void TestSetOn()
{
	VerifySizeT(BitsArrSetOn(input, -1), input, "SetOn");
	VerifySizeT(BitsArrSetOn(input, 0), input + 1, "SetOn");
	VerifySizeT(BitsArrSetOn(input, SIZE - 1), input, "SetOn");
	VerifySizeT(BitsArrSetOn(input, SIZE), input, "SetOn");
	printf("\n");
}

void TestSetOff()
{
	VerifySizeT(BitsArrSetOff(input, -1), input, "SetOff");
	VerifySizeT(BitsArrSetOff(input, 0), input, "SetOff");
	VerifySizeT(BitsArrSetOff(input, SIZE - 1), 0, "SetOff");
	VerifySizeT(BitsArrSetOff(input, SIZE), input, "SetOff");
	printf("\n");
}

void TestCountOn()
{
	VerifySizeT(BitsArrCountOn(input), 1, "CountOn");
	VerifySizeT(BitsArrCountOn(input - 1), SIZE - 1, "CountOn");
	VerifySizeT(BitsArrCountOn(input + 0xf), 5, "CountOn");
	VerifySizeT(BitsArrCountOn(input - input), 0, "CountOn");
	printf("\n");
}

void TestCountOnLut()
{
	VerifySizeT(BitsArrCountOnLut(input), 1, "CountOnLut");
	VerifySizeT(BitsArrCountOnLut(input - 1), SIZE - 1, "CountOnLut");
	VerifySizeT(BitsArrCountOnLut(input + 0xf), 5, "CountOnLut");
	VerifySizeT(BitsArrCountOnLut(input - input), 0, "CountOnLut");
	printf("\n");
}

void TestCountOff()
{
	VerifySizeT(BitsArrCountOff(input), SIZE - 1, "CountOff");
	VerifySizeT(BitsArrCountOff(input - 1), 1, "CountOff");
	VerifySizeT(BitsArrCountOff(input + 0xf), SIZE - 5, "CountOff");
	VerifySizeT(BitsArrCountOff(input - input), SIZE, "CountOff");
	printf("\n");
}

void TestResetAll()
{
	VerifySizeT(BitsArrResetAll(input), 0, "ResetAll");
	VerifySizeT(BitsArrResetAll(input - 1), 0, "ResetAll");
	VerifySizeT(BitsArrResetAll(input + 0xf), 0, "ResetAll");
	VerifySizeT(BitsArrResetAll(input - input), 0, "ResetAll");
	printf("\n");
}

void TestSetAll()
{
	VerifySizeT(BitsArrSetAll(input), ~0UL, "SetAll");
	VerifySizeT(BitsArrSetAll(input - 1), ~0UL, "SetAll");
	VerifySizeT(BitsArrSetAll(input + 0xf), ~0UL, "SetAll");
	VerifySizeT(BitsArrSetAll(input - input), ~0UL, "SetAll");
	printf("\n");
}

void TestIsOn()
{
	VerifyInt(BitsArrIsOn(input, -1), -1, "IsOn");
	VerifyInt(BitsArrIsOn(input, 0), 0,"IsOn");
	VerifyInt(BitsArrIsOn(input, SIZE - 1), 1, "IsOn");
	VerifyInt(BitsArrIsOn(input, SIZE), -1, "IsOn");
	printf("\n");
}

void TestIsOff()
{
	VerifyInt(BitsArrIsOff(input, -1), -1, "IsOff");
	VerifyInt(BitsArrIsOff(input, 0), 1, "IsOff");
	VerifyInt(BitsArrIsOff(input, SIZE - 1), 0, "IsOff");
	VerifyInt(BitsArrIsOff(input, SIZE), -1, "IsOff");
	printf("\n");
}

void TestRotR()
{
	VerifySizeT(BitsArrRotR(input, 0), input, "RotR");
	VerifySizeT(BitsArrRotR(input, (3*SIZE - 1)), 1, "RotR");
	VerifySizeT(BitsArrRotR(input + 1, (2*SIZE - 1)), 3, "RotR");
	VerifySizeT(BitsArrRotR(input, 10), input / 1024, "RotR");
	printf("\n");
}

void TestRotL()
{
	VerifySizeT(BitsArrRotL(input, 0), input, "RotL");
	VerifySizeT(BitsArrRotL(input, SIZE + 2), 2, "RotL");
	VerifySizeT(BitsArrRotL(input + 1, SIZE + 1), 3, "RotL");
	VerifySizeT(BitsArrRotL(11, 10), 11 * 1024, "RotL");
	printf("\n");
}

void TestToString()
{
	char* str = malloc(65);

	VerifyString(BitsArrToString(input, str),
				 "1000000000000000000000000000000000000000000000000000000000000000",
				 "ToString");

	VerifyString(BitsArrToString(input - 1, str),
				"0111111111111111111111111111111111111111111111111111111111111111",
				"ToString");

	VerifyString(BitsArrToString(0xaaaaaaaaaaaaaaaa, str),
				"1010101010101010101010101010101010101010101010101010101010101010",
				"ToString");

	VerifyString(BitsArrToString(0x4242424242424242, str),
				"0100001001000010010000100100001001000010010000100100001001000010",
				"ToString");
	printf("\n");

	free(str);
}

void TestMirror()
{
	VerifySizeT(BitsArrMirror(input), 1, "Mirror");
	VerifySizeT(BitsArrMirror(input + 1), input + 1, "Mirror");
	VerifySizeT(BitsArrMirror(0), 0, "Mirror");
	VerifySizeT(BitsArrMirror(input - 1), ~0UL - 1, "Mirror");
	printf("\n");
}

void TestMirrorLut()
{
	VerifySizeT(BitsArrMirrorLut(input), 1, "MirrorLut");
	VerifySizeT(BitsArrMirrorLut(input + 1), input + 1, "MirrorLut");
	VerifySizeT(BitsArrMirrorLut(0), 0, "MirrorLut");
	VerifySizeT(BitsArrMirrorLut(input - 1), ~0UL - 1, "MirrorLut");
	printf("\n");
}


void TestSetBit()
{
	VerifySizeT(BitsArrSetBit(input, 0, 1), input + 1, "SetBit");
	VerifySizeT(BitsArrSetBit(input, 63, 0), 0, "SetBit");
	VerifySizeT(BitsArrSetBit(input, 63, 1), input, "SetBit");
	VerifySizeT(BitsArrSetBit(14, 2, 0), 10, "SetBit");
	printf("\n");
}


int main()
{
	TestFlip();
	TestSetOn();
	TestSetOff();
	TestCountOn();
	TestCountOnLut();
	TestCountOff();
	TestResetAll();
	TestSetAll();
	TestIsOn();
	TestIsOff();
	TestRotR();
	TestRotL();
	TestToString();
	TestMirror();
	TestMirrorLut();	
	TestSetBit();

	return 0;
}
















