#include <stdio.h>
#include <memory.h>
#include <math.h>

unsigned long l[100005];
unsigned long f[100005];
unsigned long b[100005];

int main()
{
	unsigned long ii;
	unsigned long n;
	unsigned long st, end, m;
	unsigned long len;
	
	while(scanf("%ld", &n) != EOF)
	{
		memset(b, 0, sizeof(b));
		for(ii = 0; ii < n; ii ++)
		{
			scanf("%ld", &l[ii]);
			f[ii] = 0;
		}
		f[0] = 1;
		b[1] = l[0];
		len = 1;
		for(ii = 1; ii < n; ii ++)
		{
			if(l[ii] > b[len]) b[ ++ len] = l[ii];
			else
			{
				if(l[ii] < b[1])
				{
					b[1] = l[ii];
					continue;
				}
				st = 1;
				end = len;
				while(st < end)
				{
					m = (st + end) / 2;
					if(l[ii] > b[m])
						st = m + 1;
					else
						end = m;
				}
				b[st] = l[ii];
			}
		}
		printf("%ld\n", len);
	}
	return 0;
}
