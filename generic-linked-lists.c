#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct Node
{
    void *data;
    size_t data_size;
    struct Node *next;
};

typedef struct Node glist_t;

/** CRUD OPERATIONS */
void push_glist(glist_t **head, void *val, size_t val_size);
void destroy_glist(glist_t **head);

/** COPY OPERATIONS */
glist_t *copy_glist(glist_t *head);

/** TO DEBUG*/
// void copy_glist(glist_t **dest, glist_t **src); // does not work

int main(void)
{
    glist_t *head = NULL;
    glist_t *head_copy = NULL;

    char buffer[20];
    strcpy(buffer, "hello");

    int num[1];
    num[0] = 1;

    push_glist(&head, (void *)buffer, 20 * sizeof(char));
    push_glist(&head, (void *)num, 1 * sizeof(int));

    head_copy = copy_glist(head);

    printf("the first value is %s\n", (char *)(head_copy->data));
    printf("the second value is %i\n", *((int *)(head_copy->next->data)));

    destroy_glist(&head);
    destroy_glist(&head_copy);

    return 0;
}

void push_glist(glist_t **head, void *val, size_t val_size)
{
    assert(head != NULL);

    if (*head == NULL)
    {
        *head = malloc(sizeof(glist_t));
        assert(*head != NULL);

        (*head)->data = val;
        (*head)->data_size = val_size;
        (*head)->next = NULL;
    }
    else
    {
        glist_t *temp = *head;

        while (temp->next != NULL)
        {
            /* code */
            temp = temp->next;
        }

        temp->next = malloc(sizeof(glist_t));
        assert(temp != NULL);

        temp->next->data = val;
        temp->next->data_size = val_size;
        temp->next->next = NULL;
    }
}

/*
    Note: in the destroy function we can not free the data pointers since they are void *
    Also, since they are declared staticly (on the stack), no need to free them.

    If, you consider declaring them dynamicly ( with malloc), a hint can be to cast them as char *
*/
void destroy_glist(glist_t **head)
{
    assert(head != NULL);
    assert(*head != NULL);

    glist_t *temp = (*head);

    while (temp->next != NULL)
    {
        temp = temp->next;
        free(*head);
        *head = temp;
    }

    free(*head);
    *head = NULL;
    temp = NULL;
}

glist_t *copy_glist(glist_t *head)
{
    assert(head != NULL);

    glist_t *resault;
    glist_t *traversal = head;

    // create the resault copy with one more element at the beginning
    glist_t *current = malloc(sizeof(glist_t));
    assert(current != NULL);

    // make resault points to this first element;
    resault = current;

    while (traversal != NULL)
    {
        /* code */
        current->next = malloc(sizeof(glist_t));
        assert(current->next != NULL);

        current = current->next;

        current->data = traversal->data;
        current->data_size = traversal->data_size;

        memcpy(current->data, traversal->data, traversal->data_size);

        traversal = traversal->next;
    }

    // remove the first element;

    current = resault->next;
    free(resault);
    resault = current;

    return resault;
}






/** TO DEBUG*/

/*

void copy_glist(glist_t **dest, glist_t **src)
{
    assert(src != NULL);
    assert(*src != NULL);

    assert(dest != NULL);

    glist_t *traversal = *src;
    glist_t *current = *dest;

    if (current == NULL)
    {
        current = malloc(sizeof(glist_t));

        current->data = traversal->data;
        current->data_size = traversal->data_size;

        memcpy(current->data, traversal->data, traversal->data_size);

        current->next = NULL;

        traversal = traversal->next;
    }

    while (traversal != NULL)
    {
        current->next = malloc(sizeof(glist_t));

        current->next->data = traversal->data;
        current->next->data_size = traversal->data_size;

        memcpy(current->next->data, traversal->data, traversal->data_size);

        current->next->next = NULL;

        current = current->next;
        traversal = traversal->next;
    }
}
*/