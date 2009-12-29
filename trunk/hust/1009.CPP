#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int n,mjnum;
int ip[20][4];
char name[20],ans[20][2][20],temp[20];
char id[20][20];

void solve();
int cmp(int i, int j);

int main(){
  scanf("%d",&n);
  while(n!=0){
	mjnum=0;
	solve();
	scanf("%d",&n);
  }
  return 0;
}

void solve(){
int i,j;

  for(i=0;i<n;i++){
   scanf("%s",name);
   scanf("%d.%d.%d.%d",&ip[i][0],&ip[i][1],&ip[i][2],&ip[i][3]);
   strcpy(id[i],name);
   for(j=0;j<i;j++)
	 if(ip[i][0]==ip[j][0]&&ip[i][1]==ip[j][1]
		&&ip[i][2]==ip[j][2]&&ip[i][3]==ip[j][3]){
	   strcpy(ans[mjnum][0],id[j]);
	   strcpy(ans[mjnum][1],name);
	   mjnum++;
	   }
   }

  for(i=mjnum-2;i>=0;i--)
	for(j=0;j<=i;j++)
	  if(cmp(j,j+1)){
		strcpy(temp,ans[j][0]);
		strcpy(ans[j][0],ans[j+1][0]);
		strcpy(ans[j+1][0],temp);
		strcpy(temp,ans[j][1]);
		strcpy(ans[j][1],ans[j+1][1]);
		strcpy(ans[j+1][1],temp);
		}

  for(i=0;i<mjnum;i++) printf("%s is the MaJia of %s\n",ans[i][1],ans[i][0]);
  printf("\n");
}
int cmp(int i,int j){
char *p,*q;

  p=ans[i][0];
  q=ans[j][0];
  while(*p&&*q)
	if(*p==*q){p++;q++;}
	  else if(*p<*q) break;
		else return 1;
  if(!*q||*p>*q) return 1;
	else return 0;
}