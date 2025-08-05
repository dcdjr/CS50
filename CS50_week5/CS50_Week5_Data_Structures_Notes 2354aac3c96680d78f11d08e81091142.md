# CS50_Week5_Data_Structures_Notes

## Data Structures

- *Data structures* are essentially forms of organization in memory
- There are many ways to organize data in memory
- *Abstract data types* are those that we can conceptually imagine. When learning about CS, it’s often useful to begin with these conceptual data structures. Learning these will make it easier to understand how to implement more concrete data structures

---

## Queues

- *Queues* are one form of abstract data structure
- Queues have specific properties. Namely, they are *FIFO* or “first in first out.”
    - Example: Imagine being in an amusement park line. The first person in the line gets to go on the ride first, and the last person gets to go on the ride last.
- Queues have specific actions associated with them. For example, an item can be *enqueued*; that is, the item can join the line or queue. Further, an item can be *dequeued* or leave the queue once it reaches the front of the line.
- In code, you can imagine a queue as follows:
    
    ```c
    const int CAPACITY = 50;
    
    typedef struct
    {
        person people[CAPACITY];
        int size;
    }
    queue;
    ```
    

---

## Stacks

- Queues contrast with a *stack*. Fundamentally, a stack's properties are different than a queue's. Specifically, a stack is LIFO, “last in, first out.” Just like stacking trays in a dining hall, a tray that is placed in a stack last is the first that may be picked up.
- Stacks have specific actions associated with them. For example, *push* places something on top of a stack. *Pop* is removing something from the top of the stack.
- In code, you can imagine a stack as follows:
    
    ```c
    const int CAPACITY = 50;
    
    typedef struct
    {
        person people[CAPACITY];
        int size;
    }
    stack;
    ```
    
- You might imagine that the above code has a limitation. Since the capacity of the array is always predetermined in this code. Therefore, the stack may always be oversized.
- It would be nice for the stack to be dynamic - able to grow as items are added to it.

---

## Resizing Arrays

- Rewinding to week 2, an array is just a block of contiguous memory.
- You might imagine an array as follows:
    
    ![cs50Week5Slide019.png](cs50Week5Slide019.png)
    
- In memory, there are other values being stored by other programs, functions, and variables. Many of these may be unused garbage values that were utilized at one point but are available now for use.
- Imagine that you wanted to store a fourth value `4` in the array. What would be needed is to allocate a new area of memory and move the old array to a new one. Initially, this new area of memory would be populated with garbage values.
    
    ![cs50Week5Slide025.png](cs50Week5Slide025.png)
    
- As values are added to this area of memory, old garbage values are overwritten:
    
    ![cs50Week5Slide026.png](cs50Week5Slide026.png)
    
- Eventually, all old garbage values would be overwritten with our new data:
    
    ![cs50Week5Slide027.png](cs50Week5Slide027.png)
    
- One of the drawbacks of this approach is that it’s bad design: Every time we add a number, we have to copy the array item by item.

---

## Arrays

- Wouldn’t it be nice if we were able to put the `4` somewhere else in memory? By definition, this would no longer be an array because `4` would no longer be in contiguous memory. How could we connect different locations in memory?
- Below is an implementation of `list.c`:
    
    ```c
    // Implements a list of numbers with an array of fixed size
    
    #include <stdio.h>
    
    int main(void)
    {
        // List of size 3
        int list[3];
    
        // Initialize list with numbers
        list[0] = 1;
        list[1] = 2;
        list[2] = 3;
    
        // Print list
        for (int i = 0; i < 3; i++)
        {
            printf("%i\n", list[i]);
        }
    ```
    
- Building upon our more recent knowledge, we can use our understanding of pointers to create a better design in this code:
    
    ```c
    // Implements a list of numbers with an array of dynamic size
    
    #include <stdio.h>
    #include <stdlib.h>
    
    int main(void)
    {
        // List of size 3
        int *list = malloc(3 * sizeof(int));
        if (list == NULL)
        {
            return 1;
        }
    
        // Initialize list of size 3 with numbers
        list[0] = 1;
        list[1] = 2;
        list[2] = 3;
    
        // List of size 4
        int *tmp = malloc(4 * sizeof(int));
        if (tmp == NULL)
        {
            free(list);
            return 1;
        }
    
        // Copy list of size 3 into list of size 4
        for (int i = 0; i < 3; i++)
        {
            tmp[i] = list[i];
        }
    
        // Add number to list of size 4
        tmp[3] = 4;
    
        // Free list of size 3
        free(list);
    
        // Remember list of size 4
        list = tmp;
    
        // Print list
        for (int i = 0; i < 4; i++)
        {
            printf("%i\n", list[i]);
        }
    
        // Free list
        free(list);
        return 0;
    }
    ```
    
- It’s useful to think about `list` and `tmp` as both signs that point to a chunk of memory. As in the example above, `list` at one point *pointed* to an array of size 3. By the end, `list` was told to point to a chunk of memory of size 4. Technically, by the end of the above code, `tmp` and `list` both pointed to the same block of memory.
- One way by which we can copy the array without a for loop is by using `realloc`:
    
    ```c
    // Implements a list of numbers with an array of dynamic size using realloc
    
    #include <stdio.h>
    #include <stdlib.h>
    
    int main(void)
    {
        // List of size 3
        int *list = malloc(3 * sizeof(int));
        if (list == NULL)
        {
            return 1;
        }
    
        // Initialize list of size 3 with numbers
        list[0] = 1;
        list[1] = 2;
        list[2] = 3;
    
        // Resize list to be of size 4
        int *tmp = realloc(list, 4 * sizeof(int));
        if (tmp == NULL)
        {
            free(list);
            return 1;
        }
        list = tmp;
    
        // Add number to list
        list[3] = 4;
    
        // Print list
        for (int i = 0; i < 4; i++)
        {
            printf("%i\n", list[i]);
        }
    
        // Free list
        free(list);
        return 0;
    }
    ```
    
- One may be tempted to allocate way more memory than required for the list, such as 30 items instead of the required 3 or 4. However, this is bad design as it taxes system resources when they are not potentially needed. Further, there is little guarantee that memory for more than 30 items will be needed eventually.

---

## Linked Lists

- Recently, we have learned about three useful primitives. A `struct` is a data type that you can define yourself. A `.` in *dot notation* allows you to access variables inside that structure. The `*` operator is used to declare a pointer or dereference a variable.
- Today, we are introduced to the `->` operator. it is an arrow. This operator goes to an address and looks inside a structure.
- A *linked list* is one of the most powerful data structures within C. A linked list allows you to include values that are located in varying areas of memory. They alow you to dynamically grow and shrink the list as needed.
- You might imagine three values stored in three different areas of memory as follows:
    
    ![cs50Week5Slide036.png](cs50Week5Slide036.png)
    
- How could one stitch together these values in a list?
- We could imagine the data picture above as follows:
    
    ![cs50Week5Slide037.png](cs50Week5Slide037.png)
    
- We could utilize more memory to keep track of where the next item is using a pointer.
    
    ![Notice that NULL is utilized to indicate that nothing else is *next* in the list.](cs50Week5Slide041.png)
    
    Notice that NULL is utilized to indicate that nothing else is *next* in the list.
    
- By convention, we would keep one more element in memory, a pointer, that keeps track of the first item in the list, called the *head* of the list.
    
    ![cs50Week5Slide042.png](cs50Week5Slide042.png)
    
- Abstracting away the memory addresses, the list would appear as follows:
    
    ![cs50Week5Slide043.png](cs50Week5Slide043.png)
    
- These boxes are called *nodes*. A *node* contains both an *item* and a pointer called *next*. In code, you can imagine a node as follows:
    
    ```c
    typedef struct node
    {
        int number;
        struct node *next;
    }
    node;
    ```
    
- We can recreate `list.c` to utilize a linked list:
    
    ```c
    // Start to build a linked list by prepending nodes
    
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
        // Memory for numbers
        node *list = NULL;
    
        // Build list
        for (int i = 0; i < 3; i++)
        {
            // Allocate node for number
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                return 1;
            }
            n->number = get_int("Number: ");
            n->next = NULL;
    
            // Prepend node to list
            n->next = list;
            list = n;
        }
        return 0;
    }
    ```
    
- Conceptually, we can imagine the process of creating a linked list. First, `node *list` is declared, but it is of a garbage value.

![cs50Week5Slide055.png](cs50Week5Slide055.png)

- Next, a node called `n` is allocated in memory:

![cs50Week5Slide059.png](cs50Week5Slide059.png)

- Next, the `number` of node `n` is assigned the value `1`.

![cs50Week5Slide064.png](cs50Week5Slide064.png)

- Next, the node’s `next` field is assigned `NULL`.
    
    ![cs50Week5Slide066.png](cs50Week5Slide066.png)
    
- Next, `list` is pointed at the memory location to where `n` points. `n` and `list` now point to the same location in memory.
    
    ![cs50Week5Slide068.png](cs50Week5Slide068.png)
    
- A new node is then created. Both the `number` and `next` field are filled with garbage values.
    
    ![cs50Week5Slide073.png](cs50Week5Slide073.png)
    
- The `number` value of `n`'s node (the new node) is updated to `2`.
    
    ![cs50Week5Slide075.png](cs50Week5Slide075.png)
    
- Also, the `next` field is updated as well.
    
    ![cs50Week5Slide077.png](cs50Week5Slide077.png)
    
- We do not want to lose our connection to any of these nodes, otherwise they may be lost forever (orphaned). Accordingly, `n`'s `next` field is pointed to the same memory location as `list`.
    
    ![cs50Week5Slide084.png](cs50Week5Slide084.png)
    
- Finally, `list` is updated to point at `n`. We now have a linked list of two items.
    
    ![cs50Week5Slide086.png](cs50Week5Slide086.png)
    
- Looking at the diagram of the list, we can see that the last number added is the first number that appears in the list. If we print the list in order, starting the first node, it will appear out of order.
- We can print the list in the correct order as follows:
    
    ```c
    // Print nodes in a linked list with a while loop
    
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
        // Memory for numbers
        node *list = NULL;
    
        // Build list
        for (int i = 0; i < 3; i++)
        {
            // Allocate node for number
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                return 1;
            }
            n->number = get_int("Number: ");
            n->next = NULL;
    
            // Prepend node to list
            n->next = list;
            list = n;
        }
    
        // Print numbers
        node *ptr = list;
        while (ptr != NULL)
        {
            printf("%i\n", ptr->number);
            ptr = ptr->next;
        }
        return 0;
    }
    ```
    
- In this example, inserting into the list always has a running time of O(1), as it only takes a small number of steps to insert nodes to the front of a list.
- The amount of time necessary to search the list is O(n), because the worst case is that we have to search the whole list to find an element. The time complexity for adding elements to the list depends on where the element is added, illustrated in the examples below.
- Linked lists are not stored in a contiguous block of memory. They grow as large as you wish, provided that enough system resources exist. The downside is that more memory is needed to keep track of the list instead of an array. For each element you must store not just its value, but also the pointer to the next node. Further, linked lists cannot be indexed like an array because we need to pass through n-1 elements to find the location of the nth element. Because of this, the list above must be linearly searched. Binary search, therefore, is not possible in a list constructed as above.
- Further, you could place numbers at the end of the list as illustrated in this code.
    
    ```c
    // Appends numbers to a linked list
    
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
        // Memory for numbers
        node *list = NULL;
    
        // Build list
        for (int i = 0; i < 3; i++)
        {
            // Allocate node for number
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                return 1;
            }
            n->number = get_int("Number: ");
            n->next = NULL;
    
            // If list is empty
            if (list == NULL)
            {
                // This node is the whole list
                list = n;
            }
    
            // If list has numbers already
            else
            {
                // Iterate over nodes in list
                for (node *ptr = list; ptr != NULL; ptr = ptr->next)
                {
                    // If at end of list
                    if (ptr->next == NULL)
                    {
                        // Append node
                        ptr->next = n;
                        break;
                    }
                }
            }
        }
    
        // Print numbers
        for (node *ptr = list; ptr != NULL; ptr = ptr->next)
        {
            printf("%i\n", ptr->number);
        }
    
        // Free memory
        node *ptr = list;
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
        return 0;
    }
    ```
    
- Further, you could sort the list as items are added:
    
    ```c
    // Implements a sorted linked list of numbers
    
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
        // Memory for numbers
        node *list = NULL;
    
        // Build list
        for (int i = 0; i < 3; i++)
        {
            // Allocate node for number
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                return 1;
            }
            n->number = get_int("Number: ");
            n->next = NULL;
    
            // If list is empty
            if (list == NULL)
            {
                list = n;
            }
    
            // If number belongs at beginning of list
            else if (n->number < list->number)
            {
                n->next = list;
                list = n; 
            }
    
            // If number belongs later in list
            else
            {
                // Iterate over nodes in list
                for (node *ptr = list; ptr != NULL; ptr = ptr->next)
                {
                    // If at end of list
                    if (ptr->next == NULL)
                    {
                        // Append node
                        ptr->next = n;
                        break;
                    }
    
                    // If in middle of list
                    if (n->number < ptr->next->number)
                    {
                        n->next = ptr->next;
                        ptr->next = n;
                        break;
                    }
                }
            }
        }
    
        // Print numbers
        for (node *ptr = list; ptr != NULL; ptr = ptr->next)
        {
            printf("%i\n", ptr->number);
        }
    
        // Free memory
        node *ptr = list;
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
        return 0;
    }
    ```
    
- This code may seem complicated. However, notice that with pointers and the syntax above, we can stitch data together in different places in memory.

---

## Trees

- Arrays offer contiguous memory that can be searched quickly. Arrays also offer the ability to engage in binary search.
- Could we combine the best of both arrays and linked lists?
- *Binary search trees* are another data structure that can be used to store data more efficiently so that it can be searched and retrieved.
- You can imagine a sorted sequence of numbers:

![cs50Week5Slide118.png](cs50Week5Slide118.png)

- Imagine that the center value becomes the top of a tree, such that those that are less than this value are placed to the left and those that are more than this value are placed to the right.

![cs50Week5Slide119.png](cs50Week5Slide119.png)

- Pointers can be used to point to the current location of each area of memory such that each of these nodes can be connected.

![cs50Week5Slide120.png](cs50Week5Slide120.png)

- In code, this can be implemented as follows:

```c
// Implements a list of numbers as a binary search tree

#include <stdio.h>
#include <stdlib.h>

// Represents a node
typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
}
node;

void free_tree(node *root);
void print_tree(node *root);

int main(void)
{
    // Tree of size 0
    node *tree = NULL;

    // Add number to list
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    n->number = 2;
    n->left = NULL;
    n->right = NULL;
    tree = n;

    // Add number to list
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free_tree(tree);
        return 1;
    }
    n->number = 1;
    n->left = NULL;
    n->right = NULL;
    tree->left = n;

    // Add number to list
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free_tree(tree);
        return 1;
    }
    n->number = 3;
    n->left = NULL;
    n->right = NULL;
    tree->right = n;

    // Print tree
    print_tree(tree);

    // Free tree
    free_tree(tree);
    return 0;
}

void free_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void print_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    print_tree(root->left);
    printf("%i\n", root->number);
    print_tree(root->right);
}
```

- A tree like the above offers dynamism that an array does not offer. It can grow and shrink as needed.
- Further, this structure offers a search time of O(log n) **when the tree is balanced**.

---

## Dictionaries

- *Dictionaries* are another data structure.
- Dictionaries, like actual book-form dictionaries that have a word and a definition, have a *key* and a *value*.
- The *holy grail* of algorithmic time complexity is O(1) or *constant time*. That is, the ultimate is for access to be instantaneous
    
    ![cs50Week5Slide151.png](cs50Week5Slide151.png)
    
- Dictionaries can offer this speed of access through hashing.

---

## Hashing and Hash Tables

- *Hashing* is the idea of taking a value and being able to output a value that becomes a shortcut to it later.
    - For example, hashing *apple* may hash as a value of `1`, and *berry* may be hashed as `2`. Therefore, finding *apple* is as easy as asking the *hash* algorithm where *apple* is stored. While not ideal in terms of design, putting all *a*’s in one bucket and *b*’s in another, this concept of *bucketizing* hashed values illustrates how you can use this concept: a hashed value can be used to shortcut finding such a value.
- A *hash function* is an algorithm that reduces a larger value to something small and predictable. Generally, this function takes in an item you wish to add to your hash table, and returns an integer representing an array index of where that item should be stored.
- A *hash table* is a fantastic combination of both arrays and linked lists. When implemented in code, a hash table is an *array* of *pointers* to *nodes*.
- A hash table can be visualized as follows:
    
    ![Notice that this is simply an array that is assigned each value of the alphabet (0-25 since array is 0-indexed)](cs50Week5Slide157.png)
    
    Notice that this is simply an array that is assigned each value of the alphabet (0-25 since array is 0-indexed)
    
- Then, at each array location, a linked list is used to track each value being stored there:
    
    ![cs50Week5Slide169.png](cs50Week5Slide169.png)
    
- *Collisions* are when you add values to the hash table, and something already exists at the hashed location. Above, collisions are simply appended to the end of the list.
- Collisions can be reduced by better programming your hash table and hash algorithm. You can imagine an improvement as follows:
    
    ![cs50Week5Slide184.png](cs50Week5Slide184.png)
    
- Consider the following example of a hash algorithm:
    
    ![cs50Week5Slide173.png](cs50Week5Slide173.png)
    
- This could be implemented in code as follows:

```c
#include <ctype.h>

unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}
```

- The programmer is the one who has to decide the advantages of using more memory to have a larger hash table and potentially reducing search time or using less memory and potentially increasing search time.
- This structure offers a search time of O(n)

---

## Tries

- *Tries* are another form of data structure. Tries are trees of arrays.
- *Tries* are always searchable in constant time.
- One downside to *tries* is that they tend to take up a large amount of memory. Notice that we need 26 x 4 = 104 `node`s just to store *Toad*!
- *Toad* would be stored as follows:
    
    ![cs50Week5Slide207.png](cs50Week5Slide207.png)
    
- *Tom* would then be stored as follows:
    
    ![cs50Week5Slide209.png](cs50Week5Slide209.png)
    
- This structure offers a search time of O(1).
- The downside of this structure is how many resources are required to use it.

---