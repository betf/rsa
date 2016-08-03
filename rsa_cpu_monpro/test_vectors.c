#include "def.h"

u32 x_mgr[NUM_OF_DIGITS]; 
u32 N[NUM_OF_DIGITS];
u32 n0_pr;
u32 t1[2*NUM_OF_DIGITS];



// Test vector for NUM_OF_DIGITS = 32; 
// x_mgr is x=1 in Montgomery's domain  x_mgr . x_mgr = x_mgr, if . is Montgomery's reduction

void setVectors(void){

n0_pr=0x0567b73d;

//___Step 1, t is:___

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


x_mgr[ 0] = 0x55955815;
x_mgr[ 1] = 0xc730e3d3;
x_mgr[ 2] = 0x417c39a0;
x_mgr[ 3] = 0x07858f2e;
x_mgr[ 4] = 0x96fe0efa;
x_mgr[ 5] = 0x2c80ac27;
x_mgr[ 6] = 0x1fa3e0ac;
x_mgr[ 7] = 0x04a29f3b;
x_mgr[ 8] = 0xb719b0e3;
x_mgr[ 9] = 0x33e7f7eb;
x_mgr[10] = 0x74cefb47;
x_mgr[11] = 0xa6ad037a;
x_mgr[12] = 0xcd34f8fc;
x_mgr[13] = 0xfe79c9cb;
x_mgr[14] = 0xc44450b9;
x_mgr[15] = 0xccdb5c80;
x_mgr[16] = 0xe1842656;
x_mgr[17] = 0xc892069a;
x_mgr[18] = 0x6e47e696;
x_mgr[19] = 0xf7c4f636;
x_mgr[20] = 0xa3304848;
x_mgr[21] = 0x6799ebbe;
x_mgr[22] = 0xca7a9285;
x_mgr[23] = 0x425add2f;
x_mgr[24] = 0x8fd9e8f0;
x_mgr[25] = 0xe2fe25e6;
x_mgr[26] = 0x656ea404;
x_mgr[27] = 0x7a37caa2;
x_mgr[28] = 0xa1598676;
x_mgr[29] = 0x0d5f6cbe;
x_mgr[30] = 0xc0c62aa0;
x_mgr[31] = 0x561e9867;

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

}
/*
M - plaintext - size 32 digits :
M[ 0] = 0xf4e80b9f
M[ 1] = 0xcfccb698
M[ 2] = 0x8e40f3ad
M[ 3] = 0x4e636af9
M[ 4] = 0x68f49600
M[ 5] = 0xd62e5a12
M[ 6] = 0xd2cd8fc1
M[ 7] = 0x4a36c6e4
M[ 8] = 0x19eacedf
M[ 9] = 0x4402ad18
M[10] = 0x45fafdb2
M[11] = 0x61cf6941
M[12] = 0x2e3c6c80
M[13] = 0xf44bb5c5
M[14] = 0xe9a2f9c6
M[15] = 0xb16b2148
M[16] = 0x44964038
M[17] = 0x756099f0
M[18] = 0x55799fe3
M[19] = 0x71e474b5
M[20] = 0xf59545e6
M[21] = 0x4ef191e3
M[22] = 0x475cd694
M[23] = 0xe3fc9b2b
M[24] = 0x2aa12009
M[25] = 0x66729f13
M[26] = 0xadf5f315
M[27] = 0x228f5c95
M[28] = 0x2306f2d3
M[29] = 0x93b7e5e0
M[30] = 0x48fd1f17
M[31] = 0x0002257f




M in Montgomery's domain - size 32 digits:

m_mgr[ 0] = 0xdf38fa75
m_mgr[ 1] = 0xe463dd91
m_mgr[ 2] = 0x7481b745
m_mgr[ 3] = 0x41039b78
m_mgr[ 4] = 0x9f493fe2
m_mgr[ 5] = 0x99db3c67
m_mgr[ 6] = 0xf17da95d
m_mgr[ 7] = 0x578f9cc3
m_mgr[ 8] = 0x9a2a175d
m_mgr[ 9] = 0x0bfd7afd
m_mgr[10] = 0xfaa310be
m_mgr[11] = 0x908272f0
m_mgr[12] = 0x21a016c8
m_mgr[13] = 0x07b9fc7f
m_mgr[14] = 0x3ee76e4c
m_mgr[15] = 0x2bc3a085
m_mgr[16] = 0xcae7b0c3
m_mgr[17] = 0xb306fb4b
m_mgr[18] = 0x8c7bda3a
m_mgr[19] = 0x7c9d1fb0
m_mgr[20] = 0x97d064a9
m_mgr[21] = 0x2a7c8da7
m_mgr[22] = 0xe1110c48
m_mgr[23] = 0xe290b475
m_mgr[24] = 0xefd37023
m_mgr[25] = 0xb5ed8275
m_mgr[26] = 0x7b88eb25
m_mgr[27] = 0xf8c4ebda
m_mgr[28] = 0xece2d785
m_mgr[29] = 0x6890fe42
m_mgr[30] = 0x9bd504d2
m_mgr[31] = 0x4413ee85

___Ciphertext___x, size 32 digits:
x[ 0]= 0xba3a435b
x[ 1]= 0x424e177c
x[ 2]= 0xe69f9d41
x[ 3]= 0x218111ff
x[ 4]= 0xc44b676d
x[ 5]= 0x829e0142
x[ 6]= 0xce055839
x[ 7]= 0x609787ad
x[ 8]= 0xcb99ac7e
x[ 9]= 0x715c76f3
x[10]= 0xa0212b28
x[11]= 0x808af8f4
x[12]= 0x48ee9322
x[13]= 0x40f5b36c
x[14]= 0x64cf34c6
x[15]= 0xedc90cec
x[16]= 0xdbc6e621
x[17]= 0xeff0b0a8
x[18]= 0x2378e008
x[19]= 0x91f49a72
x[20]= 0xc3464498
x[21]= 0xc7a61eae
x[22]= 0xf32af4aa
x[23]= 0x8b92b9ec
x[24]= 0x492c9ce5
x[25]= 0x062cd739
x[26]= 0x90edecef
x[27]= 0x9a899c87
x[28]= 0xd778ec39
x[29]= 0x0f504cc4
x[30]= 0x1eb667a4
x[31]= 0x3d2ab25b
*/

