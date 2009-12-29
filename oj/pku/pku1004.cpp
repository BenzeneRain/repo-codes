#include<stdio.h>
#include<stdlib.h>

float a,sum,avg;

int main(){
int i;
  while(scanf("%f",&a)!=EOF){
	sum=a;
	for(i=1;i<12;i++){
	  scanf("%f",&a);
	  sum+=a;
	 }
	avg=sum/12;
	printf("$%.2f\n",avg);
	}
  return 0;
}