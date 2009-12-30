#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MaxN 20

struct BTree
{
	char value;
	struct BTree *lchild,*rchild;
};

struct BTree* Partition(char *,int,int);
int GetExpression(char *,int *);
void InOrderTravel(struct BTree *);
void PreOrderTravel(struct BTree *);
void PostOrderTravel(struct BTree *);

int main()
{
	int len=0;
	char exp[MaxN];
	struct BTree *root;

	GetExpression(exp,&len);
	root=Partition(exp,0,len-1);
	printf("\n前缀表达式:");
	PreOrderTravel(root);
	printf("\n中缀表达式:");
	InOrderTravel(root);
	printf("\n后缀表达式:");
	PostOrderTravel(root);
	printf("\n");
	return 0;
}

int GetExpression(char *ThisExp,int *n)
{
	scanf("%s",ThisExp);
	*n=(int)strlen(ThisExp);
	return 0;
}

struct BTree* Partition(char *ThisExp,int start,int end)
{
	int i,j;
	struct BTree* CurrentNode;

	i=start;
	j=end;
	CurrentNode=(struct BTree*)malloc(sizeof(BTree));

	if(i==j)//deal with the number node
	{
		CurrentNode->value=ThisExp[j];
		CurrentNode->lchild=NULL;
		CurrentNode->rchild=NULL;
		return CurrentNode;
	}

	while(i<j && ThisExp[j]!='+' && ThisExp[j]!='-')j--;//deal with the + and - signs
	if(ThisExp[j]=='+' || ThisExp[j]=='-')
	{
		CurrentNode->value=ThisExp[j];
		CurrentNode->lchild=Partition(ThisExp,start,j-1);
		CurrentNode->rchild=Partition(ThisExp,j+1,end);
		return CurrentNode;
	}

	i=start;
	j=end;
	while(i<j && ThisExp[j]!='*' && ThisExp[j]!='/')j--;//deal with the * and / signs
	if(ThisExp[j]=='*' || ThisExp[j]=='/')
	{
		CurrentNode->value=ThisExp[j];
		CurrentNode->lchild=Partition(ThisExp,start,j-1);
		CurrentNode->rchild=Partition(ThisExp,j+1,end);
		return CurrentNode;
	}
	else
	{
		free(CurrentNode);
		printf("/nError/n");
		exit(0);
	}
}

void InOrderTravel(struct BTree * Point)
{
	if(Point->lchild!=NULL)InOrderTravel(Point->lchild);
	printf("%c",Point->value);
	if(Point->rchild!=NULL)InOrderTravel(Point->rchild);
}

void PreOrderTravel(struct BTree *Point)
{
	printf("%c",Point->value);	
	if(Point->lchild!=NULL)PreOrderTravel(Point->lchild);
	if(Point->rchild!=NULL)PreOrderTravel(Point->rchild);
}

void PostOrderTravel(struct BTree *Point)
{
	if(Point->lchild!=NULL)PostOrderTravel(Point->lchild);
	if(Point->rchild!=NULL)PostOrderTravel(Point->rchild);
	printf("%c",Point->value);	
}