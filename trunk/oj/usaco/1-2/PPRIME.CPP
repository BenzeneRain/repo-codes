/*
id:wchzw1
prog:pprime
*/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

long a,b,num;
char st[10];
FILE *in=fopen("pprime.in","r");
FILE *out=fopen("pprime.out","w");

char *cst(char *st){
  char a;
  long i,j,c,le;
  int bo;

  le=strlen(st);
  bo=0;
  if(le%2==1){
	i=(le+1)/2-1;j=i;
  }
  else{i=le/2-1;j=le/2;};
  while(bo==0){
  if(i==0&&st[i]=='9'){
	st[i]='1';
	if(i!=j)st[j]='0';
	strcat(st,"1");bo=1;break;}
  if(st[i]=='9'){
	 st[i]='0';
	 st[j]=st[i];
	 i--;j++;}
	else{st[i]=st[i]+1;if(i!=j)st[j]=st[i];i--;j++;bo=1;break;};
  }
  return(st);
};

void init(){
  char *s;
  long int i,j,k;

  fscanf(in,"%ld%ld",&a,&b);
  if(a%2==0)a++;
  if(b%2==0)b--;
  sprintf(s,"%ld",a);
  i=0;j=strlen(s)-1;
  while(i<j){
	s[j]=s[i];
	i++;j--;
  }
  k=atol(s);
  while(k<a){
   strcpy(cst(s),s);
   k=atol(s);
  }
  strcpy(st,s);
 fclose(in);
};

void check(long x){
long i;
int bo;
  bo=0;
  for(i=3;i<sqrt(x)+1;i=i+2)
	if(x%i==0){bo=1;break;}
  if(bo==0){fprintf(out,"%ld\n",x);}
 };

void solve(){
 if(atol(st)<=b)check(atol(st));
 while(atol(st)<=b){
   strcpy(cst(st),st);
   if(atol(st)<=b&&atol(st)%2!=0)check(atol(st));
 }
};

main(){
  init();
  solve();
  fclose(out);
  return(0);
}
