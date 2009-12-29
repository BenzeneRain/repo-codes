#include <stdio.h>
#include <memory.h>

const unsigned long long mask[16] = {0x1, 0x2, 0x4, 0x8,
									 0x10,0x20, 0x40, 0x80,
									 0x100, 0x200, 0x400, 0x800,
									 0x1000, 0x2000, 0x4000, 0x8000};

typedef struct
{
	unsigned long long state[20000];
	long num;
}state_t;

int timeUse[5][310];
state_t *cur_state, *pre_state, *tmp_state;
state_t pool1, pool2;
int count;
unsigned long long cs;
int minTime[20000] = {0};

int getSolver(unsigned long long);
int makeState(unsigned long long *, unsigned long long, int, int);

int main()
{
	int caseNum;
	int n;
	int i, j, k, cur_prob;
	int ret;
	int cur_time;
	int flag;

	scanf("%d", &caseNum);
	while(caseNum --)
	{
		scanf("%d", &n);	
		for(i = 0; i < 3; i ++)
			for(j = 0; j < n; j ++)
				scanf("%d", &timeUse[i][j]);


		cur_state = &pool1;
		pre_state = &pool2;
		memset(cur_state, 0, sizeof(state_t));
		memset(pre_state, 0, sizeof(state_t));
		memset(minTime, 0, sizeof(minTime));

		count = 0;

		while(cur_state -> num >= 0)
		{
			tmp_state = pre_state;
			pre_state = cur_state;
			cur_state = tmp_state;

			cur_state -> num = -1;
			flag = 0;
			for(i = 0; i <= pre_state -> num; i ++)
			{
				j = getSolver(pre_state -> state[i]);
				for(cur_prob = 0; cur_prob < n; cur_prob ++)
					for(k = 1; k <= 3; k ++)
					{
						if(j == k) continue;
						ret = makeState(&cs, pre_state -> state[i], cur_prob, k);
						if(ret == -1) break;
						cur_time = minTime[pre_state -> state[i]] + timeUse[k - 1][cur_prob];
						if(minTime[cs] == 0 && cur_time <=280)
						{
							minTime[cs] = cur_time;
							cur_state -> num ++;
							cur_state -> state[cur_state -> num] = cs;
							flag = 1;
						}
						else if(cur_time < minTime[cs])
						{
							minTime[cs] = cur_time;
							flag = 1;
						}
					}
			}
			if(flag) count ++;

		}
		printf("%d\n", count);
	}
	return 0;
}

int getSolver(unsigned long long state)
{
	int who;

	who = (int)(state & 0x3);
	return who;
}

int makeState(unsigned long long *new_state, unsigned long long old_state, int prob, int person)
{
	int loc = prob + 2;

	if((old_state & mask[loc]) == mask[loc]) return -1;

	*new_state = ((old_state | mask[loc]) & (~(0x3ULL))) | person;
	return 0;
}
