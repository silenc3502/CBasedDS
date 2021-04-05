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

void enqueue(queue **head, int data)
{
    if (!(*head))
    {
        *head = create_queue_node();
        (*head)->data = data;
        return;
    }

    enqueue(&(*head)->link, data);
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

int dequeue(queue **head)
{
    queue *tmp;

    if (!(*head))
    {
        printf("queue is empty\n");
        return -1;
    }

    tmp = *head;

    int data = tmp->data;
    *head = tmp->link;

    free(tmp);

    return data;
}

int main(void)
{
    int i;
    queue *head = NULL;

    int data[] = { 1, 10, 5, 3, 7, 8, 12 };

    for (i = 0; i < sizeof(data) / sizeof(int); i++)
    {
        enqueue(&head, data[i]);
    }

    print_queue(head);

    printf("data from dequeue: %d\n", dequeue(&head));

    print_queue(head);

    return 0;
}
