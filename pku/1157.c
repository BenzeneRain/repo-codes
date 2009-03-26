#include <stdio.h>
#include <memory.h>

int val[105][105];
int ans[105];

int main()
{
	int f, v;
	int i, j;
	
	while(scanf("%d%d", &f, &v) != EOF)
	{
		memset(ans, 0, sizeof(ans));

		for(i = 0; i < f; i ++)
			for(j = 0; j < v; j ++)
			{
				scanf("%d", &val[i][j]);
			}

		for(i = 1; i <= v; i ++)
			if(i == 1)
				ans[i] = val[0][0];
			else
				ans[i] = ans[i - 1] > val[0][i - 1] ? 
					 ans[i - 1] : val[0][i - 1];

		for(i = 1; i < f; i ++)
			for(j = v; j >= 1; j --)
				ans[j] = ans[j] > (ans[j - 1] + val[i][j - 1]) ?
					 ans[j] : (ans[j - 1] + val[i][j - 1]);

		printf("%d\n", ans[v]);
	}
	return 0;
}
