#include<stdio.h>
#include<math.h>

#define pi acos(-1)

float x,y,r,s;
int i,n,years;

int main()
{
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%f%f",&x,&y);
		r=sqrt(x*x+y*y);
		s=pi*r*r/2;
		years=ceil(s/50);
		printf("Property %d: This property will begin eroding in year %d.\n",i+1,years);
		
	}
	printf("END OF OUTPUT.\n");
	return 0;
}
