#include<iostream>
using namespace std;

void init();
void solve();
void print();

long ans;
int n;
int data[100][100];
long int pre_solve[100][100];

main(){
  init();
  solve();
  print();
  return 0;
}

void init(){
register int i,j;

  cin>>n;
  for(i=0;i<n;i++)
    for(j=0;j<n;j++){
      cin>>data[i][j];
      pre_solve[i][j]=0;
    }
  for(i=0;i<n;i++)
    for(j=0;j<n;j++){
      if(i==0&&j==0) pre_solve[i][j]=data[i][j];
        else if(i==0)pre_solve[i][j]=pre_solve[i][j-1]+data[i][j];
               else if(j==0)pre_solve[i][j]=pre_solve[i-1][j]+data[i][j];
                       else pre_solve[i][j]=pre_solve[i-1][j]+pre_solve[i][j-1]+data[i][j]-pre_solve[i-1][j-1];
    }
 ans=100*100*(-127);
}

void solve(){
register int i,j,k,t;
register long int now;
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      for(k=i;k<n;k++)
        for(t=j;t<n;t++){
          if(i==0&&j==0)now=pre_solve[k][t];
            else if(i==0)now=pre_solve[k][t]-pre_solve[k][j-1];
              else if(j==0)now=pre_solve[k][t]-pre_solve[i-1][t];
                else if(i==k&&j==t)now=data[i][j];
                  else now=pre_solve[k][t]-pre_solve[i-1][t]-pre_solve[k][j-1]+pre_solve[i-1][j-1];
          if(now>ans)ans=now;
        }
}

void print(){
 cout<<ans<<endl;
}
