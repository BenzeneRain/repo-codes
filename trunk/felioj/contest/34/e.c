#include<stdio.h>
#include<memory.h>

#define _getbit(x,i) (((x) & mask[(i)]) >> (i))  

#define _setbit(x,i,value)      \
do                              \
{                               \
    if((value) == 0)            \
    {                           \
        (x) &= (~mask[(i)]);    \
    }                           \
    else                        \
    {                           \
        (x) |= (mask[(i)]);     \
    }                           \
}while(0)

#define _testbit(x,i) (((x) & mask[(i)]) == 0 ? 0 : 1)

const int mask[] = {0x1,   0x2,   0x4,   0x8, 
                    0x10,  0x20,  0x40,  0x80, 
		    0x100, 0x200, 0x400, 0x800};

typedef struct
{
	int state[5200];
	int num;
}state_t;


int f[5][5200][301];
int state_map[5200];
int timeUse[5][301];
int timeUseMin[301];
state_t state_pool1, state_pool2;

void qsort(int, int);

int main()
{
	int caseNum;
	int ii, jj, kk, tt;
	int temp;
	int n;
	int maxInside, pre_s, cur_prob;
	int tempprob;
	int flag;
	int glbMax;
	int count;
	state_t *state_pre;
	state_t *state_cur;
	state_t *state_tmp;

	scanf("%d", &caseNum);

	while(caseNum --)
	{
		scanf("%d", &n);
		for(ii = 0; ii < n; ii ++)
		{
			timeUseMin[ii] = 512;
		}

		for(ii = 0; ii < 3; ii ++)
		{
			for(jj = 0; jj < n; jj ++)
			{
				scanf("%d", &timeUse[ii][jj]);
				timeUseMin[jj] = timeUseMin[jj] < timeUse[ii][jj] ? 
						 timeUseMin[jj] : timeUse[ii][jj];
			}
		}

		qsort(0, n-1);
		state_pre = &state_pool1;
		state_cur = &state_pool2;

		memset(f, 0, sizeof(f));
		memset(state_pre, 0, sizeof(state_t));
		memset(state_cur, 0, sizeof(state_t));

		state_cur -> num = 0;
		glbMax = 0;
		count = -1;
		memset(state_map, 0, sizeof(state_map));

		while(state_cur -> num >= 0)
		{
			count ++;
			if(count == n)break;
			state_tmp = state_pre;
			state_pre = state_cur;
			state_cur = state_tmp;
			state_cur -> num = -1;
			for(jj = 0; jj <= (state_pre -> num); jj ++)
			{
				for(tt = 280; tt >= 0; tt --)
					for(kk = 1; kk <= 3; kk ++)
					{
						flag = 0;
						maxInside = count;
						for(cur_prob = 0; cur_prob < n; cur_prob ++)
						{
							if(tt < timeUseMin[cur_prob]) break;
							if(timeUse[kk-1][cur_prob] > tt) continue;
							if(_testbit((state_pre -> state[jj]), cur_prob) == 1)
								continue;
							for(ii = 1; ii <= 3; ii ++)
							{
								if(((state_pre -> state[jj]) != 0) &&
								   (ii == kk)) 
								   continue;
								temp = f[ii][state_pre -> state[jj]]
								        [tt - timeUse[kk-1][cur_prob]] + 1;
								if(temp > maxInside)
								{
									maxInside = temp;
									pre_s     = state_pre ->
									            state[jj];
									tempprob  = cur_prob;
									flag = 1;
								}
							}
						}
						if(flag == 1)
						{
							_setbit(pre_s, tempprob, 1);
							f[kk][pre_s][tt] = maxInside;
							if( maxInside > glbMax) glbMax = maxInside;

							if( !state_map[pre_s])
							{
								state_cur -> num ++;
								state_cur -> state[state_cur -> num] = pre_s;
								state_map[pre_s] = 1;
							}
						}
					}
			}
		}

		printf("%d\n", glbMax);
	}
	return 0;
}

void qsort(int st, int end)
{
	int tmp[3];
	int tum;
	int ii, jj, kk;

	ii = st;
	jj = end;
	for(kk = 0; kk < 3; kk ++)
	{
		tmp[kk] = timeUse[kk][st];
	}
	tum = timeUseMin[st];

	while(ii < jj)
	{
		while(ii < jj && timeUseMin[ii] <= timeUseMin[jj]) jj --;
		if(ii < jj)
		{
			for(kk = 0; kk < 3; kk ++)
			{
				timeUse[kk][ii] = timeUse[kk][jj];
			}
			timeUseMin[ii] = timeUseMin[jj];
			ii ++;
		}
		while(ii < jj && timeUseMin[ii] >= timeUseMin[jj]) ii ++;
		if(ii < jj)
		{
			for(kk = 0; kk < 3; kk ++)
			{
				timeUse[kk][jj] = timeUse[kk][ii];
			}
			timeUseMin[jj] = timeUseMin[ii];
			jj --;
		}
	}

	for(kk = 0; kk < 3; kk ++)
	{
		timeUse[kk][ii] = tmp[kk];
	}
	timeUseMin[ii] = tum;

	if(st != ii)qsort(st, ii);
	if(end != jj)qsort(jj+1, end);
}
