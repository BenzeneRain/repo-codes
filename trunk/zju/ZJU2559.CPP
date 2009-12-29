#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void init();
void solve();
void print();
double calc(int i,int j);

struct{
  long int x,y;
}point[3];

double dis[3];
double r[3];

int main(){
  freopen("zjuc1001.in","r",stdin);
  while(scanf("%ld%ld",&point[0].x,&point[0].y)!=NULL&&!feof(stdin)){
	init();
	solve();
	print();
  }
  return 0;
}

void init(){
int i;
  for(i=1;i<3;i++) scanf("%ld%ld",&point[i].x,&point[i].y);
}

void solve(){
  dis[0]=calc(0,1);
  dis[1]=calc(0,2);
  dis[2]=calc(1,2);
  r[0]=(dis[0]-dis[2]+dis[1])/2;
  r[1]=(dis[0]+dis[2]-dis[1])/2;
  r[2]=(dis[2]+dis[1]-dis[0])/2;
}

double calc(int i,int j){
double val1,val2,k,val;

  val2=(point[i].y-point[j].y);
  val2*=(point[i].y-point[j].y);
  val1=(point[i].x-point[j].x);
  val1*=(point[i].x-point[j].x);
  val=val1+val2;
  k=sqrt(val);
  return k;
}

void print(){
int i;
  for(i=0;i<3;i++)printf("%4.6f\n",r[i]);
}