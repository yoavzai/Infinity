#ifndef BITSARR_H
#define BITSARR_H

#include <stddef.h> /* size_t */

typedef size_t bitsarr_t;

/* 
valid index input for all functions: 0 to sizeof(bitsarr_t).
valid n input for BitsArrRotR and BitsArrRotL: 0 to sizeof(size_t).
valid state input on BitsArrSetBit: 0 or 1.
on BitsArrToString, please provide char* dest with enough memory or data could be overwriten.
 */

/* returns new status on success. returns old status when invalid input was enterd. complexity o(1) */
bitsarr_t BitsArrFlip(bitsarr_t arr, size_t index);

/* returns new status on success. returns old status when invalid input was enterd. complexity o(1) */
bitsarr_t BitsArrSetOn(bitsarr_t arr, size_t index);

/* returns new status on success. returns old status when invalid input was enterd. complexity o(1) */
bitsarr_t BitsArrSetOff(bitsarr_t arr, size_t index);

/* returns number of ON bits. complexity o(1)*/
size_t BitsArrCountOn(bitsarr_t arr);

size_t BitsArrCountOnLut(bitsarr_t arr);

/* returns number of OFF bits. complexity o(1)*/
size_t BitsArrCountOff(bitsarr_t arr);

/* returns arr such that all bits are set to 0. complexity o(1) */
bitsarr_t BitsArrResetAll(bitsarr_t arr);

/* returns arr such that all bits are set to 1. complexity o(1) */
bitsarr_t BitsArrSetAll(bitsarr_t arr);

/* returns 1 if ON, 0 if OFF, -1 if invalid index entered. complexity o(1) */
int BitsArrIsOn(bitsarr_t arr, size_t index);

/* returns 1 if OFF, 0 if ON, -1 if invalid index entered. complexity o(1) */
int BitsArrIsOff(bitsarr_t arr, size_t index);

/* returns new status. complexity o(1) */
bitsarr_t BitsArrRotR(bitsarr_t arr, size_t n);

/* returns new status. complexity o(1) */
bitsarr_t BitsArrRotL(bitsarr_t arr, size_t n);

/* returns arr as string. complexity o(1) */
char *BitsArrToString(bitsarr_t arr, char *dest);

/* returns new status. complexity o(1) */
bitsarr_t BitsArrMirror(bitsarr_t arr);

bitsarr_t BitsArrMirrorLut(bitsarr_t arr);

/* returns new status on success. returns old status when invalid input enterd. complexity o(1) */
bitsarr_t BitsArrSetBit(bitsarr_t arr, size_t index, int state);


#endif
