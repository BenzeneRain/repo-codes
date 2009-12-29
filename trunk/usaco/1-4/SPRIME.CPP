/*
id:wchzw1
prog:sprime
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int n,k;
FILE *in,*out;

void init(){
  in=fopen("sprime.in","r");
  fscanf(in,"%d",&n);
  fclose(in);
  out=fopen("sprime.out","w");
  k=1;
}

int chk(long now){
  register int i;

  if(now%2==0&&now!=2||now==1) return 0;
  for(i=1;i<=sqrt(now);i+=2)
	if(i!=1&&now%i==0) return 0;
  return 1;
}

void solve(long p){
  register int i;
  long now;

  for(i=1;i<10;i++){
	if(i>2&&i%2==0)i++;
	now=p*10+i;
	if(chk(now))
	  if(k==n)fprintf(out,"%ld\n",now);
		else{k++;solve(now);k--;};
  }
}

main(){

  init();
  solve(0);
  fclose(out);
  return 0;
}