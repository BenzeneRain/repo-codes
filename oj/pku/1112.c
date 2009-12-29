#include <stdio.h>

#define MAX 10000

int main()
{
	int pn;
	int disvec[105][105] = {{0}};
	int maxdist[105] = {0};
	int count[105] = {0};
	int cn;
	int dist;
	int i, j, k;
	int min;
	int loc;

	do
	{
		scanf("%d", &pn);
		if(pn == 0)
		{
			break;
		}

		for(i = 0; i < pn; i ++)
		{
			for(j = 0; j < pn; j ++)
			{
				disvec[i][j] = MAX;
			}
			maxdist[i] = -1;
			//disvec[i][i] = 0;
			count[i] = 0;
		}

		for(i = 0; i < pn; i ++)
		{
			scanf("%d", &cn);
			count[i] = cn;
			for(j = 0; j < cn; j ++)
			{
				scanf("%d%d", &k, &dist);
				disvec[i][k - 1] = dist;
			}
		}

		for(k = 0; k < pn; k ++)
			for(i = 0; i < pn; i ++)
				for(j = 0; j < pn; j ++)
				{
					if((i != j) && 
					   ((disvec[i][k] + disvec[k][j]) < disvec[i][j]))
					{
						if(disvec[i][j] == MAX)
						{	
							count[i] ++;
						}

						disvec[i][j] = disvec[i][k] + disvec[k][j];
					}
				}


		for(i = 0; i < pn; i++)
		{
			if(count[i] != (pn - 1))
			{
				continue;
			}
			else
			{
				for(j = 0; j < pn; j ++)
				{
					maxdist[i] = (i != j) && (disvec[i][j] > maxdist[i]) ? disvec[i][j] : maxdist[i];
				}
			}
		}
		min = MAX; 
		loc = 0;
		for(i = 0; i < pn; i ++)
		{
			if((count[i] == (pn - 1)) && (min > maxdist[i]))
			{
				min = maxdist[i];
				loc = i;
			}
		}

		if(min == MAX)
		{
			printf("disjoint\n");
		}
		else
		{
			printf("%d %d\n",loc+1, min);
		}

	}while(pn != 0);

	return 0;
}
