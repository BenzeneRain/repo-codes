#define _DES_KEY_GEN_
#include <stdint.h>
#include <math.h>
#include <memory.h>
#include "DESKeyGen.h"

void DESKeyGen(uint8_t *InitKey, uint8_t *thisKey[])
{
	uint8_t Keys[16][6];
	uint8_t CD0[8];
	uint8_t *C0;
	uint8_t *D0;
	uint8_t CDi[8];
	uint8_t *Ci;
	uint8_t *Di;
	int i, j, k, m, turn;
	int bit, loc;
	
	C0 = CD0;
	D0 = CD0 + 4;
	Ci = CDi;
	Di = CDi + 4;

	// Calculating C0
	k = 0;
	m = 0;
	for(i = 0; i < 4; i ++)
	{
		for(j = 0; j < 7; j ++)
		{
			loc = C0table[i * 7 + j] - 1;
			getBit(InitKey, &bit, loc);
			setBit(C0, bit, i * 7 + j);
		}
		
	}

	//Calculating D0
	k = 0;
	m = 0;
	for(i = 0; i < 4; i ++)
	{
		for(j = 0; j < 7; j ++)
		{
			loc = D0table[i * 7 + j] - 1;
			getBit(InitKey, &bit, loc);
			setBit(D0, bit, i * 7 + j);
		}
		
	}
	
	for( turn = 0 ; turn < 16 ; turn ++)
	{
		ShiftBit(Ci, C0, 48, ShiftBittable[turn]);
		ShiftBit(Di, D0, 48, ShiftBittable[turn]);
		SelKey(CDi, (uint8_t *)(&Keys[turn]));
 		memcpy(C0, Ci, 4);
		memcpy(D0, Di, 4);
	}

	memcpy(thisKey, Keys, sizeof(Keys));
}

