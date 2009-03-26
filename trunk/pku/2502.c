#include <stdio.h>
#include <math.h>

#define inf 1000000000
typedef double elem_t;

typedef struct
{
	double x,y;
}cood_t;

int cmp(double x, double y)
{
	if(fabs(x - y) < 1e-9)
		return 0;
	else if(x - y > 0)
		return 1;
	else
		return -1;
}

double calcdist(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void dijkstra(int n, elem_t mat[][205], int s, elem_t *min)
{
	int v[205], i, j, k;
	for(i = 0; i < n; i ++)
	{
		min[i] = inf, v[i] = 0;
	}

	for(min[s] = 0, j = 0; j < n; j ++)
	{
		for(k = -1, i = 0; i < n; i ++)
			if(!v[i] && (k == -1 || min[i] < min[k]))
				k = i;
		for(v[k] = 1, i = 0; i < n; i ++)
			if(!v[i] && min[k] + mat[k][i] < min[i])
				min[i] = min[k] + mat[k][i];
	}
}

int main()
{
	cood_t loc[205];
	double dis[205][205];
	int kind[205][205] = {{0}};
	double min[205];
	int i,j;
	int node_n;
	cood_t tmp;

	for(i = 0; i < 2; i ++)
	{
		scanf("%lf%lf", &loc[i].x, &loc[i].y);
	}

	while(scanf("%lf%lf", &tmp.x, &tmp.y) != EOF)
	{
		loc[i].x = tmp.x;
		loc[i].y = tmp.y;
		i ++;

		do
		{
			scanf("%lf%lf", &tmp.x, &tmp.y);
			if((tmp.x == -1) && (tmp.y == -1))
				break;

			loc[i].x = tmp.x;
			loc[i].y = tmp.y;

			kind[i][i - 1] = 1;
			kind[i - 1][i] = 1;
			i ++;
		}while(1);
	}

	node_n = i;

	for(i = 0; i < node_n; i ++ )
		for(j = i; j < node_n; j ++)
		{
			if(kind[i][j] == 1)
			{
				dis[i][j] = calcdist(loc[i].x, loc[i].y, loc[j].x, loc[j].y) / 40;
				dis[j][i] = dis[i][j];
			}
			else
			{
				dis[i][j] = calcdist(loc[i].x, loc[i].y, loc[j].x, loc[j].y) / 10;
				dis[j][i] = dis[i][j];
			}
		}

	dijkstra(node_n, dis, 0, min);
	printf("%.0lf\n", min[1] * 3 / 50);

	return 0;
}
