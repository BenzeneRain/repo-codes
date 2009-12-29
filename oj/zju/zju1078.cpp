#include<stdio.h>
#include<string.h>

const char symbol[16]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
int n;
int hash[20];

void init();
void solve();
void print();

int main(){
	scanf("%d",&n);
	while(n!=0)
	{
		init();
		solve();
		print();
		scanf("%d",&n);
	}
	return 0;
}

void init(){

	memset(hash,0,sizeof(hash));
}

void solve(){
char st[20];
int i,j,k,key;

	for(i=2;i<=16;i++){
		memset(st,NULL,sizeof(st));
	    j=0;k=n;
		while(k>=i){
			st[j]=symbol[k%i];
			k=(k-k%i)/i;
			j++;
		}
		st[j]=symbol[k];
		k=0;key=0;
		while(k<j){
			if(st[k]!=st[j]){key=1;break;}
			k++;j--;
		}
		if(!key)hash[i]=1;
	}
}

void print(){
int i,key;
int ans[20];
	key=-1;
	for(i=2;i<=16;i++)
		if(hash[i])ans[++key]=i;
	if(key==-1)printf("Number %d is not a palindrom\n",n);
	  else
	  {
		  printf("Number %d is palindrom in basis",n);
		  for(i=0;i<=key;i++)printf(" %d",ans[i]);
		  printf("\n");
	  }
}
