#include<stdio.h>
#include<math.h>

float vs,r,c,w,ans,z,xc;
int n;

int main(){
int i;
	scanf("%f%f%f%d",&vs,&r,&c,&n);
	for(i=0;i<n;i++){
	  scanf("%f",&w);
      //z=r-1/(w*c);
	  xc=1/(w*c);
	  //if(z<0)z=-z;
	  z=sqrt(xc*xc+r*r);
	  ans=vs*r/z;
	  printf("%.3f\n",ans);
	}
	return 0;
}