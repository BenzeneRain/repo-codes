#include<stdio.h>
#include<stdlib.h>

void init();
void dfs(int n);
void print();

int n,max,left;
char map[5][5];
int hash[5][5];

main(){
//  freopen("zju1002.in","r",stdin);
  n=1;
  while(n){
	init();
	if(n==0) exit(0);
	dfs(1);
	print();
	}
  return 0;
}

void init(){
 int i,j;
 scanf("%d",&n);
 left=n*n;
 max=0;
 for(i=0;i<n;i++){
	scanf("%s",map[i]);
   for(j=0;j<n;j++)
	if(map[i][j]=='.') hash[i][j]=1;
	  else {hash[i][j]=0;left--;}
	}
}

void dfs(int layer){
int i,j,k,t;
int ocpd[20];
  k=-1;
  for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	  if(hash[i][j]){
		hash[i][j]=0;
		left--;
		t=j+1;
		while(t<n&&map[i][t]!='X')
		{
		if(!hash[i][t]){t++;continue;}
		k++;ocpd[k]=i*10+t;hash[i][t]=0;t++;left--;
		}
		t=j-1;
		while(t>=0&&map[i][t]!='X')
		{
		if(!hash[i][t]){t--;continue;}
		k++;ocpd[k]=i*10+t;hash[i][t]=0;t--;left--;
		}
		t=i+1;
		while(t<n&&map[t][j]!='X')
		{
		if(!hash[t][j]){t++;continue;}
		k++;ocpd[k]=t*10+j;hash[t][j]=0;t++;left--;
		}
		t=i-1;
		while(t>=0&&map[t][j]!='X')
		{
		if(!hash[t][j]){t--;continue;}
		k++;ocpd[k]=t*10+j;hash[t][j]=0;t--;left--;
		}
		if(left)dfs(layer+1);
		 else if(layer>max)max=layer;
		hash[i][j]=1;
		for(;k>=0;k--){
		hash[(ocpd[k]-ocpd[k]%10)/10][ocpd[k]%10]=1;
		left++;
		}
		left++;
		}
}
void print(){
  printf("%d\n",max);
}