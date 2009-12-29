#include<stdio.h>

struct{
   int a,b,pre,action;
}status[500];

void init();
void solve();
int check();
void print();

int a,b,n,k,open,closed;


int main(){
 if(scanf("%d%d%d",&a,&b,&n)!=EOF)k=1;
   else k=0;
  while(k){
  init();
  solve();
  if(scanf("%d%d%d",&a,&b,&n)!=EOF)k=1;
   else k=0;
  }  
  return 0;
}

void init(){ 
    status[0].a=0;
    status[0].b=0;
    status[0].pre=0;
    status[0].action=-1;
    open=0;
    closed=-1;
}     

void solve(){
int i,key;
  while(open>closed){
      closed++;
      for(i=0;i<6;i++){
          key=0;
          if(i==0&&status[closed].a!=a){
              open++;
              status[open].a=a;
              status[open].b=status[closed].b;
              key=1;
              }
             else if(i==1&&status[closed].b!=b){
                 open++;
                 status[open].a=status[closed].a;
                 status[open].b=b;
                 key=1;
                 }
             else if(i==2&&status[closed].a!=0){
                  open++;
                  status[open].a=0;
                  status[open].b=status[closed].b;
                  key=1;
                }
             else if(i==3&&status[closed].b!=0){
                 open++;
                 status[open].a=status[closed].a;
                 status[open].b=0;
                 key=1;
                 }
             else if(i==4&&status[closed].a!=0&&status[closed].b!=b){
                 open++;
                 if(status[closed].a<=(b-status[closed].b)){
                   status[open].a=0;
                   status[open].b=status[closed].b+status[closed].a;
                   }
                   else{
                       status[open].a=status[closed].a+status[closed].b-b;
                       status[open].b=b;
                   }
                 key=1;
              }
              else if(i==5&&status[closed].a!=a&&status[closed].b!=0){
                 open++;
                 if(status[closed].b<=(a-status[closed].a)){
                   status[open].b=0;
                   status[open].a=status[closed].b+status[closed].a;
                   }
                   else{
                       status[open].b=status[closed].a+status[closed].b-a;
                       status[open].a=a;
                   }
                 key=1;                         
              }                       
          if(key){status[open].pre=closed;status[open].action=i;}   
		  if(key&&check()) open--;
			else if(status[open].b==n){print();open=closed;break;}
      }
  }  
}

int check(){
int i;
  for(i=1;i<open;i++)
    if(status[i].a==status[open].a&&status[i].b==status[open].b) return 1;
  return 0;
}

void print(){
int order[1000];
int i,num;
  i=open;num=-1;
  while(i){
      num++;
	  order[num]=i;
      i=status[i].pre;
  }
  for(i=num;i>=0;i--)
    switch(status[order[i]].action){
		case 0:printf("fill A\n");break;
		case 1:printf("fill B\n");break;
		case 2:printf("empty A\n");break;
		case 3:printf("empty B\n");break;
		case 4:printf("pour A B\n");break;
		case 5:printf("pour B A\n");break;
	}
  printf("success\n");
}
                 
