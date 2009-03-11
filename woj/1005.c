#include <stdio.h>
#include <memory.h>

long f[100005];
int size[105];
int value[105];
int n;
long totalsize;
int minsize;

void qsort(int, int);

int main()
{
	int i;
	long j;
	while(scanf("%d", &n) != EOF)
	{
		memset(f, 0, sizeof(f));
		
		for(i = 0; i < n; i ++)
		{
			scanf("%d%d", &size[i], &value[i]);
			if(i == 0) 
			{
				minsize = size[0];
			}
			else if(size[i] < minsize)
			{
				minsize = size[i];
			}
		}
		scanf("%ld", &totalsize);

		qsort(0, n - 1);
		for(i = 0; i < n; i ++)
		{
			
			for(j = totalsize; j >= size[i]; j --)
			{
				f[j] = f[j] > (f[j - size[i]] + value[i]) ?
				       f[j] :  f[j - size[i]] + value[i];
			}
		}

		printf("%ld\n", f[totalsize]);
	}
	return 0;	
}


void qsort(int st, int end)
{
	int ii, jj;
	int tmpSize, tmpVal;

	ii = st;
	jj = end;
	tmpSize = size[ii];
	tmpVal = value[ii];
	while(ii < jj)
	{
		while( (ii < jj) && size[ii] <= size[jj]) jj --;
		if( ii < jj)
		{
			size[ii] = size[jj];
			value[ii] = value[jj];
			ii ++;
		}
		while( (ii < jj) && size[ii] <= size[jj]) ii ++;
		if( ii < jj)
		{
			size[jj] = size[ii];
			value[jj] =value[ii];
			jj --;
		}
	}

	size[ii] = tmpSize;
	value[ii] = tmpVal;

	if(st < (ii - 1))qsort(st, ii - 1);
	if(end > (jj + 1))qsort(jj + 1, end);
}
