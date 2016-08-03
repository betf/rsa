#include<stdio.h>
#include<math.h>
#include "h/dbg.h"
#include "def.h"
#include "h/func.h"

/*************************************/
/**** RSA encryption using monPro ****/
/*************************************/

u32 u[NUM_OF_DIGITS+1]; /* dim(u)=s+1 */
u32 v[NUM_OF_DIGITS+1]; /* dim(u)=s+1 */

void main(){

/* Read M from a file - plaintext */
u32 Mr[2*NUM_OF_DIGITS]; /* This is M*r variable */
u32 Nr[2*NUM_OF_DIGITS]; /* This is n*r variable */


u32 reminder[2*NUM_OF_DIGITS];
u32 m_mgr[NUM_OF_DIGITS]; /* M in Montgomery's domain */
u32 x_mgr[NUM_OF_DIGITS]; /* x in Montgomery's domain */
u32 exp[NUM_OF_DIGITS];

int k=0;
int i=0;
int j=0;

extern u32 n_in[],e_in[], plaintext_in[], ciphertext_in[];

	for(k=NUM_OF_DIGITS;k<2*NUM_OF_DIGITS;k++) {
		Mr[k]=plaintext_in[2*NUM_OF_DIGITS-k-1];
		reminder[k]=Mr[k];
		Nr[k]=n_in[2*NUM_OF_DIGITS-k-1];
	}/* Mr holds M*r now */

	for(k=0;k<NUM_OF_DIGITS;k++){
		Nr[k]=0x00000000;
		Mr[k]=0x00000000;
		reminder[k]=0x00000000;
	}

	int exp_dim=NUM_OF_DIGITS;
	u32 exp_temp[exp_dim];

	for(k=0; k<NUM_OF_DIGITS;k++)exp_temp[k] = e_in[NUM_OF_DIGITS-k-1];


#ifdef DEBUG_FLAG
printf("\n\n\n");
DBG("M - input data - size %d digits :\n",NUM_OF_DIGITS);
for(k=NUM_OF_DIGITS;k<2*NUM_OF_DIGITS;k++) printf("M[%2d] = 0x%08x\n",k-NUM_OF_DIGITS,Mr[k]);
printf("\n\n\n");
DBG("N - key - size %d digits:\n", NUM_OF_DIGITS);
for(k=NUM_OF_DIGITS;k<2*NUM_OF_DIGITS;k++) printf("N[%2d] = 0x%08x\n",k-NUM_OF_DIGITS,Nr[k]);
#endif

	restorDiv(reminder, Nr);

	for(j=0;j<NUM_OF_DIGITS;j++){
		m_mgr[j]=reminder[j];
		reminder[j]=0;
	}

#ifdef DEBUG_FLAG
#ifdef DEBUG_CONVERSION
printf("\n");
DBG("M in Montgomery's domain - size %d digits:\n\n",NUM_OF_DIGITS);
for(k=0;k<NUM_OF_DIGITS;k++) printf("m_mgr[%2d] = 0x%08x\n",k,m_mgr[k]);
#endif
#endif

	/* Restoring divison algorithm to find x in Montgomery's domain */

	for(j=NUM_OF_DIGITS+1;j<2*NUM_OF_DIGITS;j++) reminder[j]=0; /* Nr holds N*r now */
	reminder[NUM_OF_DIGITS]=0x00000001; /* reminder now holds r value */

	restorDiv(reminder, Nr);
	
	for(j=0;j<NUM_OF_DIGITS;j++) x_mgr[j]=reminder[j]; /* This is x value in Montgomery's domain */

#ifdef DEBUG_FLAG
#ifdef DEBUG_CONVERSION
printf("\n");
DBG("x in Montgomery's domain for x=1 - size %d digits:\n",NUM_OF_DIGITS);
for(k=0;k<NUM_OF_DIGITS;k++) printf("x_mgr[%2d] = 0x%08x\n",k,x_mgr[k]);
#endif
#endif


	u32 n0_pr=0x95; //n_pr=3489254037, for n=3769388867

	u32* x_ptr=x_mgr;

	k=NUM_OF_DIGITS*DIGIT_WIDTH;

	for ( i = k; i+1 > 0;i--){
		
		x_ptr = monPro(x_ptr, x_ptr, &(Nr[NUM_OF_DIGITS]), n0_pr);

		printf("\n\nIs bit %d equal to 1?\n", i);
		if ( ((exp_temp[i/DIGIT_WIDTH]>>(i%DIGIT_WIDTH)) & 0x01) == 1u ) {
			int j;	

			printf("Yes. monPro(x,M)\n");
			x_ptr= monPro(m_mgr, x_ptr, &(Nr[NUM_OF_DIGITS]), n0_pr);
			printf("\nx_ptr = 0x");
			for(j=NUM_OF_DIGITS-1; j+1 > 0 ;j--)printf("%02x",x_ptr[j]);
		}else {
			
			printf("No. monPro(X,X)\n");
			int j;
			printf("\nx_ptr = 0x");
			for(j=NUM_OF_DIGITS-1; j+1>0;j--)printf("%02x",x_ptr[j]);
			}
	}

	u32* ptr;
	
	/* Return from Montgomery's domain */
	u32 val1[NUM_OF_DIGITS];
	for (j=1;j<NUM_OF_DIGITS;j++) val1[j]=0u;
	val1[0]=0x00000001;

	x_ptr = monPro(x_ptr, val1, &(Nr[NUM_OF_DIGITS]), n0_pr); 

#ifdef DEBUG_FLAG
printf("\n\n\n");
DBG("___Ciphertext___x, size %d digits:\n",NUM_OF_DIGITS);
for(k=0; k<NUM_OF_DIGITS;k++)printf("x[%2d]= 0x%08x\n",k,x_ptr[k]);
printf("\n\n");
#endif

}


