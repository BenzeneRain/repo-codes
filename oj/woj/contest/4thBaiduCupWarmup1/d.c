#include <stdio.h>
#include <string.h>

#define ENDMARK "."

int cmp(char *, char *);
void print(char *);

char stc1[2009][19];
char stc2[2009][19];
char minAns[5000][19];
int minlen = 5000;
char currentAns[5000][19];
int currentlen;
int lenStc1, lenStc2;
int ret;

void dfs(int, int);

int main()
{
	int ii, jj, kk1, kk2;

	while(1)
	{
		memset(stc1, 0, sizeof(stc1));
		memset(stc2, 0, sizeof(stc2));

		lenStc1 = 0;
		lenStc2 = 0;

		do
		{
			scanf("%s", stc1[lenStc1 ++]);
		}while(strcmp(stc1[lenStc1 - 1], ENDMARK) != 0);
		if(lenStc1 == 1)
			break;

		do
		{
			scanf("%s", stc2[lenStc2 ++]);
		}while(strcmp(stc2[lenStc2 - 1], ENDMARK) != 0);
		lenStc1 --;
		lenStc2 --;

		ii = 0;
		jj = 0;
		currentlen = 0;
		minlen = 5000;

		dfs(0, 0);

		for(ii = 0; ii < minlen; ii ++)
		{
			printf("%s ", minAns[ii]);
		}
		print(ENDMARK);
	}
	return 0;
}

void dfs(int si, int sj)
{
	int ii, jj, kk1, kk2, kkk1, kkk2, kkk3, go;
	int ret;
	int flag;

	ii= si;
	jj = sj;
	while((ii < lenStc1) && (jj < lenStc2))
	{
		if(currentlen > minlen) break;
		ret = cmp(stc1[ii], stc2[jj]);
		switch(ret)
		{
			case 0:        //stc1[ii] == stc2[jj]
				print(stc1[ii]);
				ii ++;
				jj ++;
			 	break;
			case 1:        
			case 2:
				kk1 = jj;
				while((kk1 < lenStc2) && (strcmp(stc2[kk1], stc1[ii]) != 0))
				{
					kk1 ++;
				}
				kk2 = ii;
				while((kk2 < lenStc1) && (strcmp(stc1[kk2], stc2[jj]) != 0))
				{
					kk2 ++;
				}
				if((kk1 == lenStc2) && (kk2 == lenStc1))
				{
					switch(ret)
					{
						case 1:
							print(stc2[jj]);
							jj ++;
							break;
						case 2:
							print(stc1[ii]);
							ii ++;
							break;
						default:
							break;
					}
				}
				else if((kk1 == lenStc2) || (kk2 == lenStc1))
				{
					if(kk1 == lenStc2)
					{
						while(ii < kk2)
						{
							print(stc1[ii]);
							ii ++;
						}
					}
					else
					{
						while(jj < kk1)
						{
							print(stc2[jj]);
							jj ++;
						}
					}
				}
				else
				{
					if( kkk1 != kkk2)
					{
						kkk1 = jj;
						kkk2 = ii;
						kkk3 = currentlen;
						flag = 0;
						while(jj < kk1)
						{
							print(stc2[jj]);
							jj ++;
							if(currentlen > minlen)
							{
								flag = 1;
								break;
							}
						}
						if(flag)
						{
							dfs(ii, jj);
							jj = kkk1;
					
							while(currentlen > kkk3)
							{
								currentlen --;
								memset(currentAns[currentlen], 0, strlen(currentAns[currentlen]));
							}
						}
						jj = kkk1;

						flag = 0;
						while(ii < kk2)
						{
							print(stc1[ii]);
							ii ++;
							if(currentlen > minlen)
							{
								flag = 1;
								break;
							}
						}

						if(flag)
						{
						dfs(ii, jj);
						ii = kkk2;
						while(currentlen > kkk3)
						{
							currentlen --;
							memset(currentAns[currentlen], 0, strlen(currentAns[currentlen]));
						}
						}
						ii = kkk2;
					}
					else
					{
					
						switch(ret)
							{
								case 1:
									print(stc2[jj]);
									jj ++;
									break;
								case 2:
									print(stc1[ii]);
									ii ++;
									break;
								default:
									break;
							}
					}
				}
			
				break;
			default:
				break;
		}
			
	}
	while(ii < lenStc1)
	{
		print(stc1[ii]);
		ii ++;
	}
	while(jj < lenStc2)
	{
		print(stc2[jj]);
		jj ++;
	}

	if(currentlen < minlen)
	{
		minlen = currentlen;
		for(go = 0; go < currentlen; go ++)
		{
			memset(minAns[go], 0, strlen(minAns[go]));
			strncpy(minAns[go], currentAns[go], strlen(currentAns[go]));
		}
	}
	else if(currentlen == minlen)
	{
		flag = 0;
		for(go = 0; go < currentlen; go ++)
		{
			if(cmp(currentAns[go], minAns[go]) == 1)break;
			if(cmp(currentAns[go], minAns[go]) == 2)
			{
				flag = 1;
				break;
			}
		}
		if(flag)
		{
			for(go = 0; go < currentlen; go ++)
			{
				memset(minAns[go], 0, strlen(minAns[go]));
				strncpy(minAns[go], currentAns[go], strlen(currentAns[go]));
			}
		}
	}

}

int cmp(char *src1, char *src2)
{
	int len1, len2;
	char *s1, *s2;
	int ii, jj;

	s1 = src1;
	s2 = src2;

	len1 = strlen(s1);
	len2 = strlen(s2);

	ii = 0;
	jj = 0;
	while(ii < len1 && jj < len2)
	{
		if(s1[ii] > s2[jj]) return 1;
		if(s1[ii] < s2[jj]) return 2;
		ii ++;
		jj ++;
	}

	if(len1 == len2)return 0;
	if(len1 > len2) return 1;
	if(len1 < len2) return 2;
}

void print(char *src)
{
	if(strcmp(src, ENDMARK) != 0)
	{
	//	printf("%s ", src);
		memset(currentAns[currentlen], 0, strlen(currentAns[currentlen]));
		strncpy(currentAns[currentlen], src,strlen(src));
		currentlen ++;
	}
	else
	{
		printf("%s\n", src);
	}
}
