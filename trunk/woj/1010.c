#include <stdio.h>

int main()
{
	int n;
	int i;
	int maxnum;
 	long int ans;
	int shift, last;
	int data[1001];

	scanf("%d", &n);
	while( n != 0)
	{
		scanf("%d", &data[0]);
		maxnum = data[0];
		for(i = 1; i < n; i ++)
		{
			scanf("%d", &data[i]);
			if(data[i] > maxnum)
				maxnum = data[i];
		}

		maxnum %= 2006;
		shift   = (n - 1) / 11;
		last    = (n - 1) % 11; 
		ans = 1;
		for(i = 0; i < shift; i ++)
		{
			ans <<= 11;
			ans  %= 2006;
		}

		ans <<= last;
		ans  %= 2006;

		ans = (ans * maxnum) % 2006;
		if (ans < 0) ans += 2006;

		printf("%d\n", ans);

		scanf("%d", &n);
	}
	return 0;
}
