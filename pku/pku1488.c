#include<stdio.h>
#include<string.h>

int flag;
char now;

int main()
{
	flag=0;
	while(scanf("%c",&now)!=EOF)
	{
		if(now=='"' && flag==0)
		{
			printf("``");
			flag=1;
		}
		else if(now=='"' && flag==1)
		{
			printf("''");
			flag=0;
		}
		else printf("%c",now);
	}
	return 0;
}
