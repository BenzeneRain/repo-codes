#include<stdio.h>

float sp,w,st;

int main(){
int k;
  scanf("%f%f%f",&sp,&w,&st);
  while(sp!=0&&w!=0&&st!=0){
	k=0;
	if(sp<=4.5&&w>=150&&st>=200) {printf("Wide Receiver");k++;}
	if(sp<=6.0&&w>=300&&st>=500) {if(k)printf(" ");printf("Lineman");k++;}
	if(sp<=5.0&&w>=200&&st>=300) {if(k)printf(" ");printf("Quarterback");k++;}
	if(!k)printf("No positions\n");else printf(" \n");
	scanf("%f%f%f",&sp,&w,&st);
  }
  return 0;
}