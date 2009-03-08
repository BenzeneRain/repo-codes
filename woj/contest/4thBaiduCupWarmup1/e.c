#include <stdio.h>
#include <string.h>

#define ENDMARK "END"
#define BUYMARK "buy"
#define SELLMARK "sell"

int main()
{
	char stockname[30];
	char username[1005][30];
	char temp[5];
	double info[1005];
	int type[1005];
	int n;
	int ii, jj;
	int flag;

	while(1)
	{
		scanf("%d %s", &n, stockname);
		if((n == 0) && (!strcmp(stockname, ENDMARK)))
			break;

		memset(username, 0, sizeof(username));
		memset(info, 0, sizeof(info));
		for(ii = 0; ii < n; ii ++)
		{
			memset(temp, 0, sizeof(temp));
			scanf("%s %s %f", username[ii], temp, &info[ii]);
			if( !strcmp(BUYMARK, temp))
			{
				type[ii] = 0;         //buy
			}
			else
			{
				type[ii] = 1;         //sell
			}
		}

		printf("%s\n", stockname);
		for(ii = 0; ii < n; ii ++)
		{
			printf("%s:", username[ii]);
			flag = 0;
			for(jj = 0; jj < n; jj ++)
			{
				if(ii == jj) continue;
				if(type[ii] == 0 && type[jj] == 1 && info[ii] >= info[jj])
				{
					printf(" %s", username[jj]);
					flag = 1;
				}
				else if( type[ii] == 1 && type[jj] == 0 && info[ii] <= info[jj])
				{
					printf(" %s", username[jj]);
					flag = 1;
				}
			}
			if(flag)
				printf("\n");
			else
				printf(" NO-ONE\n");
		}


	}

	return 0;
}
