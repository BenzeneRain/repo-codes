#include <stdio.h>
#include <string.h>

#define FLAG 'F'

char board[25][25];
int sizen,sizem;
int caseamt;

int main()
{
	int ii,jj,crtcase;
	int count;
	int minenum;
	int flag;
	char temp[25];

	scanf("%d", &caseamt);
	crtcase = 0;
	while( crtcase < caseamt)
	{
		memset(board, 0, sizeof(board));
		memset(temp, 0 , sizeof(temp));
		scanf("%d %d", &sizen, &sizem);
		for( ii = 1; ii <= sizen; ii ++)
		{
			scanf("%s", temp);
			for(jj = 1; jj <= sizem; jj ++)
				board[ii][jj]=temp[jj - 1];
		}
	
		flag = 0;
		minenum = 0;
		for( ii = 1; ii <= sizen; ii ++)
		{
			if(flag) break;
			for( jj = 1; jj <= sizem; jj ++)
			{
				if(board[ii][jj] == FLAG)
				{
					minenum ++;
					continue;
				}
				count = 0;
				if( board[ii - 1][jj - 1] == FLAG) count ++;
				if( board[ii - 1][jj] == FLAG) count ++;
				if( board[ii - 1][jj + 1] == FLAG) count ++;
				if( board[ii][jj - 1] == FLAG) count ++;
				if( board[ii][jj + 1] == FLAG) count ++;
				if( board[ii + 1][jj - 1] == FLAG) count ++;
				if( board[ii + 1][jj] == FLAG) count ++;
				if( board[ii + 1][jj + 1] == FLAG) count ++;

				if(count != (board[ii][jj] - '0'))
				{
					flag = 1;
					break;
				}
				
			}
		}

		if(minenum == (sizem*sizen))
			flag = 1;
		if(flag)
		{
			printf("Please sweep the mine again!\n");
		}
		else
		{
			printf("Well done Clark!\n");
		}

		crtcase ++;
	}
	return 0;
}
