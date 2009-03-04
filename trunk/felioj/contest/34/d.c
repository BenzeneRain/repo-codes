#include <stdio.h>
#include <memory.h>

int casenum;
int n,m;
int skip[1025];
int ans;

int divcnt(int, int, int *);

int main()
{

	int ii;
	int temp;
	int wo;

	scanf("%d", &casenum);
	while(casenum --)
	{
		scanf("%d %d", &n, &m);
		n = 1<<n;
		
		memset(skip, 0, sizeof(skip));
		for(ii = 0; ii < m; ii ++)
		{
			scanf("%d", &temp);
			skip[temp - 1] = 1;
		}

		wo = 0;
		ans = divcnt(0, n - 1, &wo);
		printf("%d\n", wo);
	}
	return 0;
}

int divcnt(int left, int right, int *wo)
{
	int subcountl, subcountr;
	int mid;

	if(right == (left + 1) )
	{
		if( (!skip[right]) && (!skip[left]))
			return 1;
		else if( !(skip[right] && skip[left]))
		{
			*wo = *wo + 1;
			return 1;
		}
		else
			return 0;
	}
	else
	{
		mid = ((right - left + 1) / 2) + left;
		subcountl = divcnt(left, mid - 1, wo);
		subcountr = divcnt(mid, right, wo);

		if( (subcountl == 1) && (subcountr == 1))
		{
			return 1;
		}
		else if((subcountl == 1 && subcountr == 0) || ( subcountl == 0 && subcountr == 1))
		{
			*wo = *wo + 1;
			return 1;
		}
		else if((subcountl == 0) && (subcountr == 0))
		{
			return 0;
		}
		else
		{
			printf("Error!\n");
			return -1;
		}
	}
}
