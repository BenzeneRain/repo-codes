#include <stdio.h>
#include <math.h>

#define MAX 10000

typedef struct
{
	double x,y;
}cood_t;

int cmp(double x, double y)
{
	if(fabs(x - y) < 1e-9)
		return 0;
	if(x - y > 0) 
		return 1;
	return -1;
}

int main()
{
	int stoneNum;
	double dist[205][205];
	cood_t loc[205];
	int i, j, k;
	int tcase = 0;

	do
	{
		scanf("%d", &stoneNum);
		if(stoneNum == 0)
		{
			break;
		}

		for(i = 0; i < stoneNum; i ++)
		{
			scanf("%lf%lf", &(loc[i].x), &(loc[i].y));
		}

		for(i = 0; i < stoneNum; i ++)
			for(j = i; j < stoneNum; j ++)
			{
				dist[i][j] = sqrt((loc[i].x - loc[j].x) * (loc[i].x - loc[j].x) + 
				                  (loc[i].y - loc[j].y) * (loc[i].y - loc[j].y));
				dist[j][i] = dist[i][j];
			}

		for(k = 0; k < stoneNum; k ++)
			for(i = 0; i < stoneNum; i ++)
				for(j = 0; j < stoneNum; j ++)
					if((cmp(dist[i][j], dist[i][k]) == 1) && (cmp(dist[i][j], dist[k][j]) == 1))
					{
						dist[i][j] = cmp(dist[i][k], dist[k][j]) == 1 ? dist[i][k] : dist[k][j];
						dist[j][i] = dist[i][j];
					}

		printf("Scenario #%d\n", tcase + 1);
		printf("Frog Distance = %.3lf\n", dist[0][1]);
		printf("\n");
		tcase ++;
	}while(1);

	return 0;
}
