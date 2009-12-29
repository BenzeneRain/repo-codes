#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int t,n;
int b[100],r[100];
char num[500];

void init();
void solve();
void print();

int main(){
int i;
	scanf("%d",&t);
	for(i=0;i<t;i++){
		init();
		solve();
		print();
	}
	return 0;
}

void init(){
int i,j;
char ch;
	scanf("%d",&n);
	for(i=0;i<n;i++)scanf("%d",&b[i]);
	scanf("%s",num);
	i=0;j=strlen(num)-1;
	while(i<j){
		ch=num[i];
		num[i]=num[j];
		num[j]=ch;
		i++;j--;
	}
}

void solve(){
int j,i;
long int chu;
int finish;
	for(i=0;i<n;i++){
		j=strlen(num)-1;
		finish=0;
		chu=0;
		while(!finish){
			if(j<4){
				while(j>=0){
					chu=chu*10+(int)(num[j]-'0');
					j--;
				}
				r[i]=chu%b[i];
				finish=1;
			}
			else{
				chu=chu*10+(int)(num[j]-'0');
				if(chu<b[i]){
					j--;
				}
				else{
					chu=chu%b[i];
					j--;
				}
			}
		}
	}
}

void print(){
int i;
	printf("(%d",r[0]);
	for(i=1;i<n;i++)printf(",%d",r[i]);
	printf(")\n");
}