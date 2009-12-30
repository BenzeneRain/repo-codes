/*
 * Usage: ./DESEngin e|d input_filename output_filename key
 *
 * e: encrypt
 * d: decrypt
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <fcntl.h>
#include "DESengine.h"

void initKey(char *, uint8_t *);
void encrypt(uint8_t *, uint8_t [][6], uint8_t *);
void decrypt(uint8_t *, uint8_t [][6], uint8_t *);
void work(char *, char *, uint8_t [][6], int);

int errno;

int main(int argc, char *argv[])
{
	uint8_t ValidKey[8];
	uint8_t Keys[16][6];
	int mode;

	if(argc != 5)
	{
		printf("Usage: ./DESengin e|d input_filename output_filename key\ne: encrypt\nd: decrypt\n");
		exit(0);
	}

	initKey(argv[4], ValidKey);
	DESKeyGen(ValidKey, Keys);

	if(!strcmp(argv[1], "e"))
	{
		mode = 0;
	}
	else if(!strcmp(argv[1], "d"))
	{
		mode = 1;
	}
	else
	{
		printf("Invalid work mode!\n");
		exit(0);
	}
	
	work(argv[2], argv[3], Keys, mode);
	return 0;
}

void initKey(char *OrgKey, uint8_t *ValidKey)
{
	uint8_t *padstr = "W.ZHANG";
	uint8_t NewKey[8];

	int length;
	int i, j, k;

	length = strlen(OrgKey);
	k = 0;
	for(i = 0; i < 8; i ++)
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

	memcpy(ValidKey, NewKey, 8);
}

void work(char *inputfilename, char *outputfilename, uint8_t key[][6], int mode)
{
	int fin, fout;
	char *Z = "1jr8if0,";
	uint8_t buffer[8]     = {0};
	uint8_t pbuffer[8]    = {0};
	uint8_t pcrybuffer[8] = {0};
	uint8_t lastbuffer[8] = {0};
	uint8_t decbuffer[8]  = {0};
	uint8_t temp[8]       = {0};
	int ret;
	int i, j, k;
	int bit, bit1, bit2, bit3;

	fin = open(inputfilename, O_RDONLY, NULL);
	fout = open(outputfilename, O_CREAT | O_WRONLY | O_TRUNC, 0644);

	memset(lastbuffer, 0, sizeof(lastbuffer));
	i = 0;
	if(mode == 0)  //Encrypt
	{
		ret = read(fin, buffer, 8);
		do
		{

			if(ret < 8)
			{
				for(j = ret; j < 8; j ++)
				{
					buffer[j] = 0x0;
				}
			}

			if(i == 0)
			{
				for(j = 0; j < 64; j ++)
				{
					getBit(buffer, &bit1, j);
					getBit(Z, &bit2, j);
					bit = bit1 ^ bit2;
					setBit(temp, bit, j);			
				}
			}
			else
			{
				for(j = 0; j < 64; j ++)
				{
					getBit(buffer, &bit1, j);
					getBit(pbuffer, &bit2, j);
					getBit(pcrybuffer, &bit3, j);
					bit = bit1 ^ bit2 ^ bit3;
					setBit(temp, bit, j);
				}		
			}	

			encrypt(temp, key, pcrybuffer);
			memcpy(pbuffer, buffer, 8);
			write(fout, pcrybuffer, 8);
			i ++;
			if(ret < 8)
				break;
			ret = read(fin, buffer, 8);
		}while(1);

		//deal with the last block
		j = 63;
		memset(lastbuffer, 0, sizeof(lastbuffer));
		while(ret != 0)
		{
			if(ret % 2 == 0)
			{
				setBit(lastbuffer, 0, j);
			}
			else
			{
				setBit(lastbuffer, 1, j);
			}
			j --;
			ret >>= 1;
		}

		k = 0;
		j = 63;
		while(j > k)
		{
			getBit(lastbuffer, &bit, j);
			setBit(lastbuffer, bit, k);
			setBit(lastbuffer, 0, j);
			j --;
			k ++;
		}

		for(j = 0; j < 64; j ++)
		{
			getBit(lastbuffer, &bit1, j);
			getBit(pbuffer, &bit2, j);
			getBit(pcrybuffer, &bit3, j);
			bit = bit1 ^ bit2 ^ bit3;
			setBit(temp, bit, j);

		}
		encrypt(temp, key, pcrybuffer);
		write(fout, pcrybuffer, 8);
	}	
	else  //Decrypt
	{
		ret = read(fin, buffer, 8);
		do
		{
			decrypt(buffer, key, decbuffer);
			if(i == 0)
			{
				for(j = 0; j < 64; j ++)
				{
					getBit(decbuffer, &bit1, j);
					getBit(Z, &bit2, j);
					bit= bit1 ^ bit2;
					setBit(decbuffer, bit, j);
				}
			}
			else
			{
				for(j = 0; j < 64; j ++)
				{
					getBit(decbuffer, &bit1, j);
					getBit(pbuffer, &bit2, j);
					getBit(pcrybuffer, &bit3, j);
					bit = bit1 ^ bit2 ^ bit3;
					setBit(decbuffer, bit, j);
				}
			}

			memcpy(pbuffer, buffer, 8);

			ret = read(fin, buffer, 8);
			if(ret < 8)
			{
				if( i != 0)
				{
					break;
				}
				else
				{

					printf("Invalid input data!\n");
					close(fin);
					close(fout);
					return;
				}
			}
			else
			{
				if(i != 0)
				{
					write(fout, pcrybuffer, 8);
				}
				memcpy(pcrybuffer, decbuffer, 8);
			}
			
			i ++;
		}while(1);

		k = 0;
		for(i = 63; i >= 0; i --)
		{
			k <<= 1;
			getBit(decbuffer, &bit, i);
			k = k + bit;
		}

		write(fout, pcrybuffer, k);
	}
	
	close(fin);
	close(fout);
}

void encrypt(uint8_t *data, uint8_t key[][6], uint8_t *ans)
{
	int i, j, loc;
	int bit, bit1, bit2;
	uint8_t LR0[8];
	uint8_t *L0;
	uint8_t *R0;
	uint8_t LRi[8], LRi1[8];
	uint8_t *Li, *Li1;
	uint8_t *Ri, *Ri1;
	uint8_t temp[8];

	L0 = LR0;
	R0 = LR0 + 4;
	Li = LRi;
	Ri = LRi + 4;
	Li1 = LRi1;
	Ri1 = LRi1 + 4;

	for(i = 0; i < 64; i ++)
	{
		getBit(data, &bit, IPtable[i] - 1);
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
		calcFValue(Ri, key[i], temp);
		for(j = 0; j < 32; j ++)
		{
			getBit(Li, &bit1, j);
			getBit(temp, &bit2, j);
			bit = bit1 ^ bit2;
			if(i == 15)
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
		loc = RIPtable[i] - 1;
		getBit(LRi, &bit, loc);
		setBit(LRi1, bit, i);
	}

	memcpy(ans, LRi1, 8);
}

void decrypt(uint8_t *data, uint8_t key[][6], uint8_t *ans)
{
	int i, j, loc;
	int bit, bit1, bit2;
	uint8_t LR0[8];
	uint8_t *L0;
	uint8_t *R0;
	uint8_t LRi[8],LRi1[8];
	uint8_t *Li, *Li1;
	uint8_t *Ri, *Ri1;
	uint8_t temp[8];

	L0 = LR0;
	R0 = LR0 + 4;
	Li = LRi;
	Ri = LRi + 4;
	Li1 = LRi1;
	Ri1 = LRi1 + 4;

	for(i = 0; i < 64; i ++)
	{
		getBit(data, &bit, IPtable[i] - 1);
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
		calcFValue(Ri, key[i], temp);
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
		loc = RIPtable[i] - 1;
		getBit(LRi, &bit, loc);
		setBit(LRi1, bit, i);
	}

	memcpy(ans, LRi1, 8);
}
