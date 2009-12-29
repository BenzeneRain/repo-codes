#include<stdio.h>
#include<string.h>
#include<ctype.h>

int k,e;
char kword[25][25];
char word[25][80];
char temp[80];
int count[25];
int max;

void init();
void solve();
void compare(int id);
void print(int id);

int main()
{
	int i;
	i=1;
	while(scanf("%d %d\n",&k,&e)!=EOF)
	{
		init();	
		solve();
		print(i);
		i++;
	}
	return 0;
}

void init()
{
	int i;
	int j;
	memset(kword,0,sizeof(kword));
	memset(word,0,sizeof(word));
	for(i=0;i<k;i++)gets(kword[i]);//scanf("%s",kword[i]);
	for(i=0;i<e;i++)count[i]=0;
	max=0;
}

void solve()
{
	int i;
	int j;
	int kk;
	int len;
	memset(temp,0,sizeof(temp));
	for(i=0;i<e;i++)
	{
		gets(word[i]);
		len=strlen(word[i]);
		word[i][len]='\0';
		kk=0;
		for(j=0;j<=len;j++)
		{
			if(isalpha(word[i][j]) && j<len)
			{
				temp[kk++]=tolower(word[i][j]);	
			}
			else if(kk!=0)
			{
				temp[kk]='\0';
				compare(i);
				kk=0;
				memset(temp,0,sizeof(temp));
			}
			else memset(temp,0,sizeof(temp));
		}
		if(count[i]>max)max=count[i];
	}
}

void compare(int id)
{
	int i;
	for(i=0;i<k;i++)
		if(strcmp(kword[i],temp)==0)
	{
		count[id]++;
		return;
	}	
	return;
}

void print(int id)
{
	int i;
	printf("Excuse Set #%d\n",id);
	for(i=0;i<e;i++)
		if(count[i]==max)
			printf("%s\n",word[i]);
	printf("\n");
}
