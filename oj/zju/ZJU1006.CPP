#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void init();
void solve();
void print();

int k,n;
char str[75],ans[75];
int mid[75];

int main(){
//  freopen("zju1006.in","r",stdin);
//  freopen("zju1006.out","w",stdout);
  k=1;
  while(k){
  init();
  solve();
  print();
  }
  return 0;
}

void init(){
int i;
  scanf("%d",&k);
  if(k==0) exit(0);
  strcpy(str,"");
  scanf("%s",str);
  n=strlen(str);
  for(i=0;i<n;i++)
	if(str[i]=='_')mid[i]=0;
	  else if(str[i]=='.')mid[i]=27;
		else mid[i]=str[i]-96;
  memset(ans,NULL,sizeof(ans));
//  strcpy(ans,"");
}

void solve(){
int i;
  for(i=0;i<n;i++){
	if((mid[i]+i)%28==0)ans[(k*i)%n]='_';
	else if((mid[i]+i)%28==27)ans[(k*i)%n]='.';
		else ans[(k*i)%n]=(mid[i]+i)%28+96;
   }
}

void print(){
 puts(ans);
}