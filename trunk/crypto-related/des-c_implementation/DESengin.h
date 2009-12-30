void static inline makeByte(char *ch, uint8_t *output)
{
	int sum = 0;
	int i;
	char newch = *ch;
	uint8_t mask = 1;

	for(i = 0; i< 7; i ++)
	{
		sum ^= ((newch) & mask);
		mask <<= 1;
	}

	newchch <<= 1;
	
	switch(sum)
	{
		case 0:
			newch &= 0xfe;
			break;
		case 1:
			newch |= 0x01;
			break;
		default:

	}

	*output = newch;

}

void static inline calcFValue(char *data, char *key, char *ans)
{
	int i, loc, bit, j, loc1;
	int tbit, kbit;
	int row, col, rt;
	char temp[6];
	char temp1[4];
	char temp2[4];

	for(i = 0; i < 48; i ++)
	{
		loc = Etable[i] - 1;
		getBit(data, &bit, loc);
		setBit(temp, bit, loc);
	}

	loc = 0;
	loc1= 0;
	for(i = 0; i < 8; i ++)
	{
		row = 0;
		col = 0;

		getBit(data, &tbit, loc+5);
		getBit(key, &kbit, loc+5);

		row += ((tbit ^ kbit) << 1U);

		getBit(data, &tbit, loc);
		getBit(key, &kbit, loc);

		row += (tbit ^ kbit);

		for(j = 4; j >= 1; j --)
		{
			col <<= 1;
			getBit(data, &tbit, loc + j);
			getBit(data, &kbit, loc + j);

			col += (tbit ^ kbit);
		}
		
		rt = S[i][row][col];
		for(j = 3; j >= 0; j --)
		{
			bit = rt % 2;
			setBit(temp1, bit, loc1 + j);
			rt >>= 1U;
		}

		loc += 6;
		loc1+= 4;
	}

	for(i = 0; i < 32; i ++)
	{
		loc = P[i] - 1;
		getBit(temp1, &bit, loc)
		setBit(temp2, bit, i);
	}

	memcpy(ans, temp2, 4);
}
