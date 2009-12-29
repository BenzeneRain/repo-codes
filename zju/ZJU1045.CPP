#include<stdio.h>

float data[300];
float a;

void init();
void solve();

int main(){
  init();
  scanf("%f",&a);
  while(a!=0){
	solve();
	scanf("%f",&a);
  }
  return 0;
}

void init(){
int i;
float j;
  data[0]=0.5;
  for(i=1;i<300;i++){
	j=i+2;
	data[i]=1/j;
	data[i]+=data[i-1];
	}
}

void solve(){
int i;
  i=0;
  while(a>data[i])i++;
  printf("%d card(s)\n",i+1);
}
