#include<stdio.h>

#define MaxN 20 

int InputData(int *,int *);
int QSort(int *,int ,int );
int OutputData(int *,int);

int main()
 {
	int data[MaxN];
	int scale;
	InputData(data,&scale);
	QSort(data,0,scale-1);
	OutputData(data,scale);
	return 0;
}

int InputData(int *data,int *n)
{
	int i;
	scanf("%d",n);
	for(i=0;i<*n;i++)
		scanf("%d",&data[i]);
	return 0;
}

int QSort(int *data,int head,int tail)
{
	int i,j,key;
	key=data[head];i=head;j=tail;
	while(i<j)
	{
		while(i<j && data[j]>key)j--;
		if(i<j)
		{
			data[i]=data[j];
			i++;
		}
		while(i<j && data[i]<key)i++;
		if(i<j)
		{
			data[j]=data[i];
			j--;
		}
	}
	data[i]=key;
	if(i>head+1)QSort(data,head,i-1);
	if(j<tail-1)QSort(data,j+1,tail);
	return 0;
}

int OutputData(int *data,int n)
{
	int i;
	for(i=0;i<n;i++)printf("%d ",data[i]);
	printf("\n");
	return 0;
}