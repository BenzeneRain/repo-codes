#include<stdio.h>
#include<string.h>

int data[30][4];
int count[30];
int n,kind,finish,num;
int arr[30];

void init();
void solve(int x);
void print(int i);

int main(){
	num=1;
	scanf("%d",&n);
	while(n!=0){
		if(num!=1)printf("\n");
		init();
		solve(0);
		print(num);
		scanf("%d",&n);
		num++;
	}
	return 0;
}

void init(){
int datatemp[4];
int i,j,modify;
	memset(count,0,sizeof(count));
	memset(arr,0,sizeof(arr));
	kind=0;finish=0;
	for(i=0;i<n*n;i++){
		modify=0;
		scanf("%d%d%d%d",&datatemp[0],&datatemp[1],&datatemp[2],&datatemp[3]);
		for(j=0;j<kind;j++)
			if(datatemp[0]==data[j][0]
			&&datatemp[1]==data[j][1]
			&&datatemp[2]==data[j][2]
			&&datatemp[3]==data[j][3]){
				count[j]++;
				modify=1;
				break;
			}
		if(!modify){
			data[kind][0]=datatemp[0];
			data[kind][1]=datatemp[1];
			data[kind][2]=datatemp[2];
			data[kind][3]=datatemp[3];
			count[kind]++;
			kind++;
		}
	}
}

void solve(int x){
register int i;
	for(i=0;i<kind;i++)
		if(count[i] &&(x%n==0 || data[i][3]==data[arr[x-1]][1])&&(x/n==0 || data[i][0]==data[arr[x-n]][2])){
		count[i]--;
		arr[x]=i;
		if(x==n*n-1){finish=1;return;}
			else solve(x+1);
		arr[x]=0;
		count[i]++;
		if(finish)return;
	}
}

void print(int i){
	printf("Game %d: ",i);
	if(finish)printf("Possible\n");
		else printf("Impossible\n");
}