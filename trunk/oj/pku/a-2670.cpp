#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void init();

char name[1000][20];
int din[1000],dout[1000][10];
int m,n;

int main(){
  freopen("a-2670.in","r",stdin);
  init();
  return 0; 
}    

void init(){
int i,j,k,key,fini;
char ch,natemp[20],nord;
int ord[9];
  scanf("%d%d",&m,&n);
  if(m==0&&n==0)exit(0);
  memset(name,0,sizeof(name));
  for(i=0;i<m;i++){
      j=0;ch=' '; 
      while(ch!='\0'&&ch!='\n')scanf("%c",&ch);
      while(ch!='\0'&&ch!='\n'){
          name[i][j]=ch;
          j++;
          scanf("%c",&ch);
      }
  } 
  for(i=0;i<n;i++){
      fini=1;nord=0;
      while(fini){
      j=0;ch=0;
      memset(natemp,0,sizeof(natemp));
      while(ch=='\n'&&ch=='\0')scanf("%c",&ch);
      while(ch!=','&&ch!=':'){
        natemp[j]=ch;
        j++;
        scanf("%c",&ch);
      }
      key=0;
      for(k=0;k<m;k++)
        if(!strcpy(natemp,name[k])){key=1;ord[nord]=k;nord++;break;};
      if(!key){strcpy(name[m],natemp);nord[ord]=m;nord++;m++;}
      memset(natemp,0,sizeof(natemp));  
      if(ch==':'){
          scanf(" %s",natemp);         
          key=0;
          for(k=0;k<m;k++)
            if(!strcpy(natemp,name[k])){key=1;break;};
          if(!key){strcpy(name[m],natemp);m++;}
          fini=0;
          for(j=0;j<nord;j++){
              dout[j][0]++;
              dout[j][dout[j][0]]=k;
          } 
          din[k]+=nord;       
      }
      else scanf(" ");
   }          
  }        
}    
