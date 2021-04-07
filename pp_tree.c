#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _tree tree;

struct _tree
{
    int data;
    tree *left;
    tree *right;
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

tree *create_avl_node(void)
{
    tree *tmp = (tree *)malloc(sizeof(tree));

    tmp->left = NULL;
    tmp->right = NULL;

    return tmp;
}

void insert_tree(tree **root, int data)
{
    if (!(*root))
    {
        *root = create_avl_node();
        (*root)->data = data;
        return;
    }

    if ((*root)->data > data)
    {
        insert_tree(&(*root)->left, data);
    }
    else if ((*root)->data < data)
    {
        insert_tree(&(*root)->right, data);
    }
}

void print_tree(tree *root)
{
    tree *tmp = root;

    if (tmp)
    {
        print_tree(tmp->left);

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
            printf("right = %3d\n", tmp->right->data);
        }
        else
        {
            printf("right = NULL\n");
        }

        print_tree(tmp->right);
    }
}

void exchange_node(tree **root)
{
    tree *tmp = *root;

    if ((*root)->right)
    {
        (*root) = (*root)->right;
    }
    else
    {
        (*root) = (*root)->left;
    }

    free(tmp);
}

void find_left_max(tree **root, int *max)
{
    if ((*root)->right)
    {
        find_left_max(&(*root)->right, max);
    }
    else
    {
        *max = (*root)->data;
        exchange_node(root);
    }
}

void delete_tree(tree **root, int data)
{
    int max;

    if ((*root)->data > data)
    {
        delete_tree(&(*root)->left, data);
    }
    else if ((*root)->data < data)
    {
        delete_tree(&(*root)->right, data);
    }
    else if ((*root)->left && (*root)->right)
    {
        printf("need to find left max or right min\n");

        find_left_max(&(*root)->left, &max);
        printf("left max = %d\n", max);
        (*root)->data = max;
    }
    else
    {
        printf("There are one leaf node or not\n");
        exchange_node(root);
    }
}

int main(void)
{
    tree *root = NULL;

    int i;
    int data[31] = { 0 };

	srand(time(NULL));

	init_data(data, 31);
	print_arr(data, 31);

    for (i = 0; i < sizeof(data) / sizeof(int); i++)
    {
        insert_tree(&root, data[i]);
    }

    print_tree(root);

    delete_tree(&root, 10);
    delete_tree(&root, 15);
    delete_tree(&root, 20);

    print_tree(root);

    return 0;
}
