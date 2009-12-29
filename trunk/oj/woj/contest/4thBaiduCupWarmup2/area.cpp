#include<stdio.h>
#include <stdlib.h>
#include <memory.h>
#include<string.h>
#include<math.h>

double Cal(float x1,float y1,float x2,float y2 ){
       
	   double result;
	   
//       printf("Enter Cal\n");
	   if(x1 == x2 ){
		   result =0;
		   return result ;
	   }

	   if(y1<0||y2<0)
		     return 0;

	   result = (y1 + y2 )*(x2 - x1)/2;
//	   printf("result = %f\n", result);
	return result;	       
	   
}


int main(){
   
	long N;
	long i;
	double Total;
	float *p;
	float Min;

	while(1)
	{
		scanf("%ld",&N);
		if(N ==0 )break;
		p = (float *)malloc(sizeof(float)*N * 2);
		Total =0;
	   
		for(i = 0;i < N;i++)
		{
			scanf("%f",(p+i*2));
        		scanf("%f",(p+i*2+1));
			if(i==0)
				Min = *(p+i*2+1);

			else
			{
			    
				if(Min>*(p+2*i+1))
				{
				   Min = *(p+2*i+1);
				}

			}
		}
		
		if((N == 1) || (N == 2))
		{
			printf("0\n");
			continue;
		}
		for(i=0;i<N;i++)
		{
			*(p+i*2+1) -= Min;
		}

		for(i=0;i<N-1;i++)
		{
		   Total+= Cal(*(p+i*2),*(p+2*i+1),*(p+2*i+2),*(p+2*i+3));
		}

		Total += Cal(*(p+i*2),*(p+i*2+1),*p,*(p+1));

		if(Total <0)
			Total *=-1;

		printf("%ld\n",(long )round(Total));
				
		free(p);

	}
	return 0;
 
}
