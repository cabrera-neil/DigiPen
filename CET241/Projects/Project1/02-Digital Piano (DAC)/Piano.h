#define C_NOTE 2388
#define D_NOTE 2128
#define E_NOTE 1896
#define F_NOTE 1790
#define G_NOTE 1582
#define A_NOTE 1420
#define B_NOTE 1265
#define C6_NOTE 1194
#define O_NOTE 0

extern unsigned short freq_index;

// ********************Piano Init********************
// Initialise Piano Key Inputs
// Input: none
// Output: none
void Piano_Init(void);

// ********************Piano Out********************
// Input from Piano Key Inputs
// Input: none
// Output: 0 to 15 (depending on Key Combination of CDEG)
void Piano_In(void);
