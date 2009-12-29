/*
id:wchzw1
prog:milk
*/
#include<stdio.h>
#include<stdlib.h>

long int total,num[5000][2],money;
int n;
FILE *in=fopen("milk.in","r");
FILE *out=fopen("milk.out","w");

void init(){
int i;

  money=0;
  fscanf(in,"%ld%d",&total,&n);
  for(i=0;i<n;i++)
	fscanf(in,"%d%ld",&num[i][0],&num[i][1]);
  fclose(in);
}

void sort(){
int i,j;
long temp;

  for(i=0;i<n-2;i++)
	for(j=n-2;j>=i;j--)
	  if(num[j][0]>num[j+1][0]){
		 temp=num[j][0];
		 num[j][0]=num[j+1][0];
		 num[j+1][0]=temp;
		 temp=num[j][1];
		 num[j][1]=num[j+1][1];
		 num[j+1][1]=temp;
	  }
}

void solve(){
int i;
 sort();
 i=0;
 while(1){
   if(total>num[i][1]){
	 total=total-num[i][1];
	 money=money+num[i][0]*num[i][1];
	 }
   else{
	 money=money+total*num[i][0];
	 break;
	}
 i++;
 }
}

void print(){
  fprintf(out,"%ld\n",money);
  fclose(out);
}

main(){
  init();
  solve();
  print();
  return(0);
}