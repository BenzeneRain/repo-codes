#include<stdio.h>

int  myswap(int *,int *);
int  donothing();
int (*StrangeUsage[])(int *,int *)=
{
	donothing,
	myswap
};



int main()
{
	int a,b,i,result;
	scanf("%d%d%d",&a,&b,&i);
	result=StrangeUsage[i](&a,&b);
	printf("%d %d\n",a,b);
	return 0;
}

int myswap(int *c,int *d)
{
    (*c)=(*c)^(*d);
    (*d)=(*d)^(*c);
    (*c)=(*c)^(*d);

	return 0;
}
int donothing()
{
	return 0;
}
