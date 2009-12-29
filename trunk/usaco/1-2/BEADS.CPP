/*
id:wchzw1
prog:beads
*/
#include<stdio.h>
#include<stdlib.h>

int n,max;
char beads[350];
FILE *in=fopen("beads.in","r");
FILE *out=fopen("beads.out","w");


void init(){
  fscanf(in,"%d",&n);
  fscanf(in,"%s",beads);
  max=0;
  fclose(in);
};

int count(int x,int y){
int pass,bl[350];
char mark;

for(pass=0;pass<n;pass++)bl[pass]=0;
pass=0;mark='w';
while(bl[x]==0&&(beads[x]=='w'||beads[x]==mark||mark=='w')){
  if(mark=='w'&&beads[x]!='w')mark=beads[x];
  bl[x]=1;
  pass++;
  x++;
  if(x>n-1)x=0;
  };
mark='w';
while(bl[y]==0&&(beads[y]=='w'||beads[y]==mark||mark=='w')){
  if(mark=='w'&&beads[y]!='w')mark=beads[y];
  bl[y]=1;
  pass++;
  y--;
  if(y<0)y=n-1;
  };
return(pass);
};

void solve(){
  int i,j,toa,now;

  toa=1;
  i=0;j=n-1;
  while (toa<n){
	now=count(i,j);
	if(now>max) max=now;
	i--;
	j--;
	if(i<0)i=n-1;
	toa++;}
};

void print(){

  fprintf(out,"%d\n",max);
  fclose(out);
}

main(){
 init();
 solve();
 print();
 return(0);
}
