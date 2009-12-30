#include<stdio.h>


#define MAXI 10
#define MAXN 100

typedef struct
{
	int key;
	int link;
}IdxType;

typedef IdxType IDX[MAXI];

typedef struct
{
	int LastBlockSize;
	int AvgBlockSize;
	int BlockNum;
}IdxTypeInfo;

int ConstructRecordTable(int *);
int PartitionRecordTable(IdxType*,int *,int,IdxTypeInfo*);
int IdxSearch(IdxType *,int *,int,IdxTypeInfo);
int Work(IdxType *,int *,int,IdxTypeInfo);

int main()
{
	int Record[MAXN];
	int RecordNum;
	IDX Index;
	IdxTypeInfo IndexInfo;
	RecordNum=ConstructRecordTable(Record);
	PartitionRecordTable(Index,Record,RecordNum,&IndexInfo);
	Work(Index,Record,RecordNum,IndexInfo);
	return 0;
}

int ConstructRecordTable(int *RList)
{
	int Data;
	int Count;
	FILE *fin;

	fin=fopen("data.txt","r");

	Count=0;
	while(!feof(fin))
	{
		fscanf(fin,"%d",&Data);
		RList[Count++]=Data;
	}
	fclose(fin);
	return Count;
}

int PartitionRecordTable(IdxType *Index,int *RList,int RecNum,IdxTypeInfo *IdInfo)
{
	int i,j,max;
	IdInfo->AvgBlockSize=5;
	IdInfo->BlockNum=5;
	IdInfo->LastBlockSize=5;
	for(i=0;i<IdInfo->BlockNum;i++)
	{
		Index[i].link=i*5;
		max=-1;
		for(j=i*5;j<(i+1)*5;j++)
			if(max<RList[j])
				max=RList[j];
		Index[i].key=max;
	}
	return 0;
}

int IdxSearch(IdxType *Index,int *RList,int RecNum,int key,IdxTypeInfo IdInfo)
{
	int place;
	int high,low,mid;
	int i;
	int SearchLimit;

	high=IdInfo.BlockNum-1;
	low=0;

	while(low<high)
	{
		mid=(high+low)/2;
		if(Index[mid].key>=key)
			high=mid;
		else
			low=mid+1;
	}
	i=low;
	if(i<IdInfo.BlockNum)
	{
		SearchLimit =(i==IdInfo.BlockNum-1) ? IdInfo.LastBlockSize : IdInfo.AvgBlockSize;
		i=Index[i].link;
		SearchLimit += i;
		while(RList[i] != key && i<=SearchLimit)i++;
		if(RList[i] == key)
			place=i;
		else
			place=-1;
	}
	else
		place=-1;
	return place;
}

int Work(IdxType *Index,int *RList,int RecNum,IdxTypeInfo IdInfo)
{
	int key;
	int place;
	while(printf("\n�������������ֵ(����0����):"),scanf("%d",&key),key!=0)
		if((place=IdxSearch(Index,RList,RecNum,key,IdInfo))==-1)
			printf("δ�ҵ���������ֵ%d\n",key);
		else
			printf("���ҵ���������ֵ%d,�����Ϊ%d\n",key,place);
	return 0;
}