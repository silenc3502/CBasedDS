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

/* Initialize a new node. */
avl *avl_create_node() {
    avl *node = NULL;

    if( ( node = malloc( sizeof( avl ) ) ) == NULL ) {
        return NULL;
    }

    node->left = NULL;
    node->right = NULL;
    node->data = 0;

    return node;
}

/* Find the height of an AVL node recursively */
int avl_node_height( avl *node ) {
    int height_left = 0;
    int height_right = 0;

    if( node->left ) height_left = avl_node_height( node->left );
    if( node->right ) height_right = avl_node_height( node->right );

    return height_right > height_left ? ++height_right : ++height_left;
}

/* Find the balance of an AVL node */
int avl_balance_factor( avl *node ) {
    int bf = 0;

    if( node->left  ) bf += avl_node_height( node->left );
    if( node->right ) bf -= avl_node_height( node->right );

    return bf ;
}

/* Left Left Rotate */
avl *avl_rotate_leftleft( avl *node ) {
    avl *a = node;
    avl *b = a->left;

    a->left = b->right;
    b->right = a;

    return( b );
}

/* Left Right Rotate */
avl *avl_rotate_leftright( avl *node ) {
    avl *a = node;
    avl *b = a->left;
    avl *c = b->right;

    a->left = c->right;
    b->right = c->left;
    c->left = b;
    c->right = a;

    return( c );
}

/* Right Left Rotate */
avl *avl_rotate_rightleft( avl *node ) {
    avl *a = node;
    avl *b = a->right;
    avl *c = b->left;

    a->right = c->left;
    b->left = c->right;
    c->right = b;
    c->left = a;

    return( c );
}

/* Right Right Rotate */
avl *avl_rotate_rightright( avl *node ) {
    avl *a = node;
    avl *b = a->right;

    a->right = b->left;
    b->left = a;

    return( b );
}

/* Balance a given node */
avl *avl_balance_node( avl *node ) {
    avl *newroot = NULL;

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
void avl_balance( avl **tree ) {

    avl *newroot = NULL;

    newroot = avl_balance_node( *tree );

    if( newroot != *tree )  {
        *tree = newroot;
    }
}

/* Insert a new node. */
void avl_insert( avl **tree, int data ) {
    avl *node = NULL;
    avl *next = NULL;
    avl *last = NULL;

    /* Well, there must be a first case */
    if( !(*tree) ) {
        node = avl_create_node();
        node->data = data;

        *tree = node;

        /* Okay.  We have a root already.  Where do we put this? */
    } else {
        next = *tree;

        while( next != NULL ) {
            last = next;

            if( data < next->data ) {
                next = next->left;

            } else if( data > next->data ) {
                next = next->right;

                /* Have we already inserted this node? */
            } else if( data == next->data ) {
                /* This shouldn't happen. */
            }
        }

        node = avl_create_node();
        node->data = data;

        if( data < last->data ) last->left = node;
        if( data > last->data ) last->right = node;

    }

    avl_balance( tree );
}

/* Find the node containing a given data */
avl *avl_find( avl *tree, int data ) {
    avl *current = tree;

    while( current && current->data != data ) {
        if( data > current->data )
            current = current->right;
        else
            current = current->left;
    }

    return current;
}

void print_avl(avl *tree)
{
    avl *tmp = tree;

    if (tmp)
    {
        print_avl(tmp->left);

        printf("data = %5d\t", tmp->data);

        if (tmp->left)
        {
            printf("left = %5d\t", tmp->left->data);
        }
        else
        {
            printf("left = NULL\t");
        }

        if (tmp->right)
        {
            printf("right = %5d\t", tmp->right->data);
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
    avl *tree = NULL;
    int i = 0;
    int data[31] = { 0 };
    int len = sizeof(data) / sizeof(int);

    init_data(data, len);
    print_arr(data, len);

    for( i = 0; i < len; i++ ) {
        avl_insert( &tree, data[i] );
    }

    print_avl(tree);

    return 0;
}
