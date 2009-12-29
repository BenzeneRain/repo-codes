#include<stdio.h>
#include<stdlib.h>

void init();
void solve();
void qsort(int s,int t);
void print();

int pre[1001];
int weight[1001];
int speed[1001];
int f[1001];
int n;
int num[1001];

int main(){
  freopen("zju1108.in","r",stdin);
  init();
  solve();
  print();
  return 0;
}

void init(){
int i;
  i=0;
  while(scanf("%d%d",&weight[i],&speed[i])!=EOF)i++;
  n=i-1; weight[n+1]=32767;
  for(i=0;i<1001;i++){pre[i]=-1;num[i]=i;};
  for(i=0;i<n+2;i++)f[i]=0;
}

void solve(){
int i,j;
  qsort(0,n);
  for(i=0;i<=n+1;i++)
	for(j=0;j<i;j++)
	  if(speed[j]>speed[i]&&weight[j]<weight[i]&&f[i]<f[j]+1){f[i]=f[j]+1;pre[i]=j;};
}

void qsort(int s,int t){
int x,q,i,j,numt;
  i=s;j=t;x=weight[i];q=speed[i];numt=num[i];
  while(i<j){
	while((weight[j]>x||weight[j]==x&&speed[j]<=q)&&(j>i)) j--;
	if(j>i){
	  weight[i]=weight[j];
	  speed[i]=speed[j];
	  num[i]=num[j];
	  i++;
	  }
	while((weight[i]<x||weight[i]==x&&speed[j]>=q)&&(i<j))i++;
	if(i<j){
	  weight[j]=weight[i];
	  speed[j]=speed[i];
	  num[j]=num[i];
	  j--;
	  }
	weight[i]=x;
	speed[i]=q;
	num[i]=numt;
  }
  if(s<i-1)qsort(s,i-1);
  if(i+1<t)qsort(i+1,t);
}

void print(){
int i,k;
int order[1000];
  printf("%d\n",f[n+1]);
  i=pre[n+1];k=-1;
  while(i!=-1){
	order[++k]=i;
	i=pre[i];
	}
  for(i=k;i>=0;i--) printf("%d\n",num[order[i]]+1);
}