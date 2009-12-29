#include<stdio.h>
#include<stdlib.h>

long int n;
long int a,b;
int flag;

int main(){
int i;
	scanf("%ld",&n);
	while(n!=0){
		flag=0;
		for(i=0;i<n;i++){
			scanf("%ld%ld",&a,&b);
			a%=2;b%=2;
			if((a+b)!=1){flag=1;}
		}
		if(!flag)printf("Yes\n");
			else printf("No\n");
	scanf("%ld",&n);
	}
	return 0;
}