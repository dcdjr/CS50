# CS50_Week2_Arrays_Notes

## Links

- [Lecture](https://learning.edx.org/course/course-v1:HarvardX+CS50+X/block-v1:HarvardX+CS50+X+type@sequential+block@52442dc728364068a280526913bb390e/block-v1:HarvardX+CS50+X+type@vertical+block@9750224b4083487a9891234857f088f3)
- [Problem Set 2](https://cs50.harvard.edu/x/2025/psets/2/)
- [CS50 IDE](https://verbose-cod-9x75jg9rq9qfgp5.github.dev/?autoStart=true&folder=%2Fworkspaces%2F75383640&vscodeChannel=stable)

---

## Beginning of Lecture

### Cryptography

- The art of scrambling information to ensure secure communication.

### Compilation

- Translating source code into machine code to create an executable program.

### Make vs. Clang

- `make` is not a compiler, but it automates the process of compilation.
- Under the hood, `make` uses `clang`, which is the actual compiler.
- Example:
    - `clang -o hello hello.c` → Compiles hello.c into an executable called `hello`.
    - `clang -o hello hello.c -lcs50` → Same, but links the CS50 library.

### What happens when you compile?

```
source code → preprocessing → compiling → assembling → linking → executable
```

### Preprocessing

- Handles all lines beginning with `#` (preprocessor directives).
- Example:

```c
#include <stdio.h>
```

- The preprocessor copies necessary function prototypes and constants from the library into the code.

### Compiling

- Converts preprocessed code into **assembly code***,* human-readable low-level instructions for the CPU.

### Assembling

- Converts assembly into **machine code** (binary: 0s and 1s).

### Linking

- Combines machine code from all the program’s files and linked libraries into one executable file.

### Compilation Example

```bash
make hello
clang -o hello hello.c
clang -o hello hello.c -lcs50
```

---

## Reverse Engineering

### Can you reverse engineer compiled code?

- You can go from **machine code → assembly**, but cannot fully recover original high-level structures.
    - Example: You can’t always tell if a loop was originally written as a `for` loop, `while` loop, or recursion.
- Reverse engineering is typically only partial — high-level logic and style are lost.
- If you’re smart enough to reverse engineer a complex program, you might be better off rewriting it from scratch.

---

## Debugging

### Printf Debugging

```c
#include <stdio.h>

int main(void)
{
    for (int i = 0; i <= 3; i++)
    {
        printf("i is %i\n", i);
        printf("#\n");
    }
}
```

- Simple but effective: Insert `printf()` statements to check variable values or program flow.

### Using debug50

- `debug50` is a command that runs the built-in debugger from Visual Studio Code.
- Lets you step through code line-by-line, check variable values, and control program execution.

### Breakpoints

- Mark specific lines in your code where execution will pause.
- Useful for:
    - Inspecting variable values at a certain point.
    - Testing how loops and conditionals behave.
    - Finding infinite loops or logic errors.

### Other Debugging Tips

- Always test edge cases.
- Use meaningful variable names to make bugs easier to spot.
- Work incrementally: test small parts of your code before adding more.

---

## Types Again

| **bool** | 1 byte |
| --- | --- |
| **int** | 4 bytes |
| **long** | 8 bytes |
| **float** | 4 bytes |
| **double** | 8 bytes |
| **char** | 1 byte |
| **string** | ? bytes |

---

## Memory/Arrays

```c
#include <stdio.h>

int main(void)
{
    int score1 = 72;
    int score2 = 73;
    int score3 = 33;

    // Print average
    printf("Average: %f\n", (score1 + score2 + score3) / 3.0);
}
```

- **Array:** a data structure that is made up of a sequence of values back-to-back (contiguous) in memory, where all of the values are the same data type.

```c
int scores[3];

scores[0] = 72;
scores[1] = 73;
scores[2] = 33;
```

- Constant variables are usually denoted by a capital letter by convention

```c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    const int N = 3;
    int scores[N];
    //
    for (int i = 0; i < N; i++)
    {
        scores[i] = get_int("Score: ");
    }

    // Print average
    printf("Average: %f\n", (scores[0] + scores[1] + scores[2]) / (float) N);
}

```

```c
#include <cs50.h>
#include <stdio.h>

// constant
const int N = 3;

// prototype
float average(int length, int array[]);

int main(void)
{
    // get scores
    int scores[N];
    for (int i = 0; i < N; i++)
    {
        scores[i] = get_int("Score: ");
    }

    // print average
    printf("Average: %f\n", average(N, scores));
}

float average(int length, int array[])
{
    // calculate average
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    }
    return sum / (float) length;
}

```

```c
#include <stdio.h>

int main(void)
{
    char c1 = 'H';
    char c2 = 'I';
    char c3 = '!';

    printf("%i %i %i\n", c1, c2, c3);
}

```

- A **string** is actually an array of characters because each character is stored as 1 byte contiguously in memory, which fits the definition of an array.
- How does the computer track where the bits are stored?
    - The way computers keep track of the end of an array (or a string) is by placing an extra byte at the end of the contiguous data filled with all zeros, and that way it knows it reached the end. (typically denoted by \0) also called NUL.
    

```c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string words[2];
    words[0] = "HI!";
    words[1] = "BYE!";

    printf("%s\n", words[0]);
    printf("%s\n", words[1]);
}
```

```c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string words[2];
    words[0] = "HI!";
    words[1] = "BYE!";

    printf("%c%c%c\n", words[0][0], words[0][1], words[0][2]);
    printf("%c%c%c%c\n", words[1][0], words[1][1], words[1][2], words[1][3]);
}
```

- The above programs have the same output, the right case uses the format code `%c` instead of `%s` because you use the double square bracket notation (i.e. `words[x][x]` ) to first identify the string in the array with the first set of brackets, and the character within that string with the second set of brackets.

```c
#include <cs50.h>
#include <stdio.h>

int string_length(string s);

int main(void)
{
    // prompting for name to be inputted
    string name = get_string("Name: ");

    // calls get_length(), then stores return value as variable "length"
    int length = string_length(name);

    // prints the length of the given name
    printf("%i\n", length);
}

int string_length(string s)
{
    int n = 0;
    while (s[n] != 0)
    {
        n++;
    }
    return n;
}
```

```c
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int string_length(string s);

int main(void)
{
    string name = get_string("Name: ");
    int length = strlen(name);
    printf("%i\n", length);
}

```

- Another library is the ctype.h library, which gives access to functions like:
    - [isalnum](https://manual.cs50.io/3/isalnum) - check whether a character is alphanumeric
    - [isalpha](https://manual.cs50.io/3/isalpha) - check whether a character is alphabetical
    - [isblank](https://manual.cs50.io/3/isblank) - check whether a character is blank (i.e., a space or tab)
    - [isdigit](https://manual.cs50.io/3/isdigit) - check whether a character is a digit
    - [islower](https://manual.cs50.io/3/islower) - check whether a character is lowercase
    - [ispunct](https://manual.cs50.io/3/ispunct) - check whether a character is punctuation
    - [isspace](https://manual.cs50.io/3/isspace) - check whether a character is whitespace (e.g., a newline, space, or tab)
    - [isupper](https://manual.cs50.io/3/isupper) - check whether a character is uppercase
    - [tolower](https://manual.cs50.io/3/tolower) - convert a `char` to lowercase
    - [toupper](https://manual.cs50.io/3/toupper) - convert a `char` to uppercase

```c
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("Input: ");
    printf("Output: ");
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        printf("%c", s[i]);
    }
    printf("\n");
}

```

```c
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("Before: ");
    printf("After:  ");
    // iterates through the string
    for (int i = 0, n = strlen(s); i < n; i++)
    {
		    // conditional checks if the ith character of string s is between 97 and 122 (lowercase)
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            // change i to uppercase by subtracting the ith char (which is just an int) by 32
            printf("%c", s[i] - ('a' - 'A'));
        }
        else
        {
            // Just print s[i]
            printf("%c", s[i]);
        }
    }
    printf("\n");
}
```

```c
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("Before: ");
    printf("After:  ");
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        printf("%c", toupper(s[i]));
    }
    printf("\n");
}
```

## Command line arguments

- How do we write code that accesses words at the command line?

```c
#include <stdio.h>

int main(void)
{
		...
}
```

```c
#include <stdio.h>

int main(int argc, string argv[])
{
		...
}
```

```c
#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        printf("hello, %s\n", argv[1]);
    }
    else
    {
        printf("hello, world\n");
    }
}
```

- argc = “argument count" | argv = "argument vector"
- `argv[0]` contains the name of the program, `argv[1]` is where the human-typed words start

## Exit Status

- Why does main return an int?
    - Programs return numbers to signal methodically whether or not something succeeded or failed.
- Example: 404 (file not found)
- `echo $?` can be used to print the exit status of the most recently ran command

## Cryptography

- encryption: scrambling information in a reversible way
- an encryption program takes the message and a key as input, the key is only known to the sender and the recipient so that the same algorithm can be used without being easily deciphered.
    - Example: caeser cypher. HI! (with key:1 to indicate the shifting of letters in the alphabet as 1 to the right) = IJ!
