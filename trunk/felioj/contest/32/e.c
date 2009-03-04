#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define SEQLEN 2000
#define SETMARK 'S'
#define MESMARK 'M'

const char EndMark[]="END";

unsigned int data[200009];

struct seqtree_desc
{
	unsigned long left;
	unsigned long right;
	unsigned long val;
	struct seqtree_desc *lchild;
	struct seqtree_desc *rchild;
};
typedef struct seqtree_desc seqtree_t;

void work(seqtree_t *, char, unsigned long, unsigned long);
seqtree_t *BuildSeqTree(unsigned long, unsigned long);
void SetOpt(seqtree_t *, unsigned long, int);
unsigned long QueryOpt(seqtree_t *, unsigned long, unsigned long);
void DisposeSeqTree(seqtree_t *);
void CleanSeqTree(seqtree_t *);

int main()
{
	unsigned long ponum;
	unsigned long ii;
	char optstr[10];
	char opt;
	int count;
	unsigned long Val1, Val2;
	seqtree_t *root;


	root = BuildSeqTree(0, 200009);
	scanf("%ld", &ponum);
	count = 0;
	while(ponum != 0)
	{
		if(count != 0) printf("\n");
		printf("Case %d:\n", count + 1);
		count ++;
		for( ii = 0; ii < ponum; ii ++)
		{
			scanf("%d", &data[ii]);
			SetOpt(root, ii, data[ii]);
		}
		

		while(1)
		{
			scanf("%s", optstr);
			if(!strcmp(optstr, EndMark))
			{
				break;
			}
			else
			{
				opt = *optstr;
				scanf("%ld %ld", &Val1, &Val2);
				work(root, opt, Val1, Val2);
			}
		}

		CleanSeqTree(root);

		scanf("%ld", &ponum);
		
		
	}
	DisposeSeqTree(root);
	return 0;
}

seqtree_t *BuildSeqTree(unsigned long left, unsigned long right)
{
	seqtree_t *this_node;
	unsigned long mid;

	/*
	if(node != NULL)
	{
		free(node);
	}
	*/

	this_node = (seqtree_t *)malloc(sizeof(seqtree_t));
	this_node -> left = left;
	this_node -> right = right;
	this_node -> val = 0;
	if((this_node -> left) != (this_node -> right))
	{
		mid = (this_node -> left) + ((this_node -> right) - (this_node -> left) + 1) / 2;
		this_node -> lchild = BuildSeqTree(this_node -> left, mid - 1);
		this_node -> rchild = BuildSeqTree(mid, this_node -> right);
	}

	return this_node;
}

void SetOpt(seqtree_t *node, unsigned  long loc, int val)
{
	int mid;

	if((node -> left) != (node -> right))
	{
		mid = (node -> left) + ((node -> right) - (node -> left) + 1) / 2;
		if( loc < mid )
		{
			SetOpt(node -> lchild, loc, val);
		}
		else
		{
			SetOpt(node -> rchild, loc, val);
		}
		node -> val += val;

	}
	else
	{
		node -> val += val;
	}
}

unsigned long QueryOpt(seqtree_t *node, unsigned long left, unsigned long right)
{
	unsigned long result;
	unsigned long mid;

	if( left == (node -> left) &&
	    right== (node -> right))
	{
		return node -> val;
	}
	else
	{
		mid = (node -> left) + ((node -> right) - (node -> left) + 1) / 2;
		if( right < mid)
		{
			return QueryOpt(node -> lchild, left, right);
		}
		else if( left >= mid)
		{
			return QueryOpt(node -> rchild, left, right);
		}
		else
		{
			result = QueryOpt(node -> lchild, left, mid - 1) + QueryOpt(node -> rchild, mid, right);
			return result;
		}
	}

}

void CleanSeqTree(seqtree_t *node)
{
	if( (node -> lchild) != NULL)
	{
		CleanSeqTree(node -> lchild);
	}
	
	if( (node -> rchild) != NULL)
	{
		CleanSeqTree(node -> rchild);
	}

	node -> val = 0;
}

void DisposeSeqTree(seqtree_t *node)
{
	if((node -> left) != (node -> right))
	{
		DisposeSeqTree(node -> lchild);
		DisposeSeqTree(node -> rchild);
		free(node);
	}
	else
	{
		free(node);
	}
}

void work(seqtree_t *root, char opt, unsigned long Val1, unsigned long Val2)
{
	unsigned long diff;
	unsigned long long result;

	switch(opt)
	{
		case SETMARK:
			Val1 --;
			diff = Val2 - data[Val1];
			SetOpt(root, Val1, diff);
			data[Val1] = Val2;
			break;

		case MESMARK:
			Val1 --;
			Val2 --;

			result = QueryOpt(root, Val1, Val2);
			printf("%lld\n", result);
			break;

		default:
			break;
	}
}
