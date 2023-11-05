#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define	LEFT			-2
#define RIGHT			2

static int cnt = 0;

typedef struct _avl avl;

struct _avl
{
    int data;
    avl *left;
    avl *right;
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
        tmp = rand() % num + 1;

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
        printf("%4d", data[i]);

        if (i % 7 == 6)
        {
            printf("\n");
        }
    }

    printf("\n");
}

struct avl_node_s {
    struct avl_node_s *left;
    struct avl_node_s *right;
    int value;
};

typedef struct avl_node_s avl_node_t;

struct avl_tree_s {
    struct avl_node_s *root;
};

typedef struct avl_tree_s avl_tree_t;


/* Create a new AVL tree. */
avl_tree_t *avl_create() {
    avl_tree_t *tree = NULL;

    if( ( tree = malloc( sizeof( avl_tree_t ) ) ) == NULL ) {
        return NULL;
    }

    tree->root = NULL;

    return tree;
}

/* Initialize a new node. */
avl_node_t *avl_create_node() {
    avl_node_t *node = NULL;

    if( ( node = malloc( sizeof( avl_node_t ) ) ) == NULL ) {
        return NULL;
    }

    node->left = NULL;
    node->right = NULL;
    node->value = 0;

    return node;
}

/* Find the height of an AVL node recursively */
int avl_node_height( avl_node_t *node ) {
    int height_left = 0;
    int height_right = 0;

    if( node->left ) height_left = avl_node_height( node->left );
    if( node->right ) height_right = avl_node_height( node->right );

    return height_right > height_left ? ++height_right : ++height_left;
}

/* Find the balance of an AVL node */
int avl_balance_factor( avl_node_t *node ) {
    int bf = 0;

    if( node->left  ) bf += avl_node_height( node->left );
    if( node->right ) bf -= avl_node_height( node->right );

    return bf ;
}

/* Left Left Rotate */
avl_node_t *avl_rotate_leftleft( avl_node_t *node ) {
    avl_node_t *a = node;
    avl_node_t *b = a->left;

    a->left = b->right;
    b->right = a;

    return( b );
}

/* Left Right Rotate */
avl_node_t *avl_rotate_leftright( avl_node_t *node ) {
    avl_node_t *a = node;
    avl_node_t *b = a->left;
    avl_node_t *c = b->right;

    a->left = c->right;
    b->right = c->left;
    c->left = b;
    c->right = a;

    return( c );
}

/* Right Left Rotate */
avl_node_t *avl_rotate_rightleft( avl_node_t *node ) {
    avl_node_t *a = node;
    avl_node_t *b = a->right;
    avl_node_t *c = b->left;

    a->right = c->left;
    b->left = c->right;
    c->right = b;
    c->left = a;

    return( c );
}

/* Right Right Rotate */
avl_node_t *avl_rotate_rightright( avl_node_t *node ) {
    avl_node_t *a = node;
    avl_node_t *b = a->right;

    a->right = b->left;
    b->left = a;

    return( b );
}

/* Balance a given node */
avl_node_t *avl_balance_node( avl_node_t *node ) {
    avl_node_t *newroot = NULL;

    /* Balance our children, if they exist. */
    if( node->left )
        node->left  = avl_balance_node( node->left  );
    if( node->right )
        node->right = avl_balance_node( node->right );

    int bf = avl_balance_factor( node );

    if( bf >= 2 ) {
        /* Left Heavy */

        if( avl_balance_factor( node->left ) <= -1 )
            newroot = avl_rotate_leftright( node );
        else
            newroot = avl_rotate_leftleft( node );

    } else if( bf <= -2 ) {
        /* Right Heavy */

        if( avl_balance_factor( node->right ) >= 1 )
            newroot = avl_rotate_rightleft( node );
        else
            newroot = avl_rotate_rightright( node );

    } else {
        /* This node is balanced -- no change. */

        newroot = node;
    }

    return( newroot );
}

/* Balance a given tree */
void avl_balance( avl_tree_t *tree ) {

    avl_node_t *newroot = NULL;

    newroot = avl_balance_node( tree->root );

    if( newroot != tree->root )  {
        tree->root = newroot;
    }
}

/* Insert a new node. */
void avl_insert( avl_tree_t *tree, int value ) {
    avl_node_t *node = NULL;
    avl_node_t *next = NULL;
    avl_node_t *last = NULL;

    /* Well, there must be a first case */
    if( tree->root == NULL ) {
        node = avl_create_node();
        node->value = value;

        tree->root = node;

        /* Okay.  We have a root already.  Where do we put this? */
    } else {
        next = tree->root;

        while( next != NULL ) {
            last = next;

            if( value < next->value ) {
                next = next->left;

            } else if( value > next->value ) {
                next = next->right;

                /* Have we already inserted this node? */
            } else if( value == next->value ) {
                /* This shouldn't happen. */
            }
        }

        node = avl_create_node();
        node->value = value;

        if( value < last->value ) last->left = node;
        if( value > last->value ) last->right = node;

    }

    avl_balance( tree );
}

/* Find the node containing a given value */
avl_node_t *avl_find( avl_tree_t *tree, int value ) {
    avl_node_t *current = tree->root;

    while( current && current->value != value ) {
        if( value > current->value )
            current = current->right;
        else
            current = current->left;
    }

    return current;
}

/* Do a depth first traverse of a node. */
void avl_traverse_node_dfs( avl_node_t *node, int depth ) {
    int i = 0;

    if( node->left ) avl_traverse_node_dfs( node->left, depth + 2 );

    for( i = 0; i < depth; i++ ) putchar( ' ' );
    printf( "%d: %d\n", node->value, avl_balance_factor( node ) );

    if( node->right ) avl_traverse_node_dfs( node->right, depth + 2 );
}

/* Do a depth first traverse of a tree. */
void avl_traverse_dfs( avl_tree_t *tree ) {
    avl_traverse_node_dfs( tree->root, 0 );
}

void print_avl(avl_node_t *tree)
{
    avl_node_t *tmp = tree;

    if (tmp)
    {
        print_avl(tmp->left);

        printf("data = %5d\t", tmp->value);

        if (tmp->left)
        {
            printf("left = %5d\t", tmp->left->value);
        }
        else
        {
            printf("left = NULL\t");
        }

        if (tmp->right)
        {
            printf("right = %5d\t", tmp->right->value);
        }
        else
        {
            printf("right = NULL\t");
        }

        printf("cnt = %5d\n", ++cnt);

        print_avl(tmp->right);
    }
}

int main( int argc, char **argv ) {
    avl_tree_t *tree = NULL;
    int i = 0;
    int data[2047] = { 0 };
    int len = sizeof(data) / sizeof(int);

    init_data(data, len);
    print_arr(data, len);

    tree = avl_create();

    for( i = 0; i < len; i++ ) {
        avl_insert( tree, data[i] );
    }

    print_avl(tree->root);

    return 0;
}
