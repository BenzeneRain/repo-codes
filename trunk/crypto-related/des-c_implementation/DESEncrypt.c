/*
 * Usage: ./DESEngin e|d input_filename output_filename key
 *
 * e: encrypt
 * d: decrypt
 */

#include <stdio.h>
#include <string.h>
#include <DESKeyGen.h>
#include <DESengin.h>

void initKey(char *, uint64_t *);
void encrypt(uint8_t *, uint8_t *, uint8_t *);
void decrypt(uint8_t *, uint8_t *, uint8_t *);
void work(char *, char *, uint8_t *[], int);


int main(int argc, char *argv[])
{
	uint64_t ValidKey;
	uint8_t Keys[16][6];

	if(argc != 5)
	{
		printf("Usage: ./DESengin e|d input_filename output_filename key\ne: encrypt\nd: decrypt\n");
		exit(0);
	}

	init(argv[4], &ValidKey);
	Keys = DESKeyGen(&ValidKey);


	
	return 0;
}

void initKey(char *OrgKey, uint64_t *ValidKey)
{
	char *padstr = "W.ZHANG";
	char NewKey[8];

	int length;
	int i, j, k;

	length = strlen(OrgKey);
	k = 0;
	for(i = 0; i < 7; i ++)
	{
		if(i > length)
		{
			makeByte(padstr + k, NewKey + i);
			k ++;
		}
		else
		{
			makeByte(OrgKey + i, NewKey + i);	
		}
	}

	memcpy(ValidKey, (uint64_t *)NewKey, 8);
}

void work(char *inputfilename, char *outputfilename, uint8_t *key[], int mode)
{
	FILE *fin, *fout;

	fin = fopen(inputfilename, "r");
	fout = fopen(outputfilename, "w");


}

void encrypt(uint8_t *data, uint8_t *key, uint8_t *ans)
{
	int i, j, loc;
	int bit, bit1, bit2;
	char LR0[8];
	char *L0
	char *R0;
	char LRi[8],LRi1;
	char *Li, *Li1;
	char *Ri, *Ri1;
	char temp[8];

	L0 = LR0;
	R0 = LR0 + 4;
	Li = LRi;
	Ri = LRi + 4;
	Li1 = LRi1;
	Ri1 = LRi1 + 4;

	for(i = 0; i < 64; i ++)
	{
		getBit(data, &bit, IPTable[i] - 1);
		setBit(LR0, bit, i);
	}

	memcpy(LRi, LR0, 8);
	for(i = 0; i < 16; i ++)
	{
		if( i == 15)
		{
			memcpy(Ri1, Ri, 4);
		}
		else
		{
			memcpy(Li1, Ri, 4);
		}
		calcFValue(Ri, key + i, temp);
		for(j = 0; j < 32; j ++)
		{
			getBit(Li, &bit1, j);
			getBit(temp, &bit2, j);
			bit = bit1 ^ bit2;
			if( i== 15)
			{
				setBit(Li1, bit, j);
			}
			else
			{
				setBit(Ri1, bit, j);
			}
		}
		memcpy(LRi, LRi1, 8);
	}

	for(i = 0; i < 64; i ++)
	{
		loc = RIPtable[i];
		getBit(LRi, &bit, loc);
		setBit(LRi1, bit, loc);
	}

	memcpy(ans, LRi1, 8);
}

void decrypt(uint8_t *data, uint8_t *key[6], uint8_t *ans)
{
	int i, j, loc;
	int bit, bit1, bit2;
	char LR0[8];
	char *L0
	char *R0;
	char LRi[8],LRi1;
	char *Li, *Li1;
	char *Ri, *Ri1;
	char temp[8];

	L0 = LR0;
	R0 = LR0 + 4;
	Li = LRi;
	Ri = LRi + 4;
	Li1 = LRi1;
	Ri1 = LRi1 + 4;

	for(i = 0; i < 64; i ++)
	{
		getBit(data, &bit, IPTable[i] - 1);
		setBit(LR0, bit, i);
	}

	memcpy(LRi, LR0, 8);
	for(i = 15; i >= 0; i --)
	{
		if( i == 0)
		{
			memcpy(Ri1, Ri, 4);
		}
		else
		{
			memcpy(Li1, Ri, 4);
		}
		calcFValue(Ri, key + i, temp);
		for(j = 0; j < 32; j ++)
		{
			getBit(Li, &bit1, j);
			getBit(temp, &bit2, j);
			bit = bit1 ^ bit2;
			if( i == 0)
			{
				setBit(Li1, bit, j);
			}
			else
			{
				setBit(Ri1, bit, j);
			}
		}
		memcpy(LRi, LRi1, 8);
	}

	for(i = 0; i < 64; i ++)
	{
		loc = RIPtable[i];
		getBit(LRi, &bit, loc);
		setBit(LRi1, bit, loc);
	}

	memcpy(ans, LRi1, 8);
}
