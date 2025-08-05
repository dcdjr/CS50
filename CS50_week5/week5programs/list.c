#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

int main(void)
{
    // Created a pointer to the first node in the list, initialized to NULL
    // because there are no nodes to point to yet
    node *list = NULL;

    // Loop to create 3 nodes
    for (int i = 0; i < 3; i++)
    {
         // Allocate memory for a new node and assign its address to pointer n
        node *n = malloc(sizeof(node));

        // Check if malloc failed
        if (n == NULL)
        {
            return 1;
        }

        // Set the node's number field to user input
        n->number = get_int("Number: ");
        n->next = NULL;

        // If list is empty
        if (list == NULL)
        {
            list = n;
        }
        // If list has numbers already
        else
        {
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                // If at end of list;
                if (ptr->next == NULL)
                {
                    ptr->next = n;
                    break;
                }
            }
        }
    }

    // Time passes

    for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        printf("%i\n", ptr->number);
    }

    // Time passes

    node *ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
    return 0;
}
