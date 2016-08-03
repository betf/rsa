#include "def.h"
#include<stdbool.h>
//Restoring division algorithm:
	



void restorDiv(u32* reminder, u32* Nr){

	int i,k,j;	
	
		/*int inex_check;
		printf("\n\nreminder - first:\n");
		for(inex_check=0;inex_check<2*NUM_OF_DIGITS;inex_check++)printf("%02x ", reminder[inex_check]);
		printf("\nNr - first:\n");
		for(inex_check=0;inex_check<2*NUM_OF_DIGITS;inex_check++)printf("%02x ", Nr[inex_check]);
*/

	for (k = 0; k < NUM_OF_DIGITS*DIGIT_WIDTH+1;k++){
	
		//if ( reminder < Nr ) then ( use old reminder in next iteration )
		//else ( reminder = reminder - Nr )	

		
		i = 2*NUM_OF_DIGITS-1;
		bool gr=false;
		bool ls=false;

		do {
			if ( reminder[i] < Nr[i] ) ls=true;
			if ( reminder[i] > Nr[i] ) gr=true;
			i--;
		} while ( (i+1!=0) && (ls!=true) && (gr!=true) );

		if ( ls == false ) {
			//u32 sub, sub1, bor=0x00000000;
			u32 sub, sub1, bor=0x00;
			for(j=0;j<2*NUM_OF_DIGITS;j++) {

			sub= reminder[j] - bor;
			bor = (reminder[j]<bor) ? 1u : 0u;	
			u32 sub1=sub;
			sub-=Nr[j];
			bor+=(sub1<Nr[j]) ? 1u : 0u;
			reminder[j]= sub;

			}
		}
		//u32 lsb, lsb_mask=0x00000001;
		u32 lsb, lsb_mask=0x01;


		if(k<NUM_OF_DIGITS*DIGIT_WIDTH){		
			for(j=0;j<(2*NUM_OF_DIGITS-1);j++){

				Nr[j]=Nr[j]>>1;
				lsb = Nr[j+1] & lsb_mask;
				lsb = lsb << ( DIGIT_WIDTH - 1 );
				Nr[j] = Nr[j] + lsb;

			}
		 	Nr[2*NUM_OF_DIGITS-1] = Nr[2*NUM_OF_DIGITS-1] >> 1;
		}
/*
		int inex_check;
		printf("\n\nreminder:\n");
		for(inex_check=0;inex_check<2*NUM_OF_DIGITS;inex_check++)printf("%02x ", reminder[inex_check]);
		printf("\nNr:\n");
		for(inex_check=0;inex_check<2*NUM_OF_DIGITS;inex_check++)printf("%02x ", Nr[inex_check]);*/
	}



	//Let's shift Nr back
	for(j=0;j<NUM_OF_DIGITS;j++) {
		Nr[j+NUM_OF_DIGITS]=Nr[j];
		Nr[j]=0;
	}

}

