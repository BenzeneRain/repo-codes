/*
id:wchzw1
prog:checker
*/
#include<stdio.h>
#include<stdlib.h>

unsigned int row[15],lu_rd[40],ld_ru[40],n,ans[15],tar,mid,kill;
unsigned long num,mnum;
FILE *in,*out;

void init(){
 register int i;

  in=fopen("checker.in","r");
  fscanf(in,"%d",&n);
  for(i=0;i<n;i++){
	row[i]=0;
	ans[i]=0;
  }
  for(i=0;i<(n+1)*2;i++){
	lu_rd[i]=0;
	ld_ru[i]=0;
  }
  num=0;
  tar=(n%2==1?1:0);
  if(tar==1)mid=(n+1)/2-1;
	else mid=n/2-1;
  mnum=0;
  kill=0;
  fclose(in);
  out=fopen("checker.out","w");
}

void print(){
 register int i;
 fprintf(out,"%d",ans[0]+1);
 for(i=1;i<n;i++)fprintf(out," %d",ans[i]+1);
 fprintf(out,"\n");
}

void solve(int k){
 register int i;

 for(i=0;i<n;i++)
   if(row[i]==0&&ld_ru[i-k]==0&&lu_rd[i+k]==0){
	 row[i]=1;
	 ld_ru[i-k]=1;
	 lu_rd[i+k]=1;
	 ans[k]=i;
	 if(k<n-1)solve(k+1);
	   else{
			if(ans[0]==mid)
			  mnum++;
			if(ans[0]>mid&&num>3&&n>6){
			  kill=1;
			  break;
			}
			num++;
			if(num<=3) print();
		  }
	 row[i]=0;
	 ld_ru[i-k]=0;
	 lu_rd[i+k]=0;
	 ans[k]=0;
	 if(kill)break;
   }
}


main(){
  init();
  solve(0);
  if(tar==1)num=num*2-mnum;
	else if(n>6) num*=2;
  fprintf(out,"%d\n",num);
  fclose(out);
  return(0);
}