/*
id:wchzw1
prog:clock
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char et[27][15]={"one","two","three","four","five","six","seven","eight","nine","ten",
		 "eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen",
		 "eighteen","ninteen","twenty","thirty","forty","fifty","Quarter","o\'clock","past","to"};
char st[5];
int len;
FILE *in,*out;


void init(){
  in=fopen("clock.in","r");
  out=fopen("clock.out","w");
  fscanf(in,"%s",st);
  len=strlen(st);
  fclose(in);
}

void solve(){
int dot,min,hour,i,j,k;
char hnow[5],mnow[5],now[5],*p,*q;

  if(len==4)dot=2;
	else dot=3;
  p=hnow;i=1;q=st;
  do{
	*p=*q;
	i++;p++;q++;
  }while(i<dot);
  i++;p=mnow;q++;
  do{
	*p=*q;
	i++;p++;q++;
  }while(i<=len);
  hour=atoi(hnow);
  min=atoi(mnow);
  switch(min){
	case 0:
	  strcpy(now,et[hour-1]);
	  now[0]-=32;
	  fprintf(out,"%s %s\n",now,et[24]);
	  break;
	case 15:
	  strcpy(now,et[23]);
	  fprintf(out,"%s %s %s\n",now,et[25],et[hour-1]);
	  break;
	case 45:
	  i=hour;
	  if(i==12)i=0;
	  fprintf(out,"%s %s %s\n",et[23],et[26],et[i]);
	  break;
	default:
	  if(min<45){
		i=min%10;
		if(i==0){
		  j=min/10;
		  if(j!=1)j+=17;else j=9;
		  strcpy(now,et[hour-1]);
		  now[0]-=32;
		  fprintf(out,"%s %s\n",now,et[j]);
		  break;
		}
		else{
		  j=(min-(min%10))/10;
		  if(j>1)j+=17;
		  strcpy(now,et[hour-1]);
		  now[0]-=32;
		  if(j<=1)fprintf(out,"%s %s\n",now,et[min-1]);
			else fprintf(out,"%s %s-%s\n",now,et[j],et[i-1]);
		 break;
		}
	  }else{
		 if(hour==12)k=0;else k=hour;
		 i=60-min;
		 j=(i-(i%10))/10;
		 strcpy(now,et[i-1]);
		 now[0]-=32;
		 fprintf(out,"%s %s %s\n",now,et[26],et[k]);
		 break;
	   }
  }
}

main(){
  init();
  solve();
  fclose(out);
  return(0);
}