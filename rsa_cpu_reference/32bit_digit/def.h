#ifndef DEFINITIONS

#define DEFINITIONS 

#include <stdio.h>



typedef unsigned int u32;
#define LOHALF(n) (((n) << 16) >> 16)
#define HIHALF(n) ((n) >> 16)

//typedef unsigned char u32;
//#define LOHALF(n) ((n) & 0x0f)
//#define HIHALF(n) (((n) >> 4) & 0x0f)

#define NUM_OF_DIGITS 32u //s=2, a and b are 64-bits wide
#define DIGIT_WIDTH 32u  //w=32, radix 2^32
#define EXP_BITS 3*32
#define EXP_DIGITS 3 

#define DEBUG_FLAG 1
//#define DEBUG_STEP_1 1
//#define DEBUG_STEP_2 1
//#define DEBUG_STEP_3_4 1
//#define DEBUG_CONVERSION 1

//#define DBG_MODINVERSE 1

#endif
