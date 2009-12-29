/*
id:wchzw1
prog:gift1
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static char name[10][14];
static int money[10];
int np,acc,n;
char giver[14],ri[14];
FILE *in=fopen("gift1.in","r");
FILE *out=fopen("gift1.out","w");

void init(){
  int i;
  fscanf(in,"%d",&np);
  for(i=0;i<=np-1;i++) fscanf(in,"%s",name[i]);
  for(i=0;i<=np-1;i++) money[i]=0;
}

void solve(){
  int i,j,left;
  while(!feof(in)){
  strcpy(giver,"");
  fscanf(in,"%s",giver);
  fscanf(in,"%d%d",&acc,&n);
  if (n==0) continue;
  left=acc%n;
  for(i=0;i<np;i++)
	if (strcmp(name[i],giver)==0){
	  money[i]=money[i]-acc+left;
	  break;
	 }
  for(i=0;i<n;i++){
	strcpy(ri,"");
	fscanf(in,"%s",ri);
	for(j=0;j<np;j++)
		if (strcmp(name[j],ri)==0){
			money[j]=money[j]+(acc-left)/n;
			continue;
	 }
	}
  };
   fclose(in);
}

void print(){
  int i;
  for(i=0;i<np;i++) fprintf(out,"%s %d\n",name[i],money[i]);
  fclose(out);
}

main(){
  init();
  solve();
  print();
  return(0);
}