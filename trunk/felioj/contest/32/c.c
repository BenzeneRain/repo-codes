#include <stdio.h>
#include <string.h>

const char InputEnd[]="#";
const char Mark='?';

char * readstr(char *);
unsigned long long solve(char *, char *, int);

int main()
{
	char wild[12],number[12];
	unsigned long long result;
	

	result = 0;
	while(readstr(wild)!=NULL)
	{
		readstr(number);
		result = solve(wild, number, strlen(wild));
		printf("%lld\n", result);
	}
	
	return 0;
}

char *readstr(char * src)
{
	scanf("%s", src);
	if(!strcmp(src,InputEnd))
	{
		return NULL;
	}
	else
	{
		return src;
	}
}

unsigned long long solve(char *wild, char *number, int len)
{
	char *cwild, *cnumber;
	int ii;
	unsigned long long MarkNum;
	int choice;

	if(len == 0)
	{
		return 0;
	}
	else
	{

	}

	cwild   = wild;
	cnumber = number;

	if(*cwild != Mark)
	{
		if(*cwild < *cnumber)
		{
			return 0;
		}
		else
		{
		}

		if(*cwild > *cnumber)
		{
			MarkNum = 1;
			while(*cwild)
			{
				if( *cwild == Mark)
				{
					MarkNum *= 10;
				}
				else
				{

				}

				cwild ++;
			}
			return MarkNum;
		}
		else
		{
		}

		if(*cwild == *cnumber)
		{
			if(len > 1)
			{	
				cwild ++;
				cnumber ++;
				return solve(cwild, cnumber, len-1);
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		choice = '9' - *cnumber;
		cwild ++;
		MarkNum = choice;
		while(*cwild)
		{
			if( *cwild == Mark)
			{
				MarkNum *= 10;
			}
			else
			{
			}
			cwild ++;
		}
		
		cwild = wild;
		if( len > 1)
		{
			MarkNum = MarkNum + solve(cwild + 1, cnumber + 1, len - 1);
		}
		else
		{
		}

		return MarkNum;
	}

	
}
