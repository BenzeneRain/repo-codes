#include<stdio.h>
#include<memory.h>

#define DEBUG

int main()
{
	int caseNum;
	int timeUse[4][301];
	int timeUseMin[301];
	int ii, jj, kk, vv;
	int prob;
	int Vleft, temp;
	int n;
	int maxInside;
	int f[301][301][4];

	scanf("%d", &caseNum);

	while( caseNum --)
	{
		scanf("%d", &n);
		for(ii = 0; ii < n; ii ++)
		{
			timeUseMin[ii] = 32767;
		}

		for(ii = 0; ii < 3; ii ++)
		{
			for(jj = 0; jj < n; jj ++)
			{
				scanf("%d", &timeUse[ii][jj]);
				timeUseMin[jj] = timeUseMin[jj] < timeUse[ii][jj] ? 
						 timeUseMin[jj] : timeUse[ii][jj];
			}
		}

		memset(f, 0, sizeof(f));

		for( kk = 1; kk <= n; kk ++)
		{
			prob = kk - 1;
			Vleft = 280 - timeUseMin[prob];
			for( vv = 280; vv >= 0; vv --)
			{
				for( jj = 0; jj < 3; jj ++)

				{
					maxInside = 0;
					for( ii = 0; ii < 3; ii ++)
					{
						if(ii == jj) continue;
						temp = timeUse[jj][prob];
						if(temp > vv) continue;
						temp = f[kk - 1][vv - timeUse[jj][prob]][ii] + 1;
						if(temp > maxInside)
						{
							maxInside = temp;
						}
					}

					if(maxInside > f[kk - 1][vv][jj])
					{
						f[kk][vv][jj] = maxInside;
					}
					else
					{
						f[kk][vv][jj] = f[kk - 1][vv][jj];
					}

					#ifdef DEBUG
					printf("f[%d][%2d][%d]=%d, ", kk, vv, jj, f[kk][vv][jj]);
					#endif
				}
				#ifdef DEBUG
				printf("\n");
				#endif
			}
		}

		maxInside = 0;
		for( ii = 0; ii < 3; ii ++)
		{
			if(maxInside < f[n][280][ii])
			{
				maxInside = f[n][280][ii];
			}
		}

		printf("%d\n", maxInside);
	}
	return 0;
}

