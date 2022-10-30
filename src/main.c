#include "../headers/main.h"

int main(void)
{
    glist_t *head = NULL;

    char buffer[20];

    strcpy(buffer, "world !");
    push_glist(&head, (void *)buffer, 20 * sizeof(char));

    strcpy(buffer, "there,");
    push_glist(&head, (void *)buffer, 20 * sizeof(char));

    strcpy(buffer, "hello ");
    push_glist(&head, (void *)buffer, 20 * sizeof(char));

    printf("the first value is %s\n", (char *)(head->data));
    printf("the second value is %s\n", ((char *)(head->next->data)));
    printf("the third value is %s\n", ((char *)(head->next->next->data)));

    bubble_sort_glist(&head, 3, &strcmp, &swap_glist_str);

    printf("\n\n after sorting the generic linked list \n\n");

    printf("the first value is %s\n", (char *)(head->data));
    printf("the second value is %s\n", ((char *)(head->next->data)));
    printf("the third value is %s\n", ((char *)(head->next->next->data)));

    destroy_glist(&head);

    return 0;
}
