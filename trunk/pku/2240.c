#include <stdio.h>
#include <string.h>
#include <math.h>

int find(char dir[][200], int n, char *item)
{
	int i;

	for(i = 0; i < n; i ++)
	{
		if(!strcmp(dir[i], item))
			return i;
	}
	return -1;
}

int cmp(double x, double y)
{
	if(fabs(x - y) < 1e-9)
		return 0;
	else if((x - y) > 0)
		return 1;
	else
		return -1;
}

int main()
{
	int currN;
	int exchN;
	char currName[35][200];
	double exch[35][35];
	char curr1[200], curr2[200];
	int i, j, k;
	double rate, tmp;
	int possible;
	int turn = 1;

	do
	{
		scanf("%d", &currN);
		if(currN == 0)
			break;
		
		memset(currName, 0, sizeof(currName));
		for(i = 0; i< currN; i ++)
		{
			scanf("%s", currName[i]);
		}

		scanf("%d", &exchN);
		memset(exch, 0, sizeof(exch));

		for(i = 0; i < exchN; i ++)
		{
			memset(curr1, 0, sizeof(curr1));
			memset(curr2, 0, sizeof(curr2));

			scanf("%s", curr1);
			scanf("%lf", &rate);
			scanf("%s", curr2);
			
			j = find(currName, currN, curr1);
			k = find(currName, currN, curr2);

			exch[j][k] = rate;
		}

		for(k = 0; k < currN; k ++)
			for(i = 0; i < currN; i ++)
				for(j = 0; j < currN; j ++)
				{
					tmp = exch[i][k] * exch[k][j];
					if(cmp(exch[i][j], tmp) == -1)
					{
						exch[i][j] = tmp;
					}
				}
		
		possible = 0;
		for(i = 0; i < currN; i ++)
			if(cmp(exch[i][i], 1) == 1)
			{
				possible = 1;
				break;
			}
		
		if(possible == 1)
		{
			printf("Case %d: Yes\n", turn ++);
		}
		else
		{
			printf("Case %d: No\n", turn ++);
		}
	}while(1);

	return 0;
}
