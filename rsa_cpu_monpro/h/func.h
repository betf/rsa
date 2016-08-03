#include "../def.h"

void mult32x32 (u32 *hi, u32 *lo, u32 x, u32 y);
u32* monPro(u32* a, u32* b, u32* n, u32 n0_pr);
u32 modInverse(u32 x, u32 w);
void restorDiv(u32* reminder, u32* Nr);

void printHeader_modI(void);
void printTable_modI( int col_ind, u32 col_1, u32 col_2, u32 col_3 );
void printFooter(void);
void setVectors(void);
