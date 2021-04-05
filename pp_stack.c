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

void push(stack **top, int data)
{
	stack *tmp = *top;

	*top = create_stack_node();
	(*top)->data = data;
	(*top)->link = tmp;
}

int pop(stack **top)
{
	int data;
	stack *tmp;

	if (!(*top))
	{
		printf("stack is empty\n");
		return -1;
	}

	tmp = *top;

	data = tmp->data;
	*top = tmp->link;

	free(tmp);

	return data;
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
		push(&top, data[i]);
	}

	print_stack(top);

	printf("pop from stack: %d\n", pop(&top));

	print_stack(top);

	return 0;
}
