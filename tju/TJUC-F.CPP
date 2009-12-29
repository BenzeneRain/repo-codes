#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void init();
void solve();

float cal;
int n;
float lowcase[100];
int closest[100]; 
char name[100][30];
float val[100][100];

int main(){
  while(scanf("%f",&cal)!=EOF){
	init();
	solve();
  }
  return 0;
}

void init(){
float j;
int i,k,p,q,f;
char nk[30],nt[30];
  scanf("%d",&n);
  for(i=0;i<n;i++)
	for(f=0;f<n;f++)
	  if(i==f)val[i][f]=0;
		else val[i][f]=32767;
  for(i=0;i<n;i++)scanf("%s",name[i]);
  scanf("%d",&k);
  for(i=0;i<k;i++){
	scanf("%s %s",nk,nt);
	scanf("%f",&j);
	p=-1;q=-1;f=0;
	while(q==-1||p==-1){
	  if(p==-1&&!strcmp(nk,name[f]))p=f;
	  if(q==-1&&!strcmp(nt,name[f]))q=f;
	  f++;
	}
	val[p][q]=j;
	val[q][p]=j;
	}
}

void solve(){
float cost,min;
int i,j,k;  
  cost=0;
  for(i=0;i<n;i++) {
      lowcase[i]=val[0][i];  
      closest[i]=0;  
}  
  for(i=0;i<n-1;i++){
    min=32767;
    for(j=0;j<n;j++)
      if(lowcase[j]<min&&lowcase[j]!=0){
            min=lowcase[j];
            k=j;
        }
     cost+=val[closest[k]][k];
     lowcase[k]=0;
     for(j=0;j<n;j++)
           if(val[k][j]<lowcase[j]){
                 lowcase[j]=val[k][j];
                 closest[j]=k;
             }
         }                        
  if(cost>cal) printf("Not enough cable\n");
	else printf("Need %.1f miles of cable\n",cost);
}
