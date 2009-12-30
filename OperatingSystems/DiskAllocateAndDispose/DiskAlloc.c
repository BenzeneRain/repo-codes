#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>

int DiskSize, BlkSize, BlkinGrp;
int GrpQuan, LeftDiskSize;
int *EmuDisk, *MA;

void init();
void work();
void dispose();
int *FindBlkAddr(int);
int DisposeBlk(int);
int AllocateDisk(int);
void DispFreeSpace();
int FindFreeBlk(int);

int main()
{
    init();
    work();
    dispose();
    return 0;
}


void init()
{
    int i;
    
    printf("Please input the size of the disk in blocks:");
    scanf("%d", &DiskSize);
    
    printf("Please input the size of each block(>=3):");
    scanf("%d", &BlkSize);
    
    if(BlkSize < 3)
    {
	printf("Invalid Value!\n");
	exit(1);
    }
    BlkinGrp= BlkSize - 1;
    
    EmuDisk = (int *)malloc(sizeof(int) * (DiskSize + 1) * BlkSize);
    MA      = FindBlkAddr(1);
    
    GrpQuan = 1;
    LeftDiskSize = 0;
    
    MA      = FindBlkAddr(0);
    MA[0]   = 1;
    MA[1]   = 0;
    
    for(i = DiskSize; i >= 1; i--)
    {
        DisposeBlk(i);
    }
    
}   

void dispose()
{
    free(EmuDisk);
}

int *FindBlkAddr(int blknum)
{
    if(blknum < 0)
    {
        return NULL;
    }
    else
    {    
        return EmuDisk + (blknum) * BlkSize;
    }    
}    

int DisposeBlk(int blknum)
{
    int i,j;
    int *Aj;
    
    j = blknum;
    
    if(MA[0] < BlkinGrp)
    {
	MA[0] = MA[0] + 1;
        i = MA[0];
        MA[i] = j;    
        LeftDiskSize ++;
    }   
    else
    {
        Aj = FindBlkAddr(j);
        memcpy(Aj, MA, sizeof(int) * BlkSize);
	memset(MA, 0, sizeof(int) * BlkSize);
        MA[0] = 1;
        MA[1] = j;
	GrpQuan ++;
    }

}    

int AllocateDisk(int blkquan)
{
    int i, j, s;
    int *As, *A0;
    
    printf("The blocks allocated are:\n");
    for(j = 0; j < blkquan; j++)
    {
again:
        if(MA[0] <= 1)
        {
            if(MA[0] == 1)
            {
                if(MA[1] == 0)
                {
                    printf("No free block available in the disk!\n");
                    return -1;
                }
                else
                {
                    s = MA[1];
                    As = FindBlkAddr(s);
                    A0 = FindBlkAddr(0);
                    memcpy(A0, As, sizeof(int) * BlkSize);
		    printf("%d ", s);
		    GrpQuan --;
                }        
            }
            else
            {
                MA = FindBlkAddr(0);
                goto again;
            }             
        }    
        else
        {
alloc:
            i = MA[0];
            s = MA[i];
            MA[0] = MA[0] - 1;
            LeftDiskSize = LeftDiskSize - 1;
            printf("%d ", s);
        }    
    }    
    printf("\n");
    return 0;
}  

void DispFreeSpace()
{
    int *pt;
    int i, j, k;
    
    printf("\nAll free blocks will be displayed in group below:\n");
    pt = FindBlkAddr(0);
    i = 1;
    while(1)
    {
        j = pt[0];
	if(pt[1] == 0)
	{
	    printf("Group %d has %d free blocks, and this group is the last group.\n", i, j - 1);
	}
	else
	{	
       	    printf("Group %d has %d free blocks, and block %d is the pointer to group %d.\n", i, j - 1, pt[1], i+1);
	}
        for(k = 2; k <=j; k++)
        {
	    if( pt[k] == 0) continue;
            printf("\tBlock %d is free.\n", pt[k]);
        }
	if(pt[1] == 0) break;
        pt = FindBlkAddr(pt[1]);   
	i ++;
    }
    printf("\n");    
}          

int FindFreeBlk(int blknum)
{
    int *pt;
    int i, j, k;
    
    pt = FindBlkAddr(0);
    i = 1;
    while(pt[1] != 0)
    {
        j = pt[0];
        for(k = 1; k <=j; k++)
        {
            if(pt[k] == blknum)
            {
		if(k == 1)
		{
                    return 2;
		}
		else
		{
		    return 1;
		}	
            }    
        }
        pt = FindBlkAddr(pt[1]);    
    }        
    return 0;
}    

void work()
{
    int choice;
    int ret, ret1;
    char buffer[1024];
    
    while(1)
    {
menu:
        printf("\nThere are still %d byte space available.\n", LeftDiskSize);
        printf("1---Allocate Disk Space\n");
        printf("2---Dispose Disk Space\n");
        printf("3---Display free blocks\n");
        printf("0---Exit\n");
        printf("Please input your choice:");
        
        scanf("%s", buffer);
        ret = atoi(buffer);
        
        if(ret < 0)
        {
                goto menu;
        }
        choice = ret;
        
        switch(choice)
        {
            case 0:
                return;
            case 1:
                printf("How many bytes do you want to allocate:");
                scanf("%s", buffer);
                ret = atoi(buffer);
                
                if(ret < 0)
                {
                    printf("Invalid value!\n");
                    goto menu;
                }        
                
                if(ret > LeftDiskSize)
                {
                    printf("There are not enough spaces in the disk!\n");
                    goto menu;
                }    
                
                AllocateDisk(ret);
                
                DispFreeSpace();
                
                break;
            case 2:
                printf("Which block do you want to free:");
                scanf("%s", buffer);
                ret = atoi(buffer);
                
                if(ret < 0)
                {
                    printf("Invalid value!\n");
                    goto menu;
                
		}        
                
		if(ret > DiskSize || ret <= 0)
		{
		    printf("Block number is available from 1 to %d only!\n", DiskSize);
		    goto menu; 
		}

		ret1 = FindFreeBlk(ret);

                if(ret1 == 1)
                {
                    printf("This block has been free already, and need not to be free!\n");
                    goto menu;
                }
		else if(ret1 == 2)
		{
		    printf("This block stores information of the next group, and you can not free it manually!\n");
		    goto menu;
		}
                
                DisposeBlk(ret);
                
                DispFreeSpace();
                break;
            case 3:
                DispFreeSpace();
                break;
            default:
                goto menu;     
        }        
                             
    }    
}    

   
