#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void solve();

int n,num;
int o,z;

int main(){
  solve();
  return 0;
}    

void solve(){
int i,j,k;
  scanf("%d",&n);
  for(i=0;i<n;i++){
    o=0;z=0;
    scanf("%d",&num);
    for(j=0;j<num;j++){
    scanf("%d",&k);
    if(j%2==0&&k==1)o++;
    if(j%2==1&&k==1)z++;
    }
    if(num%2==1)printf("YES\n");
    if(num%2==0)
      if(abs(o-z)<=1)printf("YES\n");
       else printf("NO\n");    
  }    
}    
