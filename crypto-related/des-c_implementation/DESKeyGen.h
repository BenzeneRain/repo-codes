#include <stdint.h>
#include <math.h>

void DESKeyGen(uint8_t *, uint8_t *[]);

const uint8_t ShiftBittable[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

const uint8_t C0table[28] = {57,49,41,33,25,17,9,
                             1,58,50,42,34,26,18,
                             10,2,59,51,43,35,27,
                             19,11,3,60,52,44,36};

const uint8_t D0table[28] = {63,55,47,39,31,23,15,
                             7,62,54,46,38,30,22,
                             14,6,61,53,45,37,29,
                             21,13,5,28,20,12,4};

const uint8_t CDSeltable[48] = {14,17,11,24,1,5,
                                3,28,15,6,21,10,
                                23,19,12,4,26,8,
                                16,7,27,20,13,2,
                                41,52,31,37,47,55,
                                30,40,51,45,33,48,
                                44,49,39,56,34,53,
                                46,42,50,36,29,32};


#ifdef _DES_KEY_GEN_
static inline void setBit(uint8_t *dst, int bit, int loc)
{
	int i, j;
	uint8_t mask;
		
	i = floor(loc / 8);
	j = loc % 8;
	
	switch(bit)
	{
		case 0:
			mask    = ~(1U << j);
			dst[i] &= mask;
			break;

		case 1:
			mask    = 1U << j;
			dst[i] |= mask;
			break;

		default:
			break;
	}
}

static inline void getBit(uint8_t *src, int *bit, int loc)
{
	int i, j;
	uint8_t mask;

	i = floor(loc / 8);
	j = loc % 8;

	mask = 1U << j;
	*bit = (src[i] & mask) >> j;
}
#endif

static inline void SelKey(uint8_t *CD, uint8_t *key)
{
	int i, loc, bit;
	
	for(i = 0; i < 48; i ++)
	{
		loc = CDSeltable[i] - 1;
		if(loc > 27)
		{
			loc += 4;
		}
		getBit(CD, &bit, loc);
		setBit(key, bit, i);	
	}

}

static inline void ShiftBit(uint8_t *dst, uint8_t *src, int length, int shift)
{
	int i, j, m, n;

	m = length - shift;

	for(i = 0; i < m; i ++)
	{
		getBit(src, &n, i + shift);
		setBit(dst, n, i);
	}

	j = 0;
	for(i = m; i < length; i ++)
	{
		getBit(src, &n, j);
		setBit(dst, n, i);
		j ++;
	}
}
