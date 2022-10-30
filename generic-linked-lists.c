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
void updateAt(glist_t **head, int pos, void *val, size_t val_size);
void destroy_glist(glist_t **head);

/** COPY OPERATIONS */
glist_t *copy_glist(glist_t *head);

/** */

/** TO DEBUG*/
// void copy_glist(glist_t **dest, glist_t **src); // does not work

int main(void)
{
    glist_t *head = NULL;
    // glist_t *head_copy = NULL;

    char buffer[20];
    strcpy(buffer, "hello");

    int num[1];
    num[0] = 1;

    push_glist(&head, (void *)buffer, 20 * sizeof(char));
    push_glist(&head, (void *)num, 1 * sizeof(int));

    // head_copy = copy_glist(head);

    printf("the first value is %s\n", (char *)(head->data));
    printf("the second value is %i\n", *((int *)(head->next->data)));

    updateAt(&head, 0, (void *)&num, 1 * sizeof(int));

    printf("the first value is %i\n", *(int *)(head->data));
    printf("the second value is %s\n", ((char*)(head->next->data)));
    printf("the third value is %i\n", *((int *)(head->next->next->data)));

    destroy_glist(&head);
    // destroy_glist(&head_copy);

    return 0;
}

void push_glist(glist_t **head, void *val, size_t val_size)
{
    assert(head != NULL);

    if (*head == NULL)
    {
        *head = malloc(sizeof(glist_t));
        assert(*head != NULL);

        (*head)->data = malloc(val_size * sizeof(char));
        assert((*head)->data != NULL);

        memcpy((*head)->data, val, val_size);

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
        assert(temp->next != NULL);

        temp = temp->next;

        temp->data = malloc(val_size * sizeof(char));
        assert(temp->data != NULL);

        memcpy(temp->data, val, val_size);

        temp->data_size = val_size;
        temp->next = NULL;
    }
}

void destroy_glist(glist_t **head)
{
    assert(head != NULL);
    assert(*head != NULL);

    glist_t *temp = (*head);

    while (temp->next != NULL)
    {
        // point to the next element starting from the head
        temp = temp->next;

        // free the head node
        free((*head)->data);
        free(*head);

        // make the head point to its next
        *head = temp;
    }

    free((*head)->data);
    free(*head);

    // set pointers to null to avoid illegal derefrenciations
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

        current->data = malloc(traversal->data_size * sizeof(char));
        assert(current->data != NULL);

        memcpy(current->data, traversal->data, traversal->data_size);

        current->data_size = traversal->data_size;

        traversal = traversal->next;
    }

    // remove the first element;

    current = resault->next;
    free(resault); // WARNING: we do not free the resault->data since we've never allocated it.
    resault = current;

    return resault;
}

void updateAt(glist_t **head, int pos, void *val, size_t val_size)
{
    assert(head != NULL);
    assert(*head != NULL);
    assert(pos >= 0);

    if (pos == 0)
    {
        // insert at the beginning
        glist_t *temp = malloc(sizeof(glist_t));
        assert(temp != NULL);

        temp->data_size = val_size;

        temp->data = malloc(val_size * sizeof(char));
        assert(temp->data != NULL);

        memcpy(temp->data, val, val_size);

        temp->next = *head;

        *head = temp;

        return;
    }

    int counter = 0;
    glist_t *traversal = *head;


    while (counter < pos && traversal->next != NULL)
    {
        /* code */
        traversal = traversal->next;
        counter++;
    }

    // if pos < length
    if (counter == pos)
    {

        // free the old data;
        free(traversal->data);

        // create the new data container
        traversal->data = malloc(val_size * sizeof(char));
        assert(traversal->data != NULL);

        traversal->data_size = val_size;

        memcpy(traversal->data, val, val_size);

        return;
    }

    // if pos > length
    if (traversal->next == NULL && counter != pos)
    {

        traversal->next = malloc(sizeof(glist_t));
        assert(traversal->next != NULL);

        traversal = traversal->next;

        traversal->data_size = val_size;

        traversal->data = malloc(val_size * sizeof(char));
        assert(traversal->data != NULL);

        memcpy(traversal->data, val, val_size);

        traversal->next = NULL;

        return;
    }
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