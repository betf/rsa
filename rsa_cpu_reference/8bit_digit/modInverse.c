#include "def.h"
#include<stdbool.h>
#include "h/func.h"

u32 modInverse(u32 x, u32 w){ //x is odd!!!    w is number of register bits
	u32 y[w+1];
	int i=0;
	for(i=0;i<w;i++)y[i]=0;
 	y[1] = 1;

	u32 a[4]; a[2]=a[3]=0;
	u32 b[4]; b[1]=0; 
	u32 c=1;

	#ifdef DBG_MODINVERSE
	printHeader_modI();
	#endif

 	for (i = 2; i< w; i++){


		
		mult32x32(&a[1], &a[0],x, y[i-1]);
		b[0]=1;
		b[1]=b[0]<<i;
		b[0]=0;
		c=1;
		c=c<<(i-1);
		int k;
		for (k = 0; k < 1*DIGIT_WIDTH+1;k++){
	
		//if ( reminder < Nr ) then ( use old reminder in next iteration )
		//else ( reminder = reminder - Nr )	

		int i = 2*1-1;
		bool gr=false;
		bool ls=false;
		do {
			if ( a[i] < b[i] ) ls=true;
			if ( a[i] > b[i] ) gr=true;
			i--;
		} while ( (i+1!=0) && (ls!=true) && (gr!=true) );

		if ( ls == false ) {
			u32 sub, sub1, bor=0x00000000;
			int j=0;
			for(j=0;j<2*1;j++) {

			sub= a[j] - bor;
			bor = (a[j]<bor) ? 1u : 0u;	
			u32 sub1=sub;
			sub-=b[j];
			bor+=(sub1<b[j]) ? 1u : 0u;
			a[j]= sub;

			}
		}
		
		u32 lsb, lsb_mask=0x00000001;
		int j;


		if(k<DIGIT_WIDTH){
			for(j=0;j<(2*1-1);j++){
	
				b[j]=b[j]>>1;
				lsb = b[j+1] & lsb_mask;
				lsb = lsb << ( DIGIT_WIDTH - 1 );
				b[j] = b[j] + lsb;

			}
			b[2*1-1] = b[2*1-1] >> 1;
		}

		}//a[0] holds the result
		//printf("\na[0]=%d",a[0]);
		


		if (c < a[0]) y[i] = y[i-1] + c;
		//if (a[0] != 1) y[i] = y[i-1] + c;
		else y[i]= y[i-1];
		
		#ifdef DBG_MODINVERSE
		printTable_modI( i, y[i-1], a[0], y[i] );
		#endif
		
	}


	
	//calc y[w]//////////////////////////////////////////////////////////////
	b[0]=0u;
	b[1]=0u;
	b[2]=0u;
	b[3]=1u;
	c=1;
	c=c<<(w-1);
	mult32x32(&a[1], &a[0],x, y[w-1]);
	
	int k;
	for (k = 0; k < 2*DIGIT_WIDTH+1;k++){
	
		//if ( reminder < Nr ) then ( use old reminder in next iteration )
		//else ( reminder = reminder - Nr )	

		int i = 2*2-1;
		bool gr=false;
		bool ls=false;
		do {
			if ( a[i] < b[i] ) ls=true;
			if ( a[i] > b[i] ) gr=true;
			i--;
		} while ( (i+1!=0) && (ls!=true) && (gr!=true) );

		if ( ls == false ) {
			u32 sub, sub1, bor=0x00000000;
			int j;
			for(j=0;j<2*2;j++) {

			sub= a[j] - bor;
			bor = (a[j]<bor) ? 1u : 0u;	
			u32 sub1=sub;
			sub-=b[j];
			bor+=(sub1<b[j]) ? 1u : 0u;
			a[j]= sub;

			}
		}
		
		u32 lsb, lsb_mask=0x00000001;
		int j;


		if(k<2*DIGIT_WIDTH){
			for(j=0;j<(2*2-1);j++){

				b[j]=b[j]>>1;
				lsb = b[j+1] & lsb_mask;
				lsb = lsb << ( DIGIT_WIDTH - 1 );
				b[j] = b[j] + lsb;

			}
			b[2*2-1] = b[2*2-1] >> 1;
		}

	}//a[0] holds the result

		if (c < a[0]) y[w] = y[w-1] + c;
		//if ( a[0] != 1u) y[w] = y[w-1] + c;
		else y[w]= y[w-1];

		#ifdef DBG_MODINVERSE
		printTable_modI( w, y[w-1], a[0], y[w] );
		printFooter();
		#endif
		


return y[w];
}
