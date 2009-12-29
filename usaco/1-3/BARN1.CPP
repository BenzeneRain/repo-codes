/*
id:wchzw1
prog:barn1
*/

#include<stdio.h>
#include<stdlib.h>

int m,s,c,start,total;
int room[200],cha[200],data[200];
FILE *in,*out;

void init(){
int i,now,pre,j,p;

  in=fopen("barn1.in","r");
  fscanf(in,"%d%d%d",&m,&s,&c);
  for(i=0;i<c;i++)fscanf(in,"%d",&data[i]);
  for(i=0;i<c;i++)
	for(j=c-2;j>=i;j--)
	  if(data[j]>data[j+1]){
		p=data[j];
		data[j]=data[j+1];
		data[j+1]=p;
		}
  now=data[0];
  start=now;
  pre=now;
  i=1;
  while(i<c){
	now=data[i];
	room[pre]=now;pre=now;
	i++;
  }
 total=pre-start+1;
 room[pre]=-1;
 fclose(in);
  for(i=0;i<c;i++)cha[200]=0;
}

void solve(){
int i,j,k,p,now;
  k=start;
  for(i=0;i<c-1;i++){
	cha[i]=room[k]-k;
	k=room[k];
  }
  for(i=0;i<m;i++)
	for(j=c-3;j>=i;j--)
	  if(cha[j]<cha[j+1]){
		p=cha[j];
		cha[j]=cha[j+1];
		cha[j+1]=p;
		}
  for(i=0;i<m-1;i++)total=total-cha[i]+1;
}

void print(){
  out=fopen("barn1.out","w");
  fprintf(out,"%d\n",total);
  fclose(out);
}

main(){
  init();
  if(m<c)solve();else total=c;
  print();
  return(0);
}