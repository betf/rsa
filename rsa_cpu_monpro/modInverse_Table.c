#include "def.h"


void printHeader_modI(void){

printf("\n     base16\n");
printf("      _____ ___________ ______________ __________________ ____________ ____________\n");
printf("     |  i  |    2^i    |    y(i-1)    | x*y(i-1) mod 2^i |   2^(i-1)  |    y(i)    |\n");
printf("     |_____|___________|______________|__________________|____________|____________|\n");

}
void printTable_modI( int col_ind, u32 col_1, u32 col_2, u32 col_3 ){

u32 exp_i=1<<col_ind;
u32 exp_i1=1<<(col_ind-1);

printf("     | %2d  |  %08x |   %08x   |     %08x     |  %08x  |  %08x  |\n", col_ind, exp_i, col_1, col_2, exp_i1, col_3);
printf("     |_____|___________|______________|__________________|____________|____________|\n");
}

void printFooter(void){

printf("\n\n\n");
}


