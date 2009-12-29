#include<stdio.h>
#include<stdlib.h>

void init();
void solve();
void print();

long int len;
int n;

int main(){
  while(1){
   init();
   solve();
   print();
}
   return 0;
}

void init(){
  scanf("%ld%d",&len,&n);
  if(len==0&&n==0)exit(0);
}

void solve(){
int i;
long int a,b,temp;
  for(i=0;i<n;i++){
      scanf("%ld%ld",&a,&b);
      if(b>a){
           temp=a;
           a=b;
           b=temp;
       }
       

}
