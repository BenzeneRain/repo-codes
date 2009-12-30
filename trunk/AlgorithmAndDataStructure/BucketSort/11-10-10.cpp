#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MaxLen 20
#define MaxR 30

struct node_type
{
	char *word;
	struct node_type *next;
};

void init(struct node_type**,int *);
void print(struct node_type*);
void bsort(struct node_type**,int,int);
int eva(char*,int);

int main()
{
	struct node_type *mylist;
	int CurrentMaxLen;
        init(&mylist,&CurrentMaxLen);
	bsort(&mylist,28,CurrentMaxLen);
	print(mylist);
	return 0;
}

void init(struct node_type **ThisList,int *len)
{
	char str[MaxLen];
	int TempLen,TempMaxLen;
        struct node_type *head,*next,*pre;
	FILE *fin;
	
	fin=freopen("data.txt","r",stdin);
	TempMaxLen=0;
	if(gets(str)!=NULL)
	{
 		TempLen=strlen(str);
		head=(struct node_type *)malloc(sizeof(struct node_type));
		head->word=(char *)malloc(TempLen*sizeof(char));
		if(TempLen>TempMaxLen)TempMaxLen=TempLen;
                strcpy(head->word,str);
		head->next=NULL;
		pre=head;
	}
	else
	{
		*ThisList=NULL;
		fclose(fin);
		*len=0;
	}
	
	while(gets(str)!=NULL)
	{
		TempLen=strlen(str);
                next=(struct node_type *)malloc(sizeof(struct node_type));
		next->word=(char *)malloc(TempLen*sizeof(char));
		if(TempLen>TempMaxLen)TempMaxLen=TempLen;
		strcpy(next->word,str);
		next->next=NULL;
		pre->next=next;
		pre=next;
	}
	fclose(fin);
	*ThisList=head;
	*len=TempMaxLen;
}

void print(struct node_type* ThisNode)
{
	struct node_type* next;
	next=ThisNode;
	while(next!=NULL)
	{
		printf("%s\n",next->word);
		next=next->next;
	}
}

int eva(char *str,int i)
{	
	int k;
	if(strlen(str)<i+1)k=0;
	else if(str[i]==' ')k=27;
		 else k=str[i]-'a'+1;
	return k;
}

void bsort(struct node_type** ThisList,int r,int d)
{
	struct node_type *p,*t,*pp,*tt,*head[MaxR],*tail[MaxR];
	int i,j,k,k1,ks;
	char *q;

	p=*ThisList;
	pp=NULL;
	i=0;
	while(i<d)
	{
		for(j=0;j<r;j++)
		{
			head[j]=NULL;
			tail[j]=NULL;
		}
		while(p!=NULL)
		{
			q=p->word;
			if(i>0)
			{
				k1=eva(q,i-1);
				if(k1!=ks)
				{
					ks=k1;
					break;
				}
			}
			k=eva(q,i);
			if(head[k]==NULL)
			{
				head[k]=p;
				tail[k]=p;
			}
			else
			{
				tail[k]->next=p;
				tail[k]=p;
			}
			p=p->next;
		}
		for(j=0;j<r;j++)
			if(head[j]!=NULL)
			{
				if(pp==NULL)
				{
					pp=head[j];
					tt=tail[j];
				}
				else
				{
					tt->next=head[j];
					tt=tail[j];
				}
			}
		tt->next=NULL;
		if(p==NULL)
		{
			p=pp;
			t=tt;
			pp=NULL;
			ks=eva(p->word,i);
			i++;
		}
	}
	*ThisList=p;
}
