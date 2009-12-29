#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

void init();
void solve();
void print();
void dfs();
void pop1();//stack to word
void pop2();//new to stack
void push1();//word to stack
void push2();//stack to new

//int target_hash[26]={0},word_hash[26]={0};
char word[100],target[100],new_word[100],stack[101],order[200];
int top,key,word_key,new_key,order_num;

int main(){
  int i;
  i=0;
//  freopen("zju1004.in","r",stdin);
  while(!feof(stdin)){
  init();
//  if(i)printf("\n[\n");
//	else printf("[\n");
  solve();
  printf("]\n");
  i++;
  }
  return 0;
}

void init(){
  memset(new_word,NULL,sizeof(new_word));
  memset(stack,NULL,sizeof(stack));
  memset(order,NULL,sizeof(order));
  memset(word,NULL,sizeof(word));
  memset(target,NULL,sizeof(target));
  scanf("%s",word);
  scanf("%s",target);
//  gets(word);
//  gets(target);
 if(word[0]==NULL&&target[0]==NULL) exit(0);
  printf("[\n");
//stack
  top=-1;
//pointers
  word_key=0;
  new_key=-1;
  order_num=-1;
}

void solve(){
//char *p;
int i;
//check whether two seq have the same elements
  key=1;
  if(strlen(word)==strlen(target)){
/*  p=word;
  while(*p){
	 word_hash[toupper(*p)-65]++;
	 p++;
	 }
  p=target;
  while(*p){
	 target_hash[toupper(*p)-65]++;
	 p++;
	 }
  key=1;
  for(i=0;i<26;i++)
	if(word_hash[i]!=target_hash[i]){
	 key=0;
	 break;
	 }*/
//key=1 then solve, key=0 then return null
  if(key) dfs();
  };
}

void dfs(){
  if(!word_key){
	push1();
	dfs();
	pop1();
	}
	 else{
		 if(word_key!=strlen(word)){
		   push1();
		   dfs();
		   pop1();
		   }
		 if(top>=0){
		   pop2();
		   if((top==-1)&&(new_key==strlen(target)-1)&&
			  (!strcmp(new_word,target)))
			  print();
			  else dfs();
		   push2();
		   }
		 }
}

void print(){
int i;
  for(i=0;i<=strlen(target)*2-2;i++)
	printf("%c ",order[i]);
  printf("%c \n",order[strlen(target)*2-1]);
}

void push1(){
  top++;
  stack[top]=word[word_key];
  order_num++;
  order[order_num]='i';
  word_key++;
}

void pop1(){
  stack[top]=NULL;
  order[order_num]=NULL;
  order_num--;
  word_key--;
  top--;
}

void pop2(){
  new_key++;
  new_word[new_key]=stack[top];
  stack[top]=NULL;
  top--;
  order_num++;
  order[order_num]='o';
}

void push2(){
  top++;
  stack[top]=new_word[new_key];
  new_word[new_key]=NULL;
  new_key--;
  order[order_num]=NULL;
  order_num--;
}

