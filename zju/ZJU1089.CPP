#include<stdio.h>
#include<stdlib.h>

void dfs(int layer);
void init();
void print();

int k;
int order[20],data[20],hash[50];

int main(){
  init();
  while(k){
  dfs(0);
  init();
  printf("\n");
  }
  return 0;
}

void init(){
int i;
  scanf("%d",&k);
  if(k==0)exit(0);
  for(i=0;i<k;i++)scanf("%d",&data[i]);
  for(i=0;i<50;i++)hash[i]=1;
}

void dfs(int layer){
int i;
  for(i=0;i<k;i++)
	if(hash[data[i]]){
	  if(layer!=0&&data[i]<order[layer-1]) continue;
	  order[layer]=data[i];
	  hash[data[i]]=0;
	  if(layer==5) print();
		else dfs(layer+1);
	  hash[data[i]]=1;
	  order[layer]=0;
	  }
}

void print(){
int i;
  for(i=0;i<5;i++) printf("%d ",order[i]);
  printf("%d\n",order[5]);
}