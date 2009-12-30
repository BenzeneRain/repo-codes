#include<stdio.h>
#include<time.h>
#include<sys/time.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>

/*
 *pcb_struct_t
 * status indicates the status of specific process:
 * 0---Wait
 * 1---Run
 * 2---End
 */

struct pcb_struct
{
	char   PName[32];
	struct pcb_struct *next;
	struct pcb_struct *prev;
	int    time_required;
	int    time_used;
	int    status;
};
typedef struct pcb_struct pcb_struct_t;

/*
 * timeslice is measured in microseconds
 * the default value is 10
 */
int timeslice = 10;
/*
 *  proc_ret indicates why current process exits
 *  0 --- time slice has been used up
 *  1 --- current process has been finished
 */
int proc_ret  = 0;
pcb_struct_t *head;

int sched();
void timeup(int);
int init();

int main()
{
	init();
	sched();
	printf("All processes have finished working!\n");
	return 0;
}

int init()
{
	FILE *fin;
	pcb_struct_t *current = head;
	pcb_struct_t *prev    = head;
	struct sigaction act;

	head    = (pcb_struct_t *) malloc(sizeof(pcb_struct_t));
	current = head;
	prev    = head;
        fin = fopen("processes.txt", "r");
	fscanf(fin, "%d", &timeslice);
	while(!feof(fin))
	{
		current = (pcb_struct_t *) malloc(sizeof(pcb_struct_t));
		if( fscanf(fin, "%s", current->PName) == EOF)
		{
			free(current);
			break;
		}
		fscanf(fin, "%d", &current->time_required);
		current->status    = 0;
		current->time_used = 0;

		current->next      = head;
	        current->prev      = prev;
		prev   ->next      = current;
		head   ->prev      = current;
	        prev               = current;	
	}

	head->prev->next = head->next;
	head->next->prev = head->prev;

	fclose(fin);

	//set alarm handler
	memset(&act, 0, sizeof(act));
	act.sa_handler = timeup;
	sigaction(SIGALRM, &act, NULL);
	
	return 0;
}

int sched()
{
	pcb_struct_t *current = head->next;
	pcb_struct_t *prev    = head->next;
	struct itimerval tstart;
	struct itimerval tstop;

	memset(&tstart, 0, sizeof(struct itimerval));
	memset(&tstop,  0, sizeof(struct itimerval));
	tstart.it_interval.tv_usec = timeslice;
	tstart.it_value.tv_usec    = timeslice;
	tstop .it_interval.tv_usec = 0;
	tstop .it_value.tv_usec = 0;
	
	setitimer(ITIMER_REAL, &tstop, NULL);
	while(current != NULL)
	{
		proc_ret = -1;
//	        __asm__ volatile ("cli");	
		current->status = 1;
		printf("Process %s begins to run!\n", current->PName);
		setitimer(ITIMER_REAL, &tstart, NULL);
//		__asm__ volatile ("sti");

		//simulate process running using a stupid loop stub ...
		while( proc_ret < 0)
		{
			/*
			 * the real process should return if it is finished
			 * then the proc_ret should be set to 1
			 */
		}
//		__asm__ volatile ("cli");
		setitimer(ITIMER_REAL, &tstop, NULL);

		if( proc_ret == 0 &&
		    (current->time_used + 
		    timeslice) >= 
		    current->time_required)
		{
			proc_ret = 1;
		}

		switch(proc_ret)
		{
			case 0:
			{
				current->status = 1;
				printf("Process %s has used up its time slice! So begins to wait!\n\n", current->PName);
 				
				current->time_used += timeslice;

				prev    = current;
				current = current->next;

				break;
			}

			case 1:
			{
				current->status = 2;
				printf("Process %s has been finished!\n\n", current->PName);
				
				current->prev->next = current->next;
				current->next->prev = current->prev;
				
				prev    = current;
				current = current->next;
				free(prev);
				if( current == prev ) current = NULL;	
				break;
			}

			default:
			{
				printf("Anormaly proc_ret %d from process %s\n", proc_ret, current->PName);
				printf("Sched_timeslice exit!!!\n");
				exit(1);
			}
		}
//		__asm__ volatile ("sti");
	}	
	
	
}

void timeup(int signum)
{
	proc_ret = 0;
	return ;
}
