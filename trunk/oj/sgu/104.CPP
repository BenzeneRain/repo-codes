#include<stdio.h>
#include<stdlib.h>

void init();
int max(int a,int b);
void print();
void solve1();

int f,v;
int data[100][100];
int t[100][100];

int main(){
  freopen("104.in","r",stdin);
  init();
  solve1();
  print();
  return 0;
}

void init(){
int i,j;
  for(i=0;i<100;i++)
	for(j=0;j<100;j++) t[i][j]=-9999;
  scanf("%d%d",&f,&v);
  for(i=0;i<f;i++)
	for(j=0;j<v;j++)
	  scanf("%d",&data[i][j]);
}

int max(int a,int b){
  if(a<b){a=a^b;b=b^a;a=a^b;}
  return a;
}

void solve1(){
int i,j;
  t[0][0]=data[0][0];
  for(j=1;j<v;j++) t[0][j]=max(t[0][j-1],data[0][j]);
  for(i=1;i<f;i++)
	for(j=1;j<v;j++)
	  t[i][j]=max(t[i-1][j-1]+data[i][j],t[i][j-1]);
}

void print(){
int order[100];
int k,i,j,p;
  printf("%d\n",t[f-1][v-1]);
  p=v-1;
  k=-1;
  for(i=f-1;i>=0;i--){
   j=p;
   while(t[i][j]==t[i][p]&&j>=0)
	j--;
   order[++k]=j+2;
   p=j;
   }
  for(i=k;i>0;i--)printf("%d ",order[i]);
  printf("%d\n",order[0]);
}
