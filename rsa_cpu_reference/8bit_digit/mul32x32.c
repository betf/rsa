#include "def.h"

//Function to multiply large numbers
//s digits
//each digit is 32-bit wide
void mult32x32 (u32 *hi, u32 *lo, u32 x, u32 y){
	u32 pp1, pp2, pp3, pp4;

	/* work out partial products */
	pp1 = LOHALF(x) * LOHALF(y);
	pp2 = LOHALF(x) * HIHALF(y);
	pp3 = HIHALF(x) * LOHALF(y);
	pp4 = HIHALF(x) * HIHALF(y);

	/* combine the two middle products & check for overflow */
	pp2 += pp3;
	if (pp2 < pp3) {
		//pp4 += (1 << 16);
		pp4 += (1 << 4);
	}

	/* build the bottom half of the result & check for overflow */
	//*lo = (pp2 << 16) + pp1;
	*lo = (pp2 << 4) + pp1;
	pp4 += (*lo < pp1) ? 1 : 0;

	/* build the top half of the result */
	//*hi = (pp2 >> 16) + pp4;
	*hi = (pp2 >> 4) + pp4;
}
