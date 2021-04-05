#include <stdio.h>
#include <malloc.h>

typedef struct _stack stack;

struct _stack
{
	int data;
	stack *link;
};

stack *create_stack_node(void)
{
	stack *node = (stack *)malloc(sizeof(stack));
	node->link = NULL;

	return node;
}

stack *push(stack *top, int data)
{
	stack *tmp = create_stack_node();

	tmp->data = data;
	tmp->link = top;

	return tmp;
}

stack *pop(stack *top)
{
	int data;
	stack *tmp;

	if (!top)
	{
		printf("stack is empty\n");
		return NULL;
	}

	tmp = top;

	data = top->data;
	tmp = top->link;

	printf("pop from stack: %d\n", data);

	free(top);

	return tmp;
}

void print_stack(stack *top)
{
	stack *tmp = top;

	while (tmp)
	{
		printf("stack: %d\n", tmp->data);
		tmp = tmp->link;
	}
}

int main(void)
{
	int i;
	int data[] = { 10, 13, 7, 24, 15 };

	stack *top = NULL;

	for (i = 0; i < sizeof(data) / sizeof(int); i++)
	{
		top = push(top, data[i]);
	}

	print_stack(top);

	top = pop(top);

	print_stack(top);

	return 0;
}
