#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>

struct page_desc
{
	int page_number;
	int block_number;
};
typedef struct page_desc page_desc_t;

struct page_dir
{
	int pg_num;
	page_desc_t *pg_item;
};
typedef struct page_dir page_dir_t;

struct pcb_struct
{
	char *name;
	int proc_id;
	page_dir_t *pg_entry;

	struct pcb_struct *next;
	struct pcb_struct *prev;
};
typedef struct pcb_struct pcb_struct_t; 

//typedef unsigned char uint8_t;
//typedef unsigned uint32_t;

uint8_t bitmap[8];
int blk_left;
pcb_struct_t *pcb_head, *pcb_tail;
uint32_t proc_count;

int init();
int getInput();
int disp_current_procs();
int disp_current_bitmap();
int disp_spec_proc_pg_table();
pcb_struct_t* find_proc_by_id(int);

int main()
{
	init();
	while(getInput() != 0);
	return 0;
}

int init()
{
	memset(bitmap, 0, sizeof(bitmap));	
	blk_left   = 64;
	pcb_head   = NULL;
	pcb_tail   = NULL;
	proc_count = 0;
	return 0;
}

int getInput()
{
	char choice;
	char name[64];
	char flusher[1024];
	int size;
	int i, j, k;
	int ii;
	int temp;
	pcb_struct_t *this_pcb;
disp:

	printf("\nThere are %d free blocks of memory left!\n", blk_left);
	printf("1 --- Insert a process into memory\n");
	printf("2 --- Remove a process from memory\n");
	printf("3 --- Display current processes in memory\n");
	printf("4 --- Display current bitmap\n");
	printf("5 --- Display page_table of a specific process\n");
	printf("6 --- Exit\n");
	printf("Select your choice:");
	
	scanf("%s", flusher);
	if( strlen(flusher) != 1)
	{
		printf("\n");
		goto disp;
	}

	choice = flusher[0];

	switch(choice)
	{
		case '1':
			{
				printf("\nPlease input the process's name(less than 64 chars):");
				scanf("%s", name);
retry:				
				printf("Please input the process's size(larger than 0):");
				scanf("%d", &size);
				
				if(size <= 0)
				{
					printf("Invalid mount of memory requested!\n");
					goto retry;
				}
				if(blk_left < size)
				{
					printf("Not enough memory to allocate, only %d left\n", blk_left);
					break;
				}

				blk_left = blk_left - size;
				this_pcb = (pcb_struct_t *)malloc(sizeof(pcb_struct_t));
				this_pcb -> name     = (char *) malloc(strlen(name));
				strncpy(this_pcb -> name, name, strlen(name));
				this_pcb -> pg_entry = (page_dir_t *)malloc(sizeof(page_dir_t));
				this_pcb -> pg_entry 
					 -> pg_num   = size;
				this_pcb -> pg_entry 
					 -> pg_item  = (page_desc_t *)malloc(sizeof(page_desc_t) * size);
				this_pcb -> next     = NULL;
				this_pcb -> prev     = NULL;
				this_pcb -> proc_id  = proc_count ++;
				
				ii = 0;
				for(k = 0; k < size; k++)
				{
					for(i = ii; i < 8; i++)
					{
						if(bitmap[i] == 0xff)
							continue;
						
						temp = bitmap[i];
						j = 0;
						while( j < 8 && (temp & 0x1)!=0)
						{
							temp = temp >> 1;
							j ++;
						}
						if(j < 8)
							break;	
					}

					this_pcb -> pg_entry
						 -> pg_item[k]
						 .  page_number = k;
					this_pcb -> pg_entry
						 -> pg_item[k]
						 .  block_number  = i*8 + j;
					bitmap[i] |= (1<<j);

					ii = i;
				}
				
				

				if(pcb_head == NULL)
				{
					pcb_head = this_pcb;
					pcb_tail = this_pcb;
				}
				else
				{
					pcb_tail -> next = this_pcb;
					this_pcb -> prev = pcb_tail;
					pcb_tail = this_pcb;
				}

				break;
			}
		case '2':
			{
				disp_current_procs();
				do
				{
					printf("Which one(id) do you want to remove(-1 to return)?:");
					scanf("%d", &i);
				}while( i != -1 && (this_pcb = find_proc_by_id(i)) == (pcb_struct_t *)NULL );

				if( i == -1)
					break;
				ii = this_pcb -> pg_entry 
					      -> pg_num;

				for( i = 0; i< ii; i++)
				{
					j = this_pcb -> pg_entry
						     -> pg_item[i]
						     .  block_number / 8;
					k = this_pcb -> pg_entry
						     -> pg_item[i] 
						     .  block_number % 8;
					bitmap[j] ^= (1<<k);
				}

				blk_left += this_pcb -> pg_entry 
					             -> pg_num;

				free(this_pcb -> pg_entry -> pg_item);
				free(this_pcb -> pg_entry);

				if( this_pcb == pcb_head)
				{
					pcb_head = this_pcb -> next;
					free(this_pcb);
				}
				else if( this_pcb == pcb_tail)
					{
						pcb_tail = pcb_tail -> prev;
						free(this_pcb);
					}
					else
					{
						this_pcb -> next 
							 -> prev = this_pcb -> prev;
					        this_pcb -> prev 
							 -> next = this_pcb -> next;
						free(this_pcb);	
					}
				break;
				printf("There are %d free blocks of memory left!\n", blk_left);
			}
		case '3':
			{
				disp_current_procs();
				break;
			}
		case '4':
			{
				printf("\nThere are %d free blocks of memory left!\n", blk_left);
				disp_current_bitmap();
				break;
			}
		case '5':
			{
				printf("\n");
				disp_current_procs();
				printf("\n");
				disp_spec_proc_pg_table();
				break;
			}
		case '6':
			{
				return 0;
				break;
			}
		default:
			{
				printf("\n");
				return 2;
			}

	}
	while(getchar()!='\n');
	return 1;
}

int disp_current_procs()
{
	pcb_struct_t *this;

	printf("\nCurrent Processes:\n");
	this = pcb_head;
	if( this == NULL )
		printf("No process exists at the moment!\n");
	else	
	{
		while( this != NULL)
		{
			printf("Process id %d, name %s, occupies %d blocks of memory.\n",
				this->proc_id, this->name, this->pg_entry->pg_num);
			this = this -> next;
		}
	}
	return 0;
}

pcb_struct_t* find_proc_by_id(int id)
{
	pcb_struct_t *this;
	
	this = pcb_head;
	while( this != (pcb_struct_t *)NULL &&(this -> proc_id) != id) 
		this = this -> next;
	return this;
}

int disp_current_bitmap()
{
	int i, j, temp;

	printf("\nCurrent Bitmap:\n");
	printf("\t0\t1\t2\t3\t4\t5\t6\t7\n");
	for(i = 0; i < 8; i++)
	{
		printf("%d", i);
		temp = bitmap[i];
		for(j = 0; j < 8; j++)
		{
			printf("\t%d", (temp & 0x1));
			temp = temp >> 1;
		}
		printf("\n");
	}
	return 0;
}

int disp_spec_proc_pg_table()
{
	int i;
	pcb_struct_t* this_pcb;

	do
	{
		printf("Which one(id) do you want to display(-1 to return)?:");
		scanf("%d", &i);
	}while( i != -1 && (this_pcb = find_proc_by_id(i)) == (pcb_struct_t *)NULL );

	if( i == -1)
		return 0;
	if( this_pcb == (pcb_struct_t *)NULL)
	{
		printf("There no process with id equals %d\n", i);
		return 1;
	}
	printf("\tPage_Number\tBlock_Number\n");
	for(i = 0; 
	    i < this_pcb -> 
	        pg_entry ->
		pg_num;
	    i ++)
	{
		printf("\t%d\t\t%d\n", 
			this_pcb ->
			pg_entry ->
			pg_item[i].
			page_number,
			this_pcb ->
			pg_entry ->
			pg_item[i].
			block_number);
	}
	return 0;
}
