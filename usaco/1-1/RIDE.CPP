/*
id:wchzw1
prog:ride
*/

#include<stdio.h>
#include<stdlib.h>


main()
{
  char a;
  long int ans,cme;
  int i;
  FILE *in=fopen("ride.in","r");
  FILE *out=fopen("ride.out","w");

  ans=1;cme=1;
  do{
  fscanf(in,"%c",&a);
  if (a=='\n'|| a==' ')break;
  ans=ans*(a-64);
  }
  while(a!='\n');
  do{
  fscanf(in,"%c",&a);
  if (a=='\n'|| a==' ' || feof(in))break;
  cme=cme*(a-64);
  }
  while(a!='\n');
  if(ans%47==cme%47) fprintf(out,"GO\n");
	else fprintf(out,"STAY\n");
  fclose(in);
  fclose(out);
  return(0);
}