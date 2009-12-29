/*
id:wchzw1
prog:numtri
*/
#include<stdio.h>
#include<stdlib.h>

long sum[1000][1000];
int n;
FILE *in,*out;

void init(){
  register int i,j;

  in=fopen("numtri.in","r");
  fscanf(in,"%d",&n);
  for(i=0;i<n;i++)
	for(j=0;j<=i;j++)
	  fscanf(in,"%ld",&sum[i][j]);
  fclose(in);
}

void solve(){
  register int i,j;

  for(i=n-1;i>=0;i--)
	for(j=0;j<i;j++)
	  sum[i-1][j]+= sum[i][j]>sum[i][j+1]?sum[i][j]:sum[i][j+1];
}

void print(){
 out=fopen("numtri.out","w");
 fprintf(out,"%ld\n",sum[0][0]);
 fclose(out);
}

main(void){
  init();
  solve();
  print();
  return 0;
}