#include "def.h"
#include "h/func.h"
#include <stdbool.h>

//Montgomery product
//a, b - numbers having s digits, each digit has w bits
//calculation is performed in radix 2^w

//Montgomery product steps:
//Step 1. t := a*b
//Step 2. m := (t * n_pr) mod r
//Step 3. u := (t + m * n)/r
//Step 4. if u >= n then return u - n
//else return u

extern u32 u[NUM_OF_DIGITS+1];//dim(u)=s+1
extern u32 v[NUM_OF_DIGITS+1];//dim(u)=s+1

u32 calcRem(u32* tempA, u32* tempB){ 
	
	int k;
	for (k = 0; k < 2*DIGIT_WIDTH+1;k++){
	
		//if ( reminder < Nr ) then ( use old reminder in next iteration )
		//else ( reminder = reminder - Nr )	

		int ind_st2 = 2*2-1;
		bool gr=false;
		bool ls=false;
		do {
			if ( tempA[ind_st2] < tempB[ind_st2] ) ls=true;
			if ( tempA[ind_st2] > tempB[ind_st2] ) gr=true;
			ind_st2--;
		} while ( (ind_st2+1!=0) && (ls!=true) && (gr!=true) );

		if ( ls == false ) {
			u32 sub, sub1, bor=0x00000000;
			int ind_5;
			for(ind_5=0;ind_5<2*2;ind_5++) {

			sub= tempA[ind_5] - bor;
			bor = (tempA[ind_5]<bor) ? 1u : 0u;	
			u32 sub1=sub;
			sub-=tempB[ind_5];
			bor+=(sub1<tempB[ind_5]) ? 1u : 0u;
			tempA[ind_5]= sub;

			}
		}
		
		u32 lsb, lsb_mask=0x00000001;
		int ind_6;


		if(k<2*DIGIT_WIDTH){
			for(ind_6=0;ind_6<(2*2-1);ind_6++){

				tempB[ind_6]=tempB[ind_6]>>1;
				lsb = tempB[ind_6+1] & lsb_mask;
				lsb = lsb << ( DIGIT_WIDTH - 1 );
				tempB[ind_6] = tempB[ind_6] + lsb;

			}
			tempB[2*2-1] = tempB[2*2-1] >> 1;
		}

	}
return tempA[0];
}

u32* monPro(u32* a, u32* b, u32* n, u32 n0_pr){

	u32 s=NUM_OF_DIGITS;
	u32 w=DIGIT_WIDTH;
	u32 t[2*s+1]; //2*s+1 to hold mul result of numbers with s digits (+1 for the last carry)

	int i=0;
	int j=0;
	int k=0;


//Step 1.

u32 carry=0;
u32 sum=0;

	for(i=0;i<2*s+1;i++)t[i]=0; //Fill t with zeros

			/*
			//Debug
			int k=0;
			printf("\na:\n");
			for(k=0; k<s;k++)printf("\na[%2d]= 0x%08x",k,*(a+k));
			printf("\nb:\n");
			for(k=0; k<s;k++)printf("\nb[%2d]= 0x%08x",k,*(b+k));
			printf("\n\n");
			*/

	for (i=0; i<s; i++){

		carry=0;
		for (j=0; j<s; j++) {
			
			u32 lo_digit, hi_digit; //Provide memory for
			u32*x=&lo_digit;        //the lower and upper part of the 64-bit result
			u32*y=&hi_digit;
			
			//printf("\na[%2d]=%08x\n",j,a[j]);
			//printf("b[%2d]=%08x\n\n",i,b[i]);
			
			mult32x32(y, x, a[i], b[j]); //mul digit a[j] and b[i] of numbers a and b

			//printf("\nI am in step1:)\n");
			//printf("\na[%d]=%02x",i, a[i]);
			//printf("\nb[%d]=%02x",j, b[j]);
			//printf("\nx=%02x", *x);
			//printf("\ny=%02x", *y);


			sum = *x + carry; 
			//printf("\nsum = x + carry = %02x",sum);			
			carry = (sum < carry) ? 1 : 0;
			//printf("\ncarry=%02x",carry);
			sum += t[i+j];
			//printf("\nt[i+j]; sum += t[i+j]; %02x; %02x",t[i+j], sum);			
			carry += (sum < t[i+j]) ? 1 : 0;
			//printf("\ncarry+=....=%02x",carry);			
			t[i+j] = sum;
			//printf("\nt[i+j] = %02x",t[i+j]);			
			carry += *y;
			//printf("\ncarry +=y, carry = %02x",carry);
			//printf("\n\n    Next iteration       \n\n");						

			//printf("t[%2d]=%08x\n\n",i+j,t[i+j]);

		}
		t[i+s]=carry;
	}


	t[2*s-1]=carry; //write last carry to the last t element	
	
	////////////////////////////
	//int k;
	#ifdef DEBUG_FLAG
	#ifdef DEBUG_STEP_1
	printf("\n___Step 1, t is:___\n");
	for(k=0; k<2*s;k++)printf("\nt[%2d]= 0x%08x",k,t[k]);
	printf("\n\n");
	#endif
	#endif
	///////////////////////////

//Step 2.

u32 m=0;
//unsigned long long temp=1u;
carry=0; //reset carry before the t update

 for (i=0; i<s; i++){ 
	
	u32 lo_digit, hi_digit; //Provide memory for
	u32*x=&lo_digit;        //the lower and upper part of the 64-bit result
	u32*y=&hi_digit;
	mult32x32(y, x, t[i], n0_pr);
	//m = (t[i]*n0_pr)%(temp<<w); //find i-th digit of m
 				    //use it in next loop and throw away


/////////////////////////////////
//calc y[w]//////////////////////////////////////////////////////////////
	u32 tempA[4]={0,0,0,0};	
	u32 tempB[4];
	
	tempA[0]=*x;
	tempA[1]=*y;	

	tempB[0]=0;
	tempB[1]=0u;
	tempB[2]=0u;
	tempB[3]=1u;

	//printf("\ntempA: %08x %08x %08x %08x", tempA[3], tempA[2], tempA[1], tempA[0]);
	//printf("\ntempB: %08x %08x %08x %08x", tempB[3], tempB[2], tempB[1], tempB[0]);

	m=calcRem(tempA, tempB);

//////////////////////////////////
	//m = (t[i]*n0_pr)%1000;

	////////////////////////////
	#ifdef DEBUG_FLAG	
	#ifdef DEBUG_STEP_2
	printf("\nm[%2d]= 0x%08x",i,m);
	//printf("\ntemp<<w=0x%016llx", temp<<w);
	printf("\nt[i]*n0_pr=%08x",t[i]*n0_pr);
	printf("\nt[i]=%08x", t[i]);
	printf("\nn0_pr=%08x", n0_pr);
	printf("\n\n");
	#endif
	#endif
	///////////////////////////


	for (j=0; j<s; j++) {
			
		u32 lo_digit, hi_digit;
		u32*x=&lo_digit;
		u32*y=&hi_digit;

		mult32x32(y, x, m, n[j]);
		sum = *x + carry;
		carry = (sum < carry) ? 1 : 0;
		sum += t[i+j];
		carry += (sum < t[i+j]) ? 1 : 0;
		t[i+j] = sum;
		carry += *y;
	}
	
	//Allow carry to propagate till the end of the array t
	//It is necessary since t is not initialized to 0 like in step 1
	for (j = i + s; j < 2*s ; j++){
		sum = t[j] + carry;
		carry = (sum < carry) ? 1 : 0;
		t[j] = sum;
	}
	t[2*s]=carry; //t is 2*s+1 digits long

  }

////////////////////////////
	//int k;
	#ifdef DEBUG_FLAG
	#ifdef DEBUG_STEP_2
	printf("\n___Step 2, t is:___\n");
	for(k=0; k<2*s+1;k++)printf("\nt[%2d]= 0x%08x",k,t[k]);
	printf("\n\n");
	///////////////////////////
	#endif
	#endif

//Steps 3 and 4.
	
u32 borrow, diff = 0;

	for (j = 0; j < s+1; j++) u[j]= t[j+s];  //copy upper half of t to u
	
		borrow = 0;
		for (j = 0; j < s ; j++){
			diff= u[j] - borrow;
			borrow = (u[j]<borrow) ? 1 : 0;	
			u32 diff1=diff;
			diff-=n[j];
			borrow+=(diff1<n[j]) ? 1 : 0;
			v[j]= diff;
		}

			diff= u[s] - borrow;
			borrow = (u[s]<borrow) ? 1 : 0;	
			u32 diff1=diff;
			diff-=0;
			borrow+=(diff1<0) ? 1 : 0;
			v[s]= diff;

		//u[s]=0;
		//v[s]=0;



////////////////////////////
	//int k;
	#ifdef DEBUG_FLAG
	#ifdef DEBUG_STEP_3_4
	printf("\n___Step 3,4, u and v are:___\n");
	for(k=0; k<s+1;k++)printf("\nu[%2d]= 0x%08x    v[%2d]= 0x%08x",k,u[k],k,v[k]);
	printf("\n\n");
	#endif
	#endif
	///////////////////////////



		if (borrow == 0) {printf("\nReturn V.");return v;} //v[0]...v[s-1] is result
		else {printf("\nReturn U.");return u;}             //u[0]...u[s-1] is result



}
