CS50_Week4_Memory_Notes

## Welcome

- Lecture goes further into detail on how we represent images using zeros and ones, along with the building blocks that make up files
- Will discuss how to access the underlying data stored in computer memory
- Concepts may take time to fully *click*

---

## Pixel Art

- Pixels are squares, individual dots, of color that are arranged on an up-down, left-right grid.
- You can imagine an image as a map of bits, where zeros represent black and ones represent white. (see below)
    
    ![cs50Week4Slide015.png](cs50Week4Slide015.png)
    

---

## Hexadecimal

- RGB (red, green, blue) are numbers that represent the amount of each of these colors. In Adobe Photoshop, you can see these settings as follows:
    
    ![Notice how the amount of red, blue, and green changes the color selected.](cs50Week4Slide016.png)
    
    Notice how the amount of red, blue, and green changes the color selected.
    
- You can see from the image above that color is not just represented by three values, at the bottom, there is a special value made up of numbers and characters, and `255` is represented as `FF`. Why?
- *Hexadecimal* is a system of counting that has 16 counting values. They are as follows:
    - `0 1 2 3 4 5 6 7 8 9 A B C D E F`
- Hexadecimal is a.k.a. *base-16*
    - When counting in hexadecimal, each column is a power of 16.
- Examples:
    - The number `0` is represented as `00`.
    - The number `1` is represented as `01`.
    - The number `9` is represented by `09`.
    - The number `10` is represented as `0A`.
    - The number `15` is represented as `0F`.
    - The number `16` is represented as `10`.
    - The number `255` is represented as `FF`, because 16 x 15 (or `F`) is 240. Add 15 more to make 255. This is the highest number you can count using a two-digit hexadecimal system.
- Hexadecimal is useful because it can be represented using fewer digits. Hexadecimal allows us to represent information more succinctly.

---

## Memory

- Applying hexadecimal numbering to each of these blocks of memory, you can visualize these as follows:
    
    ![cs50Week4Slide065.png](cs50Week4Slide065.png)
    
- There may be confusion regarding whether the `10` block may represent a location in memory or the value `10`. Because of this, by convention, all hexadecimal numbers are often represented with the `0x` prefix as follows:
    
    ![cs50Week4Slide066.png](cs50Week4Slide066.png)
    
- After typing `code addresses.c`, the following program was written:
    
    ```c
    // Prints an integer
    
    #include <stdio.h>
    
    int main(void)
    {
        int n = 50;
        printf("%i\n", n);
    }
    ```
    
- You can visualize how the program stores this value as follows:
    
    ![cs50Week4Slide070.png](cs50Week4Slide070.png)
    

---

## Pointers

- C has two operators that relate to memory (plus one format code):
    - **`&`** - provides the address of something stored in memory
        - “*Address of* operator”
    - `*`  - instructs the compiler to go to a location in memory
        - “*Dereference* operator”
    - `%p` - print *pointers* using printf
    - *Pointers* are just variables that store the address of something in memory
- We can use this knowledge by modifying our code like this:
    
    ```c
    // Prints an integer's address
    
    #include <stdio.h>
    
    int main(void)
    {
        int n = 50;
        printf("%p\n", &n);
    }
    ```
    
- Consider the following code:
    
    ```c
    int n = 50;
    int *p = &n;
    ```
    
- Modify the code as follows:
    
    ```c
    // Stores and prints an integer's address
    
    #include <stdio.h>
    
    int main(void)
    {
        int n = 50;
        int *p = &n;
        printf("%p\n", p);
    }
    ```
    
- To illustrate the use of the `*` operator, consider the following:
    
    ```c
    // Stores and prints an integer via its address
    
    #include <stdio.h>
    
    int main(void)
    {
        int n = 50;
        int *p = &n;
        printf("%i\n", *p);
    }
    ```
    
- You can visualize the code as follows:
    
    ![Notice the pointer seems rather large. Indeed, a pointer is usually stored as an 8-byte value. `p` is storing the address of the `50`.](cs50Week4Slide078.png)
    
    Notice the pointer seems rather large. Indeed, a pointer is usually stored as an 8-byte value. `p` is storing the address of the `50`.
    
- You can more accurately visualize a pointer as one address that points to another:
    
    ![cs50Week4Slide079.png](cs50Week4Slide079.png)
    

---

## Strings

- Now that we have a mental model for pointers, we can peel back a level of simplification that was offered earlier in the course.
- Code:
    
    ```c
    // Prints a string
    
    #include <cs50.h>
    #include <stdio.h>
    
    int main(void)
    {
        string s = "HI!";
        printf("%s\n", s);
    }
    ```
    
- Recall that a string is simply an array of characters. Ex: `string s = "HI!"` can be represented as follows:
    
    ![cs50Week4Slide085.png](cs50Week4Slide085.png)
    
- What is `s` really? Where is the `s` stored in memory? As you can imagine, `s` needs to be stored somewhere, and you can visualize the relationship of `s` to the string as follows:
    
    ![Notice how a pointer called `s` tells the compiler where the first byte of the string exists in memory.](cs50Week4Slide086.png)
    
    Notice how a pointer called `s` tells the compiler where the first byte of the string exists in memory.
    
- Code:
    
    ```c
    // Prints a string's address as well the addresses of its chars
    
    #include <cs50.h>
    #include <stdio.h>
    
    int main(void)
    {
        string s = "HI!";
        printf("%p\n", s);
        printf("%p\n", &s[0]);
        printf("%p\n", &s[1]);
        printf("%p\n", &s[2]);
        printf("%p\n", &s[3]);
    }
    ```
    
- Code:
    
    ```c
    // Declares a string with CS50 Library
    
    #include <cs50.h>
    #include <stdio.h>
    
    int main(void)
    {
        string s = "HI!";
        printf("%s\n", s);
    }
    ```
    
- Taking off the training wheels, you can modify your code again:
    
    ```c
    // Declares a string without CS50 Library
    
    #include <stdio.h>
    
    int main(void)
    {
        char *s = "HI!";
        printf("%s\n", s);
    }
    ```
    
- You can imagine how a string, as a data type, is created.
- Last week, we learned how to create custom data types as structs.
- The cs50 library includes a struct as follows: `typedef char *string`
- This struct, when using the cs50 library, allows one to use a custom data type called `string`.

---

## Pointer Arithmetic

- Pointer arithmetic is the ability to perform mathematical operations on memory addresses.
- You can modify your code to print out each memory location in the string as follows:
    
    ```c
    // Prints a string's chars
    
    #include <stdio.h>
    
    int main(void)
    {
        char *s = "HI!";
        printf("%c\n", s[0]);
        printf("%c\n", s[1]);
        printf("%c\n", s[2]);
    }
    ```
    
- Further modification:
    
    ```c
    // Prints a string's chars via pointer arithmetic
    
    #include<stdio.h>
    
    int main(void)
    {
        char *s= "HI!";
        printf("%c\n", *s);
        printf("%c\n", *(s + 1));
        printf("%c\n", *(s + 2));
    }
    ```
    
- Likewise, consider:
    
    ```c
    // Prints substrings via pointer arithmetic
    
    #include <stdio.h>
    
    int main(void)
    {
        char *s = "HI!";
        printf("%s\n", s);
        printf("%s\n", s + 1);
        printf("%s\n", s + 2);
    }
    ```
    

---

## String Comparison

- A string of characters is simply an array of characters identified by the location of the first byte.
- Earlier in the course, we considered the comparison of integers. We could represent this in code by typing `code compare.c` into the terminal window as follows:
    
    ```c
    // Compares two integers
    
    #include <cs50.h>
    #include <stdio.h>
    
    int main(void)
    {
        // Get two integers
        int i = get_int("i: ");
        int j = get_int("j: ");
    
        // Compare integers
        if (i == j)
        {
            printf("Same\n");
        }
        else
        {
            printf("Different\n");
        }
    }
    ```
    
- In the case of strings, however, one cannot compare two strings using the `==` operator
- Using the `==` operator in an attempt to compare strings will attempt to compare the memory addresses of the strings instead of the characters stored therein. Consequently,`strcmp` is used.
    
    ```c
    // Compares two strings' addresses
    
    #include <cs50.h>
    #include <stdio.h>
    
    int main(void)
    {
        // Get two strings
        char *s = get_string("s: ");
        char *t = get_string("t: ");
    
        // Compare strings' addresses
        if (s == t)
        {
            printf("Same\n");
        }
        else
        {
            printf("Different\n");
        }
    }
    ```
    
    - Why are these strings seemingly different? You can use the following to visualize why:
        
        ![cs50Week4Slide115.png](cs50Week4Slide115.png)
        
    - Therefore, the code for `compare.c` above is actually attempting to see if the memory addresses are different, not the strings themselves.
    - Using `strcmp`, we can correct the code:
        
        ```c
        // Compares two strings using strcmp
        
        #include <cs50.h>
        #include <stdio.h>
        #include <string.h>
        
        int main(void)
        {
            // Get two strings
            char *s = get_string("s: ");
            char *t = get_string("t: ");
        
            // Compare strings
            if (strcmp(s, t) == 0)
            {
                printf("Same\n");
            }
            else
            {
                printf("Different\n");
            }
        }
        ```
        
    - To further illustrate how these two strings are stored in two different locations, modify the code as follows:
        
        ```c
        // Prints two strings
        
        #include <cs50.h>
        #include <stdio.h>
        
        int main(void)
        {
            // Get two strings
            char *s = get_string("s: ");
            char *t = get_string("t: ");
        
            // Print strings
            printf("%s\n", s);
            printf("%s\n", t);
        }
        ```
        
    - You can see the locations of the two stored strings with a small modification:
        
        ```c
        // Prints two strings' addresses
        
        #include <cs50.h>
        #include <stdio.h>
        
        int main(void)
        {
            // Get two strings
            char *s = get_string("s: ");
            char *t = get_string("t: ");
        
            // Print strings' addresses
            printf("%p\n", s);
            printf("%p\n", t);
        }
        ```
        

---

## Copying and malloc

- A common need in programming is a to copy one string to another
- Implementation of `copy.c`
    
    ```c
    // Capitalizes a string
    
    #include <cs50.h>
    #include <ctype.h>
    #include <stdio.h>
    #include <string.h>
    
    int main(void)
    {
        // Get a string
        string s = get_string("s: ");
    
        // Copy string's address
        string t = s;
    
        // Capitalize first letter in string
        t[0] = toupper(t[0]);
    
        // Print string twice
        printf("s: %s\n", s);
        printf("t: %s\n", t);
    }
    ```
    
- You can visualize the above code as follows:
    
    ![Notice that `s` and `t` are still pointing to the same blocks of memory. This is not a copy of the string. Instead, these are two pointers pointing at the same string.](cs50Week4Slide124.png)
    
    Notice that `s` and `t` are still pointing to the same blocks of memory. This is not a copy of the string. Instead, these are two pointers pointing at the same string.
    
- Before we address this, it’s important to ensure that we don’t experience a *segmentation fault* through our code, where we attempt to copy `string s`to `string t`, where `string t` does not exist. We can employ the `strlen` function as follows to assist with this:
    
    ```c
    // Capitalizes a string, checking length first
    
    #include <cs50.h>
    #include <ctype.h>
    #include <stdio.h>
    #include <string.h>
    
    int main(void)
    {
        // Get a string
        string s = get_string("s: ");
    
        // Copy string's address
        string t = s;
    
        // Capitalize first letter in string
        if (strlen(t) > 0)
        {
            t[0] = toupper(t[0]);
        }
    
        // Print string twice
        printf("s: %s\n", s);
        printf("t: %s\n", t);
    }
    ```
    
- To make an authentic copy of the string, we will need to introduce two new building blocks. First, `malloc` allows you to allocate a block of a specific size of memory. Second, `free` allows you tell to tell the compiler to *free up* that block of memory you previously allocated with `malloc`.
- We can modify our code to create an authentic copy of our string as follows:
    
    ```c
    // Capitalizes a copy of a string
    
    #include <cs50.h>
    #include <ctype.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main(void)
    {
        // Get a string
        char *s = get_string("s: ");
    
        // Allocate memory for another string
        char *t = malloc(strlen(s) + 1);
    
        // Copy string into memory, including '\0'
        for (int i = 0; i <= strlen(s); i++)
        {
            t[i] = s[i];
        }
    
        // Capitalize copy
        t[0] = toupper(t[0]);
    
        // Print strings
        printf("s: %s\n", s);
        printf("t: %s\n", t);
    }
    ```
    
- However, that code is inefficient because we call `strlen(s)` each time the for loop iterates through a location in string `s`.
    
    ```c
    // Capitalizes a copy of a string, defining n in loop too
    
    #include <cs50.h>
    #include <ctype.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main(void)
    {
        // Get a string
        char *s = get_string("s: ");
    
        // Allocate memory for another string
        char *t = malloc(strlen(s) + 1);
    
        // Copy string into memory, including '\0'
        for (int i = 0, n = strlen(s); i <= n; i++)
        {
            t[i] = s[i];
        }
    
        // Capitalize copy
        t[0] = toupper(t[0]);
    
        // Print strings
        printf("s: %s\n", s);
        printf("t: %s\n", t);
    }
    ```
    
- The `C` language has a built-in function to copy strings called `strcpy`. It can be implemented as follows:
    
    ```c
    // Capitalizes a copy of a string using strcpy
    
    #include <cs50.h>
    #include <ctype.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main(void)
    {
        // Get a string
        char *s = get_string("s: ");
    
        // Allocate memory for another string
        char *t = malloc(strlen(s) + 1);
    
        // Copy string into memory
        strcpy(t, s);
    
        // Capitalize copy
        t[0] = toupper(t[0]);
    
        // Print strings
        printf("s: %s\n", s);
        printf("t: %s\n", t);
    }
    ```
    
- Both `get_string` and `malloc` return `NULL`, a special value in memory, in the even that something goes wrong. You can write code that can check for this `NULL` condition as follows:
    
    ```c
    // Capitalizes a copy of a string without memory errors
    
    #include <cs50.h>
    #include <ctype.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int main(void)
    {
        // Get a string
        char *s = get_string("s: ");
        if (s == NULL)
        {
            return 1;
        }
    
        // Allocate memory for another string
        char *t = malloc(strlen(s) + 1);
        if (t == NULL)
        {
            return 1;
        }
    
        // Copy string into memory
        strcpy(t, s);
    
        // Capitalize copy
        if (strlen(t) > 0)
        {
            t[0] = toupper(t[0]);
        }
    
        // Print strings
        printf("s: %s\n", s);
        printf("t: %s\n", t);
    
        // Free memory
        free(t);
        return 0;
    }
    ```
    

---

## Valgrind

- *Valgrind* is a tool that can check for memory-related issues with your programs wherein you utilized `malloc`. Specifically, it checks to see if you `free` all the memory you allocated.
- Consider the following code for `memory.c`:
    
    ```c
    // Demonstrates memory errors via valgrind
    
    #include <stdio.h>
    #include <stdlib.h>
    
    int main(void)
    {
        int *x = malloc(3 * sizeof(int));
        x[1] = 72;
        x[2] = 73;
        x[3] = 33;
    }
    ```
    
- If you type `make memory` followed by `valgrind ./memory`, you will get a report from valgrind that will report where memory has been lost as a result of your program. One error that valgrind reveals is that we attempted to assign the value of `33` at the 4th position of the array, where we only allocated an array of size `3`. Another error is that we never freed `x`.
- You can modify the code to free the memory of `x` as follows:
    
    ```c
    // Demonstrates memory errors via valgrind
    
    #include <stdio.h>
    #include <stdlib.h>
    
    int main(void)
    {
        int *x = malloc(3 * sizeof(int));
        x[1] = 72;
        x[2] = 73;
        x[3] = 33;
        free(x);
    }
    ```
    

---

## Garbage Values

- When you ask the compiler for a block of memory, there is no guarantee that this memory will be empty.
- It’s very possible that the memory you allocated was previously utilized by the computer. Accordingly, you may see *junk* or *garbage values*. This is a result of you getting a block of memory but not initializing it. For example, consider the following code for `garbage.c`:
    
    ```c
    #include <stdio.h>
    #include <stdlib.h>
    
    int main(void)
    {
        int scores[1024];
        for (int i = 0; i < 1024; i++)
        {
            printf("%i\n", scores[i]);
        }
    }
    ```
    

---

## Swapping

- In the real world, swapping two values is very common in programming. It’s hard to swap two variables without a temporary holding space. You can type`code swap.c` and write code as follows to see this in action:
    
    ```c
    // Fails to swap two integers
    
    #include <stdio.h>
    
    void swap(int a, int b);
    
    int main(void)
    {
        int x = 1;
        int y = 2;
    
        printf("x is %i, y is %i\n", x, y);
        swap(x, y);
        printf("x is %i, y is %i\n", x, y);
    }
    
    void swap(int a, int b)
    {
        int tmp = a;
        a = b;
        b = tmp;
    }
    ```
    
- When you pass values to a function, you are only providing copies. The *scope* of `x` and `y` is limited to the main function as the code is presently written. That is, the values of `x` and `y` created in the curly braces of the `main` function only have the scope of the `main` function. In the code above, `x` and `y` are being passed *by value*.
- Consider the following images:
    
    ![Notice that global variables, which have not been used in the course thus far, line in one place in memory. Various functions are stored in the `stack` in another area of memory.](cs50Week4Slide163.png)
    
    Notice that global variables, which have not been used in the course thus far, line in one place in memory. Various functions are stored in the `stack` in another area of memory.
    
    ![Notice that `main` and `swap` have two separate *frames* or areas of memory. Therefore, we cannot simply pass the values from one function to another to change them.](cs50Week4Slide167.png)
    
    Notice that `main` and `swap` have two separate *frames* or areas of memory. Therefore, we cannot simply pass the values from one function to another to change them.
    
- Modify the code as follows:
    
    ```c
    // Swaps two integers using pointers
    
    #include <stdio.h>
    
    void swap(int *a, int *b);
    
    int main(void)
    {
        int x = 1;
        int y = 2;
    
        printf("x is %i, y is %i\n", x, y);
        swap(&x, &y);
        printf("x is %i, y is %i\n", x, y);
    }
    
    void swap(int *a, int *b)
    {
        int tmp = *a;
        *a = *b;
        *b = tmp;
    }
    ```
    
- You can visualize this as follows:
    
    ![cs50Week4Slide198.png](cs50Week4Slide198.png)
    

---

## Overflow

- A *heap overflow* is when you overflow the heap, touching areas of memory you are not supposed to.
- A *stack overflow* is when too many functions are called, overflowing the amount of memory available.
- Both of these are considered *buffer overflows*.

---

## `scanf`

- In CS50, there are functions like `get_int` to simplify the act of getting input from the user.
- `scanf` is a built-in function that can get user input.
- We can reimplement `get_int` using `scanf` as follows:
    
    ```c
    // Gets an int from user using scanf
    
    #include <stdio.h>
    
    int main(void)
    {
        int n;
        printf("n: ");
        scanf("%i", &n);
        printf("n: %i\n", n);
    }
    ```
    
- However, attempting to reimplement `get_string` is not easy. Consider the following:
    
    ```c
    // Dangerously gets a string from user using scanf with array
    
    #include <stdio.h>
    
    int main(void)
    {
        char s[4];
        printf("s: ");
        scanf("%s", s);
        printf("s: %s\n", s);
    }
    ```
    
- Further, your code could be modified as follows. However, we have to pre-allocate a certain amount of memory for a string:
    
    ```c
    // Using malloc
    
    #include <stdio.h>
    #include <stdlib.h>
    
    int main(void)
    {
        char *s = malloc(4);
        if (s == NULL)
        {
            return 1;
        }
        printf("s: ");
        scanf("%s", s);
        printf("s: %s\n", s);
        free(s);
        return 0;
    }
    ```
    
- Simplifying the code, we can further understand this essential problem of pre-allocation:
    
    ```c
    #include <stdio.h>
    
    int main(void)
    {
        char s[4];
        printf("s: ");
        scanf("%s", s);
        printf("s: %s\n", s);
    }
    ```
    
- Sometimes, the compiler of or the system running it may allocate more memory that we indicate. Fundamentally, the above code is unsafe because we cannot trust that the user will input a string that fits into our pre-allocated memory.

---

## File I/O

- You can read from and manipulate files. While this topic will be discussed further in later week, consider the following code for `phonebook.c`:
    
    ```c
    // Saves names and numbers to a CSV file
    
    #include <cs50.h>
    #include <stdio.h>
    #include <string.h>
    
    int main(void)
    {
        // Open CSV file
        FILE *file = fopen("phonebook.csv", "a");
    
        // Get name and number
        char *name = get_string("Name: ");
        char *number = get_string("Number: ");
    
        // Print to file
        fprintf(file, "%s,%s\n", name, number);
    
        // Close file
        fclose(file);
    }
    ```
    
- You can create a file called `phonebook.csv` in advance of running the above code. After running the program and inputting a name and phone number, you will notice that this data persists in your CSV file.
- If we want to ensure that `phonebook.csv` exists prior to running the program, we can modify our code as follows:
    
    ```c
    // Saves names and numbers to a CSV file
    
    #include <cs50.h>
    #include <stdio.h>
    #include <string.h>
    
    int main(void)
    {
        // Open CSV file
        FILE *file = fopen("phonebook.csv", "a");
        if (!file)
        {
            return 1;
        }
    
        // Get name and number
        char *name = get_string("Name: ");
        char *number = get_string("Number: ");
    
        // Print to file
        fprintf(file, "%s,%s\n", name, number);
    
        // Close file
        fclose(file);
    }
    ```
    
- We can implement our own copy program by typing `code cp.c` and writing code as follows:
    
    ```c
    // Copies a file
    
    #include <stdio.h>
    #include <stdint.h>
    
    // stdint.h gives fixed-width integer types like uint8_t,
    // which is an unsigned 1-byte (8-bit) integer. Good for
    // reading raw bytes
    typedef uint8_t BYTE;
    
    int main(int argc, char *argv[])
    {
        FILE *src = fopen(argv[1], "rb");
        FILE *dst = fopen(argv[2], "wb");
    
        BYTE b;
    
        while (fread(&b, sizeof(b), 1, src) != 0)
        {
            fwrite(&b, sizeof(b), 1, dst);
        }
    
        fclose(dst);
        fclose(src);
    }
    ```
    
- BMPs are also an assortment of data that we can examine and manipulate.b2bb.md…]()
