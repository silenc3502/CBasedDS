#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define	LEFT			-2
#define RIGHT			2

typedef struct _avl avl;

struct _avl
{
	int data;
	avl *left;
	avl *right;
	int level;
};

bool check_dup(int *data, int compare, int idx)
{
	int i;

	for (i = 0; i < idx; i++)
	{
		if (data[i] == compare)
		{
			return true;
		}
	}

	return false;
}

void init_data(int *data, int num)
{
	int i, tmp;

	for (i = 0; i < num; i++)
	{
reassign:
		tmp = rand() % 31 + 1;

		if (check_dup(data, tmp, i))
		{
			goto reassign;
		}

		data[i] = tmp;
	}
}

void print_arr(int *data, int num)
{
	int i;

	for (i = 0; i < num; i++)
	{
		printf("%3d", data[i]);

		if (i % 7 == 6)
		{
			printf("\n");
		}
	}

	printf("\n");
}

avl *create_avl_node(void)
{
	avl *tmp = (avl *)malloc(sizeof(avl));

	tmp->left = NULL;
	tmp->right = NULL;

	return tmp;
}

int calc_level(avl **root)
{
	int left, right;

	right = (*root)->right ? (*root)->right->level : 0;
	left = (*root)->left ? (*root)->left->level : 0;

	if (right > left)
	{
		return right + 1;
	}

	return left + 1;
}

void lr_rotation(void)
{
	printf("lr rotation\n");
}

void ll_rotation(void)
{
	printf("ll rotation\n");
}

void rl_rotation(void)
{
	printf("rl rotation\n");
}

void rr_rotation(void)
{
	printf("rr rotation\n");
}

void rotation(int factor, avl **root, int data)
{
	printf("balance factor = %3d\tnode data = %3d\t in data = %3d\n", factor, (*root)->data, data);

	switch (factor)
	{
		case LEFT:
			// FIX
			if ((*root)->left->data < data)
			{
				lr_rotation();
			}
			else
			{
				ll_rotation();
			}

			break;

		case RIGHT:
			// CHECK
			if ((*root)->right->data > data)
			{
				rl_rotation();
			}
			else
			{
				rr_rotation();
			}

			break;
	}
}

void adjust_balance(avl **root, int data)
{
	int left, right, balance_factor;

	left = (*root)->left ? (*root)->left->level : 0;
	right = (*root)->right ? (*root)->right->level : 0;

	balance_factor = right - left;
	if (abs(balance_factor) > 1)
	{
		printf("Rotation Occurrence\n");
		rotation(balance_factor, root, data);
	}
}

void insert_avl(avl **root, int data)
{
	if (!(*root))
	{
		*root = create_avl_node();
		(*root)->data = data;
		(*root)->level = 1;
	}

	if ((*root)->data > data)
	{
		insert_avl(&(*root)->left, data);
	}
	else if ((*root)->data < data)
	{
		insert_avl(&(*root)->right, data);
	}

	(*root)->level = calc_level(root);

	adjust_balance(root, data);
}

void print_avl(avl *tree)
{
	avl *tmp = tree;

	if (tmp)
	{
		print_avl(tmp->left);

		printf("data = %3d\t", tmp->data);

		if (tmp->left)
		{
			printf("left = %3d\t", tmp->left->data);
		}
		else
		{
			printf("left = NULL\t");
		}

		if (tmp->right)
		{
			printf("right = %3d\t", tmp->right->data);
		}
		else
		{
			printf("right = NULL\t");
		}

		printf("level = %2d\n", tmp->level);

		print_avl(tmp->right);
	}
}

int main(void)
{
	avl *root = NULL;

	int i;
	// test for LR
	// int data[6] = { 12, 20, 7, 10, 3, 8 };
	// test for LL
	// int data[6] = { 12, 20, 7, 10, 3, 2 };
	// test for RR
	// int data[6] = { 12, 7, 20, 15, 24, 28 };
	// test for RL
	int data[6] = { 12, 7, 20, 25, 15, 13 };
#if 0
	int data[31] = { 0 };

	srand(time(NULL));

	init_data(data, 31);
	print_arr(data, 31);
#endif

	for (i = 0; i < sizeof(data) / sizeof(int); i++)
	{
		insert_avl(&root, data[i]);
	}

	print_avl(root);

	return 0;
}
