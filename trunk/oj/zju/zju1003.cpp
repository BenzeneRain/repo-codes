#include<stdio.h>
#include<stdlib.h>

void init();
void print();
void solve(long int m,long int n,long int p);
long int min(long int i,long int j);  

long int a,b;
int key1,key2,key3;;


int main(){
    while(scanf("%ld%ld",&a,&b)!=EOF){
    init();
    solve(a,b,min(100,min(a,b)));
    print();
  }    
    return 0;
}

long int min(long int i,long int j){
  if(i>j)return j;
    else return i;
}

void solve(long int m,long int n,long int p){
long int k;   
   if(n==1&&m==1)key1=1;
   if(m==1)key2=1;
   if(key1)key3=1;
   if(p==1||key3)return;
   if(m%p==0)solve(m/p,n,p-1);
   if(n%p==0){k=n/p;solve(m,k,p-1);}
   solve(m,n,p-1);
} 

void init(){
  if(a>b){a=a^b;b=b^a;a=a^b;}
  key1=0;
  key2=0;
  key3=0;
}    


void print(){
    if(key1||(!key2))printf("%ld\n",b);
      else printf("%ld\n",a);
}                
