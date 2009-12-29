#include<stdio.h>

int a[30],b[30];
int n,suma,sumb;

void init();
void solve();
int abs(int i);

int main()
{
	int i;
	i=0;
  do{
	scanf("%d",&n);
    if(n!=0&&i!=0)printf("\n");
	  else if(n==0)break;
    init();
    solve();
	i++;
  }while(n!=0);
  return 0;
}

void init()
{
int i;

  for(i=0;i<n;i++)scanf("%d",&a[i]);
  for(i=0;i<n;i++)scanf("%d",&b[i]);
  suma=0;
  sumb=0;
}

void solve()
{
int i;
  for(i=0;i<n;i++)
	if(a[i]!=b[i])
		if(abs(a[i]-b[i])==1)a[i]>b[i]?
			((a[i]==2&&b[i]==1)?sumb+=6:sumb=sumb+a[i]+b[i]):
			((b[i]==2&&a[i]==1)?suma+=6:suma=suma+a[i]+b[i]);
			else a[i]>b[i]?suma+=a[i]:sumb+=b[i];
  printf("A has %d points. B has %d points.\n",suma,sumb); 
}

int abs(int i){
	if(i>0)return i;
	  else return -i;
}