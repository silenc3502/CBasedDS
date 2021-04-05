#include <stdio.h>
#include <stdlib.h>

typedef struct _queue queue;

struct _queue
{
    int data;
    queue *link;
};

queue *create_queue_node(void)
{
    queue *tmp = (queue *)malloc(sizeof(queue));

    tmp->link = NULL;
    return tmp;
}

queue *enqueue(queue *head, int data)
{
    if (!head)
    {
        head = create_queue_node();
        head->data = data;
        return head;
    }

    head->link = enqueue(head->link, data);
}

void print_queue(queue *head)
{
    queue *tmp = head;

    while (tmp)
    {
        printf("data from queue: %d\n", tmp->data);
        tmp = tmp->link;
    }
}

queue *dequeue(queue *head)
{
    queue *tmp;
    int data;

    if (!head)
    {
        printf("queue is empty\n");
        return NULL;
    }

    data = head->data;
    tmp = head->link;

    free(head);

    printf("data from dequeue: %d\n", data);

    return tmp;
}

int main(void)
{
    int i;
    queue *head = NULL;

    int data[] = { 1, 10, 5, 3, 7, 8, 12 };

    for (i = 0; i < sizeof(data) / sizeof(int); i++)
    {
        head = enqueue(head, data[i]);
    }

    print_queue(head);

    head = dequeue(head);

    print_queue(head);

    return 0;
}
