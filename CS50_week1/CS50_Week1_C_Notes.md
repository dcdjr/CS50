# CS50_Week1_C_Notes

## Key Concepts Summary

- Compiling C code (`make hello`, `./hello`)
- Data types and variables
- Loops (while, for)
- Functions & scope
- Terminal commands
- Debugging with `debug50`
- Using `man` for documentation
- Style conventions (indentation, comments, readability)

---

## Basic C Program Example

```c
#include <stdio.h>int main(void){    printf("hello, world\n");}
```

---

## Header Files & Libraries

- **Header file (.h):** Contains built-in functionality (e.g., `stdio.h` provides `printf`)
- **Libraries:** Code written by others, accessed through header files

---

## Terminal Commands

```markdown
code hello.c       # Create/edit the file
make hello         # Compile the code
./hello            # Run the program
ls                 # List files in directory
cd                 # Change directory
cp                 # Copy file
mkdir              # Make new directory
mv                 # Move/rename file
rm                 # Delete file
rmdir              # Delete directory
man <command>      # Show manual for command
```

---

## Format Codes (Placeholders)

- `%s` - String
- `%i` - Integer
- `%f` - Floating point number

---

## Escape Sequences

- `\n` - Newline
- `\r` - Return to start of line
- `\"` - Double quote
- `\'` - Single quote
- `\\` - Backslash

---

## Data Types

- `bool` - true/false (`#include <stdbool.h>`)
- `char` - single character (use single quotes)
- `double` / `float` - real numbers
- `long` - larger integers
- `int` - integer
- `string` - string of text (`#include <cs50.h>`)

---

## Operators

- `=` Assignment
- `<` Less than
- `<=` Less than or equal
- `>` Greater than
- `>=` Greater than or equal
- `==` Equal
- `!=` Not equal
- `&&` Logical AND
- `||` Logical OR
- `!` Logical NOT

---

## Variables & Scope

- Variables exist only in the `{}` block where they are defined (scope)

---

## Debugging

- `debug50 ./program` — Step through your code to find errors
- Common issues: uninitialized variables, missing semicolons, unmatched braces

---

## Style Tips

- Use consistent indentation (4 spaces)
- Comment your code where needed
- Keep functions small and focused
- Follow CS50 style guide

---

## Sample Programs

### String Input

```c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string answer = get_string("What's your name? ");
    printf("hello, %s\n", answer);
}
```

### Conditionals (yes/no)

```c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    char c = get_char("Do you agree? ");
    if (c == 'y' || c == 'Y')
    {
        printf("Agreed.\n");
    }
    else if (c == 'n' || c == 'N')
    {
        printf("Not agreed.\n");
    }
}
```

### Loop (while)

```c
#include <stdio.h>

int main(void)
{
    int i = 0;
    while (i < 3)
    {
        printf("meow\n");
        i++;
    }
}
```

### Loop (for)

```c
#include <stdio.h>

int main(void)
{
    for (int i = 0; i < 3; i++)
    {
        printf("meow\n");
    }
}
```

---

## Functions

### Function with no arguments

```c
#include <cs50.h>
#include <stdio.h>

void meow(void);

int main(void)
{
    for (int i = 0; i < 3; i++)
    {
        meow();
    }
}

void meow(void)
{
    printf("meow\n");
}
```

### Function with arguments

```c
#include <cs50.h>
#include <stdio.h>

void meow(int n);

int main(void)
{
    meow(5);
}

void meow(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("meow\n");
    }
}
```

### Get positive integer

```c
#include <cs50.h>
#include <stdio.h>

int get_positive_int(void);
void meow(int n);

int main(void)
{
    int times = get_positive_int();
    meow(times);
}

int get_positive_int(void)
{
    int n;
    do
    {
        n = get_int("Number: ");
    }
    while (n < 1);
    return n;
}

void meow(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("meow\n");
    }
}
```

---

## Mario Example

```c
#include <stdio.h>

void print_row(int n);

int main(void)
{
    const int n = 3;
    for (int i = 0; i < n; i++)
    {
        print_row(n);
    }
}

void print_row(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
}
```

---

## Calculator & Overflow Example

```c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int dollars = 1;
    while (true)
    {
        char c = get_char("Here's %i. Double it and give it to the next person? ", dollars);
        if (c == 'y')
        {
            dollars *= 2;
        }
        else
        {
            break;
        }
    }
}
```

**Integer overflow:** If you double an integer enough times, it will exceed the number of bits available and wrap around.

---

## Float Precision Example

```c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x = get_int("x: ");
    int y = get_int("y: ");

    printf("%.50f\n", (float) x / y);
}
```

---

**Additional Notes:**

- `debug50` is a very useful tool for finding logic errors, use it frequently!
- You can access documentation for most commands with `man <command>` (good habit to check before googling).
- Clear code style and commenting help you and others read your code easily, start doing this from Week 1.
