#include<stdio.h>
#include<stdlib.h>

#define LEN 500000
//#define DEBUG
typedef struct{
  int x,y;
  int distance;
  int direction[2];
} node;

node queue[LEN];
int head,tail;

int now[2],end[2];

node cur,ext;

int dis[25][25][4];
int visited[25][25][4];
char maze[25][25];

int enqueue(node N)
{
  queue[tail]=N;
  tail=(tail+1)%LEN;     
  return 0;
}

int dequeue()
{
  cur=queue[head];
  head=(head+1)%LEN; 
  return 0;
}

int empty()
{
  if (head==tail)
  	return 1;
  else
  	return 0;
}

int move(int dir)
{

  switch(dir)
  {
    case 0:  // up
         ext.x=cur.x-1;
         ext.y=cur.y;
         break;
    case 1:  // right
         ext.x=cur.x;
         ext.y=cur.y+1;
         break;     
    case 2: //down
         ext.x=cur.x+1;
         ext.y=cur.y;
         break;           
    case 3:  //left
         ext.x=cur.x;
         ext.y=cur.y-1;
         break;        
  }
 
  ext.distance=cur.distance+1;
  ext.direction[0]=dir;
  ext.direction[1]=(dir+1)%4;   
     
  return 0;
}

int legal(node ext, int dir)
{
  if(maze[ext.x][ext.y]=='X')
    return 0;
   
  if(visited[ext.x][ext.y][dir]==1 && dis[ext.x][ext.y][dir]<=ext.distance)
    return 0;
 
  return 1;
}


int main()
{
  int n,row,col,i,j,k;
 
  scanf("%d",&n);
 
L: while(n--)
  {   
    scanf("%d%d",&row,&col);
         
    for(i=0;i<row;i++)
      {
         while(getchar() != 'X');
	 ungetc('X', stdin);
         for(j=0;j<col;j++)
          {
             scanf("%c", &maze[i][j]);
             if(maze[i][j]=='S')
               {now[0]=i;now[1]=j;/*printf("S %d %d\n",i,j);*/}
             else
               if(maze[i][j]=='F') 
               {end[0]=i;end[1]=j;/*printf(" F %d %d\n",i,j);*/}


             for(k=0;k<4;k++)
               {
                 visited[i][j][k]=0;
                 dis[i][j][k]=100000;
               }
              
          }
	  #ifdef DEBUG
	  printf("%s\n", maze[i]);
	  #endif
     
      }
   

    cur.distance=0;

    cur.x=now[0];
    cur.y=now[1];
 
    for(k=0;k<4;k++)
      dis[cur.x][cur.y][k]=0;
   
    head=tail=0;

   
    for(i=0;i<4;i++)
    {
      move(i);
      if( legal(ext,i) )
      {
        dis[ext.x][ext.y][i]=ext.distance;  // update the distance matrix
        if((ext.x==end[0]) && (ext.y==end[1]))
          {printf("1\n");goto L;}
       
        visited[ext.x][ext.y][i]=1;
        enqueue(ext);   
      }
    }
   
   
    while(!empty())
    {
      dequeue();
     
      for(i=0;i<2;i++)
      {
        move(cur.direction[i]);
        if( legal(ext,cur.direction[i]) )
          {
            if(ext.x==end[0] && ext.y==end[1])
               {printf("%d\n",ext.distance); dis[ext.x][ext.y][cur.direction[i]]=ext.distance;goto L;}
             
            dis[ext.x][ext.y][cur.direction[i]]=ext.distance;  // update the distance matrix
           
            visited[ext.x][ext.y][cur.direction[i]]=1;
            enqueue(ext);
          }


      }                  
   
    }
   
    int min=100000;
    for(k=0;k<4;k++)
      min=min>dis[end[0]][end[1]][cur.direction[k]] ? dis[end[0]][end[1]][cur.direction[k]]:min;
   
    printf("%d\n",min);

  }
 
   
  return 0;
}
