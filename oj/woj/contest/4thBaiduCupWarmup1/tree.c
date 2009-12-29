#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

struct node_desc
{
	int val;
	unsigned long long count;
	struct node_desc *lchild;
	struct node_desc *rchild;
	unsigned long long lm, ll;
	unsigned long long rm, rl;
};
typedef struct node_desc node_t;

void initTree();
unsigned long long countTree(node_t *);
unsigned long long comb(unsigned long long, unsigned long long);
void insert(node_t *, int);

int data[1000];
int n;
node_t root;
unsigned long long total;

int main()
{
	int ii;

	while(1)
	{	
		scanf("%d", &n);
		if(n == 1)break;
		for(ii = 0; ii < n; ii ++)
			scanf("%d", &data[ii]);

		initTree();
		total = 0;

		total = countTree(&root);
		printf("%lld\n", total);
	}
	return 0;
}

void initTree()
{
	int ii;

	root.val = data[0];
	root.lchild = NULL;
	root.rchild = NULL;
	root.ll = 0;
	root.rl = 0;
	root.lm = 1;
	root.rm = 1;
	root.count = 0;

	for(ii = 1; ii < n; ii ++)
	{
		insert(&root, data[ii]);
	}
}

unsigned long long comb(unsigned long long a, unsigned long long b)
{
	double ans = 1;
	double now = 1;
	int ii;

	for(ii = b+1; ii <= a; ii ++)
	{
		ans *= ii;
	}

	while(now <= (a-b))
	{
		ans /= now;
		now ++;
	}

	return (unsigned long long )ans;
}

unsigned long long countTree(node_t *node)
{
	unsigned long long temp = 0;
	unsigned long long lmm = 0, rmm = 0;

	if( node -> lchild == NULL &&
	    node -> rchild == NULL) 
	{
		node -> count = 1;
		return 1;
	}
	   
	if( node -> lchild != NULL) 
	{
		lmm = countTree(node -> lchild);
	}
	else
		lmm = 1;
	if( node -> rchild != NULL)
	{
		rmm = countTree(node -> rchild);
	}
	else
		rmm = 1;
	
	temp = node -> ll + node -> rl;
	node -> count = comb(temp, node -> ll);
	node -> count = (node -> count) * lmm * rmm;
	printf("calc node %d, rl+ll=%lld, ll=%lld, lmm=%lld, rmm=%lld, value=%lld\n", node->val, temp, node -> ll, lmm, rmm,node->count);
	return node -> count;
}

void insert(node_t *node, int value)
{
	node_t *new_node;

	if(value >= (node -> val))
	{
		if((node -> rchild) != NULL)
		{
			node -> rl ++;
			insert(node -> rchild, value);
		}
		else
		{
			node -> rl ++;
			new_node = (node_t *)malloc(sizeof(node_t));
			new_node -> val = value;
			new_node -> lchild = NULL;
			new_node -> rchild = NULL;
			new_node -> count = 0;
			new_node -> ll = 0;
			new_node -> rl = 0;
			new_node -> lm = 1;
			new_node -> rm = 1;
			node -> rchild = new_node;
		}
	}
	else
	{
		if((node -> lchild) != NULL)
		{
			node -> ll ++;
			insert(node -> lchild, value);
		}
		else
		{
			node -> ll ++;
			new_node = (node_t *)malloc(sizeof(node_t));
			new_node -> val = value;
			new_node -> lchild = NULL;
			new_node -> rchild = NULL;
			new_node -> count = 0;
			new_node -> ll = 0;
			new_node -> rl = 0;
			new_node -> lm = 1;
			new_node -> rm = 1;
			node -> lchild = new_node;
		}
		
	}
}
