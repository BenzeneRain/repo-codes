#include <stdio.h>
#include <memory.h>

int casenum;
unsigned long data[1005];
int cnum;

unsigned long calclcd(unsigned long, unsigned long);

int main()
{
	unsigned long temp,sum,diff;
	int ii, jj;
	unsigned long lcd;
	int flag;

	scanf("%d", &casenum);

	while(casenum --)
	{	
		memset(data, 0 ,sizeof(data));
		scanf("%d", &cnum);
		for(ii = 0; ii < cnum; ii ++)
		{
			sum = 0;
			for( jj = 0; jj < 9; jj ++)
			{
				scanf("%ld", &temp);
				sum += temp;
			}
			scanf("%ld", &temp);

			diff = sum > temp ? sum - temp : temp - sum;
			data[ii] = diff;
		}

		lcd = calclcd(data[0], data[1]);
		for( ii = 2; ii < cnum; ii ++)
		{
			if(lcd <= 1) break;
			if(data[ii] == 0)
			{
				lcd = 0;
			}
			else
			{
				lcd = calclcd(data[ii], lcd);
			}
		}

		if(lcd > 1)
		{
			flag = 1;
			for( ii = 0; ii < cnum; ii ++)
			{
				if(data[ii] != lcd)
				{
					flag = 0;
					break;
				}
			}
			if(flag)lcd = 0;
		}

		if(lcd <= 1)
		{
			printf("impossible\n");
		}
		else
		{
			printf("%ld\n", lcd);
		}
		
	}
	return 0;
}

unsigned long calclcd(unsigned long a, unsigned long b)
{
	unsigned long aa, bb;

	if( a >= b)
	{
		aa = a;
		bb = b;
	}
	else
	{
		aa = b;
		bb = a;
	}
	if (bb == 0) 
	{
		return aa;
	}
	else
	{
		return calclcd(bb, aa % bb);
	}

}
