#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Maxfiles.h"
#include "MaxSLiCInterface.h"

#include<time.h>
#include <stdint.h> 
#include "dbg.h"
#include "def.h"
#include "func.h"

#include <stdint.h>
//#include <MaxCompilerRT.h>
//#include "Maxfiles.h" 			// Includes .max files
//#include <MaxSLiCInterface.h>	// Simple Live CPU interface

#define DATALENGTH (REPEAT*NUM_OF_DIGITS)

/* #define TCLK 0.5 */  /* ns */
#define TCLK 0.3745 /* ns */

/* Maxeler version 1 */

extern u32 x_mgr[];
extern u32 x[];
extern u32 y[];

u32 N[NUM_OF_DIGITS];
u32 n0_pr;
u32 t1[2*NUM_OF_DIGITS];

static inline uint64_t RDTSC(){

	  unsigned int hi, lo;
	  __asm__ volatile("rdtsc" : "=a" (lo), "=d" (hi));
	  return ((uint64_t)hi << 32) | lo;
}

/* Test vector for NUM_OF_DIGITS = 32; */
/* x_mgr is x=1 in Montgomery's domain  x_mgr . x_mgr = x_mgr, if . is Montgomery's reduction */

void setVectors(void){

n0_pr=0x0567b73d;

/* ___Step 1, t is:___ */

t1[ 0]= 0x98c071b9;
t1[ 1]= 0xb8e0f43b;
t1[ 2]= 0x434e336e;
t1[ 3]= 0xa9a3ccc4;
t1[ 4]= 0xe53c2f4d;
t1[ 5]= 0x40a84736;
t1[ 6]= 0x567bacc9;
t1[ 7]= 0x06e039db;
t1[ 8]= 0x20359ac3;
t1[ 9]= 0x4036804f;
t1[10]= 0xf30f8381;
t1[11]= 0xc0cd5311;
t1[12]= 0x87f367d0;
t1[13]= 0x51861f47;
t1[14]= 0x0ed1a32a;
t1[15]= 0x9c84c2c2;
t1[16]= 0x3f1d40d5;
t1[17]= 0x09d75144;
t1[18]= 0x0a00b40b;
t1[19]= 0x9d600869;
t1[20]= 0x034eae9c;
t1[21]= 0x3c9b428d;
t1[22]= 0x12206eb1;
t1[23]= 0xd4209689;
t1[24]= 0x66129c06;
t1[25]= 0x4e801e1b;
t1[26]= 0x6d8362bc;
t1[27]= 0x81bdf9f6;
t1[28]= 0x02a4c1af;
t1[29]= 0x69b48175;
t1[30]= 0x9ceac8e3;
t1[31]= 0x6957e12a;
t1[32]= 0x1a3ede50;
t1[33]= 0xe48672fb;
t1[34]= 0xb6316a07;
t1[35]= 0x810cf947;
t1[36]= 0x8a55dc18;
t1[37]= 0x685ddfa8;
t1[38]= 0xfa50645e;
t1[39]= 0x5dd637a5;
t1[40]= 0x13b11da9;
t1[41]= 0x416de351;
t1[42]= 0x831bf0e1;
t1[43]= 0x36168013;
t1[44]= 0x6c1a58dd;
t1[45]= 0x2715a1ce;
t1[46]= 0xbcf2f637;
t1[47]= 0xdbf23fec;
t1[48]= 0x8044a60d;
t1[49]= 0x0604ffa1;
t1[50]= 0x0404c849;
t1[51]= 0xc353bf1f;
t1[52]= 0x4406193a;
t1[53]= 0xad18318e;
t1[54]= 0x3572bafd;
t1[55]= 0xc11f5d9b;
t1[56]= 0x8fb91e5e;
t1[57]= 0x1f6cd961;
t1[58]= 0x3a6bf3e8;
t1[59]= 0x742a35b7;
t1[60]= 0xafbe9381;
t1[61]= 0x89bd756f;
t1[62]= 0xc891b20d;
t1[63]= 0x1cf8920d;

int i;
for(i=0; i<REPEAT; i++){
x_mgr[ i*NUM_OF_DIGITS + 0] = 0x55955815;
x_mgr[ i*NUM_OF_DIGITS + 1] = 0xc730e3d3;
x_mgr[ i*NUM_OF_DIGITS + 2] = 0x417c39a0;
x_mgr[ i*NUM_OF_DIGITS + 3] = 0x07858f2e;
x_mgr[ i*NUM_OF_DIGITS + 4] = 0x96fe0efa;
x_mgr[ i*NUM_OF_DIGITS + 5] = 0x2c80ac27;
x_mgr[ i*NUM_OF_DIGITS + 6] = 0x1fa3e0ac;
x_mgr[ i*NUM_OF_DIGITS + 7] = 0x04a29f3b;
x_mgr[ i*NUM_OF_DIGITS + 8] = 0xb719b0e3;
x_mgr[ i*NUM_OF_DIGITS + 9] = 0x33e7f7eb;
x_mgr[ i*NUM_OF_DIGITS +10] = 0x74cefb47;
x_mgr[ i*NUM_OF_DIGITS +11] = 0xa6ad037a;
x_mgr[ i*NUM_OF_DIGITS +12] = 0xcd34f8fc;
x_mgr[ i*NUM_OF_DIGITS +13] = 0xfe79c9cb;
x_mgr[ i*NUM_OF_DIGITS +14] = 0xc44450b9;
x_mgr[ i*NUM_OF_DIGITS +15] = 0xccdb5c80;
x_mgr[ i*NUM_OF_DIGITS +16] = 0xe1842656;
x_mgr[ i*NUM_OF_DIGITS +17] = 0xc892069a;
x_mgr[ i*NUM_OF_DIGITS +18] = 0x6e47e696;
x_mgr[ i*NUM_OF_DIGITS +19] = 0xf7c4f636;
x_mgr[ i*NUM_OF_DIGITS +20] = 0xa3304848;
x_mgr[ i*NUM_OF_DIGITS +21] = 0x6799ebbe;
x_mgr[ i*NUM_OF_DIGITS +22] = 0xca7a9285;
x_mgr[ i*NUM_OF_DIGITS +23] = 0x425add2f;
x_mgr[ i*NUM_OF_DIGITS +24] = 0x8fd9e8f0;
x_mgr[ i*NUM_OF_DIGITS +25] = 0xe2fe25e6;
x_mgr[ i*NUM_OF_DIGITS +26] = 0x656ea404;
x_mgr[ i*NUM_OF_DIGITS +27] = 0x7a37caa2;
x_mgr[ i*NUM_OF_DIGITS +28] = 0xa1598676;
x_mgr[ i*NUM_OF_DIGITS +29] = 0x0d5f6cbe;
x_mgr[ i*NUM_OF_DIGITS +30] = 0xc0c62aa0;
x_mgr[ i*NUM_OF_DIGITS +31] = 0x561e9867;
}


N[ 0] = 0xaa6aa7eb;
N[ 1] = 0x38cf1c2c;
N[ 2] = 0xbe83c65f;
N[ 3] = 0xf87a70d1;
N[ 4] = 0x6901f105;
N[ 5] = 0xd37f53d8;
N[ 6] = 0xe05c1f53;
N[ 7] = 0xfb5d60c4;
N[ 8] = 0x48e64f1c;
N[ 9] = 0xcc180814;
N[10] = 0x8b3104b8;
N[11] = 0x5952fc85;
N[12] = 0x32cb0703;
N[13] = 0x01863634;
N[14] = 0x3bbbaf46;
N[15] = 0x3324a37f;
N[16] = 0x1e7bd9a9;
N[17] = 0x376df965;
N[18] = 0x91b81969;
N[19] = 0x083b09c9;
N[20] = 0x5ccfb7b7;
N[21] = 0x98661441;
N[22] = 0x35856d7a;
N[23] = 0xbda522d0;
N[24] = 0x7026170f;
N[25] = 0x1d01da19;
N[26] = 0x9a915bfb;
N[27] = 0x85c8355d;
N[28] = 0x5ea67989;
N[29] = 0xf2a09341;
N[30] = 0x3f39d55f;
N[31] = 0xa9e16798;

for(i=0; i<REPEAT; i++){
/* x array for a[0]*b */
x [ i*NUM_OF_DIGITS + 0]= 0x98c071b9;
x [ i*NUM_OF_DIGITS +1]= 0xce22384f;
x [ i*NUM_OF_DIGITS +2]= 0xbd1fba20;
x [ i*NUM_OF_DIGITS +3]= 0x22f28ec6;
x [ i*NUM_OF_DIGITS +4]= 0x717f2a82;
x [ i*NUM_OF_DIGITS +5]= 0x076e8733;
x [ i*NUM_OF_DIGITS +6]= 0xcdc88e1c;
x [ i*NUM_OF_DIGITS +7]= 0x8c6a57d7;
x [ i*NUM_OF_DIGITS +8]= 0x2d088a9f;
x [ i*NUM_OF_DIGITS +9]= 0x52071e47;
x [ i*NUM_OF_DIGITS +10]= 0x8eae04d3;
x [ i*NUM_OF_DIGITS +11]= 0xad653902;
x [ i*NUM_OF_DIGITS +12]= 0xa19b0cac;
x [ i*NUM_OF_DIGITS +13]= 0x978255a7;
x [ i*NUM_OF_DIGITS +14]= 0xfe07372d;
x [ i*NUM_OF_DIGITS +15]= 0x8c4a9680;
x [ i*NUM_OF_DIGITS +16]= 0xcb12b50e;
x [ i*NUM_OF_DIGITS +17]= 0x9fe17aa2;
x [ i*NUM_OF_DIGITS +18]= 0xc6777a4e;
x [ i*NUM_OF_DIGITS +19]= 0x4338c26e;
x [ i*NUM_OF_DIGITS +20]= 0xf5b6ade8;
x [ i*NUM_OF_DIGITS +21]= 0xb43fa696;
x [ i*NUM_OF_DIGITS +22]= 0x2ed4bce9;
x [ i*NUM_OF_DIGITS +23]= 0x04d74cdb;
x [ i*NUM_OF_DIGITS +24]= 0xf8a29bb0;
x [ i*NUM_OF_DIGITS +25]= 0x68be2bde;
x [ i*NUM_OF_DIGITS +26]= 0x24c8d454;
x [ i*NUM_OF_DIGITS +27]= 0xee854f4a;
x [ i*NUM_OF_DIGITS +28]= 0x733e97ae;
x [ i*NUM_OF_DIGITS +29]= 0x46cb3b96;
x [ i*NUM_OF_DIGITS +30]= 0xde087f20;
x [ i*NUM_OF_DIGITS +31]= 0x7bd8e873;


/* y array for a[0]*b */
y [ i*NUM_OF_DIGITS +0]= 0x1c9c839d;
y [ i*NUM_OF_DIGITS +1]= 0x42976fa2;
y [ i*NUM_OF_DIGITS +2]= 0x15e472f7;
y [ i*NUM_OF_DIGITS +3]= 0x0283bbdd;
y [ i*NUM_OF_DIGITS +4]= 0x327a70cb;
y [ i*NUM_OF_DIGITS +5]= 0x0ee0af5d;
y [ i*NUM_OF_DIGITS +6]= 0x0a93dedd;
y [ i*NUM_OF_DIGITS +7]= 0x018cb31d;
y [ i*NUM_OF_DIGITS +8]= 0x3d3658af;
y [ i*NUM_OF_DIGITS +9]= 0x115a4d30;
y [ i*NUM_OF_DIGITS +10]= 0x270cde17;
y [ i*NUM_OF_DIGITS +11]= 0x37b8ae33;
y [ i*NUM_OF_DIGITS +12]= 0x449a4d1b;
y [ i*NUM_OF_DIGITS +13]= 0x5512e471;
y [ i*NUM_OF_DIGITS +14]= 0x419d2e17;
y [ i*NUM_OF_DIGITS +15]= 0x447c57df;
y [ i*NUM_OF_DIGITS +16]= 0x4b64703c;
y [ i*NUM_OF_DIGITS +17]= 0x430d7e31;
y [ i*NUM_OF_DIGITS +18]= 0x24de355a;
y [ i*NUM_OF_DIGITS +19]= 0x52d4f0a3;
y [ i*NUM_OF_DIGITS +20]= 0x368e3b3f;
y [ i*NUM_OF_DIGITS +21]= 0x22a28b81;
y [ i*NUM_OF_DIGITS +22]= 0x43b0d1a8;
y [ i*NUM_OF_DIGITS +23]= 0x162ee128;
y [ i*NUM_OF_DIGITS +24]= 0x301745aa;
y [ i*NUM_OF_DIGITS +25]= 0x4be2ce9b;
y [ i*NUM_OF_DIGITS +26]= 0x21e8e8c1;
y [ i*NUM_OF_DIGITS +27]= 0x28dbd2cd;
y [ i*NUM_OF_DIGITS +28]= 0x35f0da44;
y [ i*NUM_OF_DIGITS +29]= 0x04787c3f;
y [ i*NUM_OF_DIGITS +30]= 0x407241d1;
y [ i*NUM_OF_DIGITS +31]= 0x1cca660a;
}
}

unsigned int data_out_x[DATALENGTH];
unsigned int data_out_y[DATALENGTH];



int main(int argc, char **argv){

uint64_t t;
int i;
int status = 0;


/* Montgomery's reduction */
	u32* x_ptr=x_mgr;
	setVectors(); /* Set test-vectors */
	u32 a=x_ptr[0]; /* Set scalar input */

	printf("Running DFE\n");
	t = RDTSC();
	for(int i=0; i<NUM_OF_DIGITS;i++)
		monpro(DATALENGTH, a, x_ptr, data_out_x, data_out_y);
	t = RDTSC() - t;
	printf ("It took me %lld clicks (%g ns).\n",t, t*TCLK);

	/* Verify output */
	printf("Verifying output\n");

	for(i=0; i<DATALENGTH; i++){
		if ( (data_out_x[i] != x[i]) || (data_out_y[i] != y[i])) {
			printf("[%d] Verification error, in: %u and %u != expected: %u and %u\n", i, data_out_x[i], data_out_y[i], x[i], y[i]);
			status = 1;
		}
	}

	if (status)
		printf("Test failed.\n");
	else
		printf("Test passed OK!\n");

	//printf("Shutting down\n");
	//max_close_device(device);
	//max_destroy(maxfile);

	//return status;

	return 0;

}


