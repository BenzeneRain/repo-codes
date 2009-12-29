#include<stdio.h>
#include<stdlib.h>

void init();
void solve();
void print();
void qsort(int s,int t);

int t,n,ans;
int w[5005],l[5005],hash[5005];

int main(){
int i;
  scanf("%d",&t);
  for(i=0;i<t;i++){
  init();
  solve();
  print();
  }
  return 0;
}

void init(){
int i;
  ans=0;
  scanf("%d",&n);
  for(i=1;i<=n;i++){
	scanf("%d%d",&l[i],&w[i]);
	}
  for(i=0;i<5005;i++)hash[i]=1;
  w[0]=1;
  l[0]=1;
}

void solve(){
int i,left,wn,ln;
  qsort(1,n);
  left=n;
  while(left>0){
   wn=w[0];ln=l[0];ans++;
   for(i=1;i<=n;i++)
	if(hash[i]&&w[i]>=wn&&l[i]>=ln){
	  hash[i]=0;
	  wn=w[i];
	  ln=l[i];
	  left--;
	  }
  }
}

void print(){
  printf("%d\n",ans);
}

void qsort(int s,int t){
int i,j;
int keyw,keyl;
  i=s;j=t;keyw=w[i];keyl=l[i];
  while(i<j){
	while((l[j]>keyl||(l[j]==keyl&&w[j]>=keyw))&&i<j)j--;
	if(i<j){
	  l[i]=l[j];
	  w[i]=w[j];
	  i++;
	  }
	while((l[i]<keyl||(l[i]==keyl&&w[i]<=keyw))&&i<j)i++;
	if(i<j){
	  l[j]=l[i];
	  w[j]=w[i];
	  j--;
	  }
	w[i]=keyw;
	l[i]=keyl;
  }
  if(s<(i-1))qsort(s,i-1);
  if(t>(i+1))qsort(i+1,t);
}