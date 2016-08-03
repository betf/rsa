#include<stdio.h>
#include<time.h>
#include <stdint.h> /* for uint64_t */
#include<math.h>
#include "h/dbg.h"
#include "def.h"
#include "h/func.h"

#define TCLK 0.5 /* ns */


u32 u[NUM_OF_DIGITS+1]; /* dim(u)=s+1 */
u32 v[NUM_OF_DIGITS+1]; /* dim(u)=s+1 */

/* assembly code to read the TSC */
static inline uint64_t RDTSC(){

	  unsigned int hi, lo;
	  __asm__ volatile("rdtsc" : "=a" (lo), "=d" (hi));
	  return ((uint64_t)hi << 32) | lo;
}


/* Maxeler version 1 */
int main(){

extern u32 x_mgr[], N[], n0_pr, t1[];
uint64_t t;

/* Montgomery's reduction */

	u32* x_ptr=x_mgr;

		setVectors();		
		
		t = RDTSC(); /* Read timestamp counter */
		x_ptr = monPro(x_ptr, x_ptr, &(N[0]), n0_pr); /* Montgomery's reduction */
		t = RDTSC() - t;

	 	printf ("It took me %lld clicks for the monPro (%g ns).\n",t, t*TCLK);
		printf("\nCheck output:\n");

		int k=0;
		for(k=0; k< 2*NUM_OF_DIGITS;k++){
			if(x_ptr[k] != t1[k]){
				printf("Error: Output mismatch!\n\n");
				return -1;

			}
		}
		printf("SUCCESS!\n\n");

return 0;

}


