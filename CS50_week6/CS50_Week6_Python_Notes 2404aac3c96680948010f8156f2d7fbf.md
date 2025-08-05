# CS50_Week6_Python_Notes

## Hello Python!

- Humans, over time, have seen how design decisions of prior programming languages could be improved upon.
- Python is a higher-level programming language that builds upon what we already learned in C.
- Python additionally has access to a vast number of user-created libraries.
- Unlike in C, which is a *compiled language*, Python is an *interpreted language*, where you don’t need to separately compile your program. Rather, you run the program in the *Python Interpreter*.
- Up until now, the code has looked like this:

```c
// A program that says hello to the world

#include <stdio.h>

int main(void)
{
    printf("hello, world\n");
}
```

- With Python, the process of writing and compiling code has been simplified. For example:

```python
# A program that says hello to the world

print("hello, world")
```

- Python notably can implement what was quite complicated in C with relative simplicity.

---

## Speller

- To illustrate this simplicity, dictionary.c can be improved upon using Python as follows:

```python
# Words in dictionary
words = set()

def check(word):
    """Return true if word is in dictionary else false"""
    return word.lower() in words

def load(dictionary):
    """Load dictionary into memory, returning true if successful else false"""
    with open(dictionary) as file:
        words.update(file.read().splitlines())
    return True

def size():
    """Returns number of words in dictionary if loaded else 0 if not yet loaded"""
    return len(words)

def unload():
    """Unloads dictionary from memory, returning true if successful else false"""
    return True
```

- The code shows why higher-level languages exist: To simplify and facilitate easier code writing.
- However, speed may be a tradeoff. In C, since the programmer handles memory management, it may run faster than Python,  depending on the code’s implementation. While C only runs your lines of code, Python runs all the code that comes under the hood with it when you call Python’s built-in functions.

---

## Filter

- Another program that can be simplified is `filter.c` written in week 4’s pset.

```python
# Blurs an image

from PIL import Image, ImageFilter

# Blur image
before = Image.open("bridge.bmp")
after = before.filter(ImageFilter.BoxBlur(1))
after.save("out.bmp")
```

- Further:

```python
# Finds edges in an image

from PIL import Image, ImageFilter

# Find edges
before = Image.open("bridge.bmp")
after = before.filter(ImageFilter.FIND_EDGES)
after.save("out.bmp")
```

- Python allows the programmer to abstract away code that would be much more complicated with C and other *lower-level* programming languages.

---

## Functions

- In C, functions are seen as follows:

```c
printf("hello, world\n");
```

- In Python, you will see functions as follows:

```python
print("hello, world")
```

---

## Libraries, Modules, and Packages

- The CS50 library can also be used with Python
- The following functions will be of particular use:

```python
get_float
get_int
get_string
```

- You can import the CS50 library as follows:

```python
import cs50
```

- You also have the option of importing specific functions from the library as follows:

```python
from cs50 import get_float, get_int, get_string
```

---

## Strings

- In C, you might remember this code:

```c
// get_string and printf with %s

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string answer = get_string("What's your name? ");
    printf("hello, %s\n", answer);
}
```

- This code in Python is:

```python
# get_string and print, with concatenation

from cs50 import get_string

answer = get_string("What's your name? ")
print("hello, " + answer)
```

- Similarly, this can be done without concatentation:

```python
# get_string and print, without concatenation

from cs50 import get_string

answer = get_string("What's your name? ")
print("hello,", answer)
```

- Similarly, you could implement the above code as follows:

```python
# get_string and print, with format strings

from cs50 import get_string

answer  = get_string("What's your name? ")
print(f"hello, {answer}")
```

---

## Positional Parameters and Named Parameters

- Functions in C like `fread`, `fwrite`, and `printf` use positional arguments, where you provide arguments with commas as separators. You must remember what argument is in which position. These are referred to as *positional parameters*.
- In Python, *named parameters* allow you to provide arguments without regard to positionality.
- Accessing the official Python documentation, you may see the following:

```python
print(*objects, sep=' ', end='\n', file=None, flush=False)
```

---

## Variables

- Variable declaration is simplified too. in C, you might have `int counter = 0;`. In Python, this same line would read `counter = 0`. You need not declare the type of the variable.
- Python favors `counter += 1` to increment by one, losing the ability found in C to type counter++;

---

## Types

- Data types in Python do need to be explicitly declared. For example, the `answer` variable above is a string, but you don’t have to tell the interpreter this was the case, as it knew on its own.
- In Python, commonly used types include:

```python
  bool
  float
  int
  str
```

- Some other data types in Python include:

```python
range   sequence of numbers
list    sequence of mutable values
tuple   sequence of immutable values
dict    collection of key-value pairs
set     collection of unique values
```

- Each of these data types can be implemented in C, but in Python, they can be implemented more simply.

---

## Calculator

- You might recall `calculator.c` from earlier in this course:

```c
// Addition with int

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for x
    int x = get_int("x: ");

    // Prompt user for y
    int y = get_int("y: ");

    // Perform addition
    printf("%i\n", x + y);
}
```

- We can implement a simple calculator just as we did with C.

```python
# Addition with int [using get_int]

from cs50 import get_int

# Prompt user for x
x = get_int("x: ")

# Prompt user for y
y = get_int("y: ")

# Perform addition
print(x + y)
```

- It’s possible to remove the training wheels of the cs50 library:

```python
# Addition with int [using input]

# Prompt user for x
x = input("x: ")

# Prompt user for y
y = input("y: ")

# Perform addition
print(x + y)
```

- It turns out the interpreter understood `x` and `y` to be strings, and concatenates them rather than adding them as ints. The fix can be implemented as follows:

```python
# Addition with int [using input]

# Prompt user for x
x = int(input("x: "))

# Prompt user for y
y = int(input("y: "))

# Perform addition
print(x + y)
```

---

## Conditionals

- In C, you may remember a program like this:

```c
// Conditionals, Boolean expressions, relational operators

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for integers
    int x = get_int("What's x? ");
    int y = get_int("What's y? ");

    // Compare integers
    if (x < y)
    {
        printf("x is less than y\n");
    }
    else if (x > y)
    {
        printf("x is greater than y\n");
    }
    else
    {
        printf("x is equal to y\n");
    }
}
```

- In Python, it would appear like this:

```python
# Conditionals, Boolean expressions, relational operators

from cs50 import get_int

# Prompt user for integers
x = get_int("What's x? ")
y = get_int("What's y? ")

# Compare integers
if x < y:
    print("x is less than y")
elif x > y:
    print("x is greater than y")
else:
    print("x is equal to y")
```

- Further looking at comparisons, consider the following code in C:

```c
// Logical operators

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user to agree
    char c = get_char("Do you agree? ");

    // Check whether agreed
    if (c == 'Y' || c == 'y')
    {
        printf("Agreed.\n");
    }
    else if (c == 'N' || c == 'n')
    {
        printf("Not agreed.\n");
    }
}
```

- The above code can be implemented as follows:

```python
# Logical operators

from cs50 import get_string

# Prompt user to agree
s = get_string("Do you agree? ")

# Check whether agreed
if s == "Y" or s == "y":
    print("Agreed.")
elif s == "N" or s == "n":
    print("Not agreed.")
```

- Another approach to this same code could be as follows, using *lists:*

```python
# Logical operators, using lists

from cs50 import get_string

# Prompt user to agree
s = get_string("Do you agree? ")

# Check whether agreed
if s in ["y", "yes"]:
    print("Agreed.")
elif s in ["n", "no"]:
    print("Not agreed.")
```

---

## Object-Oriented Programming

- In Python, certain values can not only store data through properties or attributes, but can also include functions that operate on that data. These values are known as *objects*.
- In C, we can use a `struct` to group multiple variables into a custom data type. Python expands on this idea by allowing us to include both data (attributes) and behavior (functions) within a single user-defined type. When a function is tied to a specific object, it is referred to as a *method*.
- For example. `strs` in Python have built-in *methods*. Therefore, you could modify the above code as follows:

```python
# Logical operators, using lists

# Prompt user to agree
s = input("Do you agree? ").lower()

# Check whether agreed
if s in ["y", "yes"]:
    print("Agreed.")
elif s in ["n", "no"]:
    print("Not agreed.")
```

- Similarly, you can recall how we copied a string in C:

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

- We can implement the above in Python as follows:

```python
# Capitalizes a copy of a string

# Get a string
s = input("s: ")

# Capitalize copy of string
t = s.capitalize()

# Print strings
print(f"s: {s}")
print(f"t: {t}")
```

---

## Loops

- Loops in Python are very similar to C. You may recall the following C code:

```c
// Demonstrates for loop

#include <stdio.h>

int main(void)
{
    for (int i = 0; i < 3; i++)
    {
        printf("meow\n");
    }
}
```

- `for` loops can be implemented in Python as follows:

```python
# Better design

for i in range(3):
    print("meow")
```

- Further, a `while`loop can be implemented as follows:

```python
# Demonstrates while loop

i = 0
while i < 3:
    print("meow")
    i += 1
```

- `uppercase.py`:

```python
# Uppercases string one character at a time

before = input("Before: ")
print("After:  ", end="")
for c in before:
    print(c.upper(), end="")
print()
```

- Reading the documentation, we discover that Python has methods that can be implemented upon the entire string as follows:

```python
# Uppercases string all at once

before = input("Before: ")
after = before.upper()
print(f"After:  {after}")
```

---

## Abstraction

- You can further improve the code by using functions and abstracting away various code into functions. Modify [`meow.py`](http://meow.py) as such:

```python
# Abstraction

def main():
    for i in range(3):
        meow()

# Meow once
def meow():
    print("meow")

main()
```

- We can pass variables between our functions as follows:

```python
# Abstraction with parameterization

def main():
    meow(3)

# Meow some number of times
def meow(n):
    for i in range(n):
        print("meow")

```

---

## Truncation and Floating Point Imprecision

- Recall that in C, we experienced truncation where one integer is divided by another could result in an imprecise result.
- You can see how python handles such division as follows:

```python
# Division with integers, demonstration lack of truncation

# Prompt user for x
x = int(input("x: "))

# Prompt user for y
y = int(input("y: "))

# Divide x by y
z = x / y
print(z)
```

- We can reveal this imprecision by modifying the code slightly:

```python
# Floating-point imprecision

# Prompt user for x
x = int(input("x: "))

# Prompt user for y
y = int(input("y: "))

# Divide x by y
z = x / y
print(f"{z:.50f}")
```

---

## Exceptions

- Modify [`calculator.py`](http://calculator.py) as follows:

```python
# Doesn't handle exception

# Prompt user for an integer
n = int(input("Input: "))
print("Integer")
```

- We can `try` to handle and *catch* potential exception by modifying our code as follows:

```python
# Handles exception

# Prompt user for an integer
try:
    n = int(input("Input: "))
    print("Integer.")
except ValueError:
    print("Not integer.")
```

---

## Mario

- Recall that a previous challenge in the course was building three blocks on top of one another, like in Mario.
- In Python, we can implement something akin to this as follows:

```python
# Prints a column of 3 bricks with a loop

for i in range(3):
    print("#")
```

- In C. we had the advantage of `do-while` loop. However, in Python, it is conventional to utilize a `while` loop, as Python does not have a `do-while` loop. You can write code as follows in a file called `mario.py`:

```python
# Prints a column of n bricks with a loop

from cs50 import get_int

while True:
    n = get_int("Height: ")
    if n > 0:
        break

for i in range(n):
    print("#")
```

- In Python, we could implement by modifying your code as follows:

```python
# Prints a row of 4 question marks with a loop

for i in range(4):
    print("?", end="")
print()
```

- Similar in spirit to previous iterations, we can further simplify this program:

```python
# Prints a row of 4 question marks without a loop

print("?" * 4)
```

- What about a large block of bricks? To implement it:

```python
# Prints a 3-by-3 grid of bricks with loops

for i in range(3):
    for j in range(3):
        print("#", end="")
    print()
```

- You can learn more about the `print` function in the python documentation.

---

## Lists

- `list`s are a data structure in Python
- `list`s have built-in methods or functions within them
- For example, consider the following code:

```python
# Averages three numbers using a list

# Scores
scores = [72, 73, 33]

# Print average
average = sum(scores) / len(scores)
print(f"Average: {average}")
```

- You can even utilize the following syntax to get values from the user:

```python
# Averages three numbers using a list and a loop

from cs50 import get_int

# Get scores
scores = []
for i in range(3):
    score = get_int("Score: ")
    scores.append(score)

# Print average
average = sum(scores) / len(scores)
print(f"Average: {average}")
```

---

## Searching and Dictionaries

- We can also search within a data structure
- Consider a program called [`phonebook.py`](http://phonebook.py) as follows:

```python
# Implements linear search for names using loop

# A list of names
names = ["Yuliia", "David", "John"]

# Ask for name
name = input("Name: ")

# Search for name
for n in names:
    if name == n:
        print("Found")
        break
else:
    print("Not found")
```

- However, we don’t need to iterate through a list. in Python, we can execute linear search as follows:

```python
# Implements linear search for names using `in`

# A list of names
names = ["Yuliia", "David", "John"]

# Ask for name
name = input("Name: ")

# Search for name
if name in names:
    print("Found")
else:
    print("Not found")
```

- Recall that a *dictionary* or `dict` is a collection of *key* and *value* pairs.
- You can implement a dictionary in Python as follows:

```python
# Implements a phone book as a list of dictionaries, without a variable

from cs50 import get_string

people = [
    {"name": "Yuliia", "number": "+1-617-495-1000"},
    {"name": "David", "number": "+1-617-495-1000"},
    {"name": "John", "number": "+1-949-468-2750"},
]

# Search for name
name = get_string("Name: ")
for person in people:
    if person["name"] == name:
        print(f"Found {person['number']}")
        break
else:
    print("Not found")
```

- Even better, we don’t need both a `name` and a `number`. We can simplify this code as follows:

```python
# Implements a phone book using a dictionary

from cs50 import get_string

people = {
    "Yuliia": "+1-617-495-1000",
    "David": "+1-617-495-1000",
    "John": "+1-949-468-2750",
}

# Search for name
name = get_string("Name: ")
if name in people:
    print(f"Number: {people[name]}")
else:
    print("Not found")
```

- Python has done their best to get to constant time using their built-in searches.

---

## Command-Line Arguments

- As with C, you can also utilize command-line arguments. Consider the following code:

```python
# Prints a command-line argument

from sys import argv

if len(argv) == 2:
    print(f"hello, {argv[1]}")
else:
    print("hello, world")
```

---

## Exit Status

- The `sys` library also has built-in methods. We can use `sys.exit(i)` to exit the program with a specific exit code:

```python
# Exits with explicit value, importing sys

import sys

if len(sys.argv) != 2:
    print("Missing command-line argument")
    sys.exit(1)

print(f"hello, {sys.argv[1]}")
sys.exit(0)
```

---

## CSV Files

- Python has built-in support for CSV files.
- Modify [`phonebook.py`](http://phonebook.py) as follows:

```python
import csv

file = open("phonebook.csv", "a")

name = input("Name: ")
number = input("Number: ")

writer = csv.writer(file)
writer.writerow([name,number])

file.close()
```

- While `file.close` and `file = open` are commonly used and available syntax in Python, this code can be improved as follows:

```python
import csv

name = input("Name: ")
number = input("Number: ")

with open("phonebook.csv", "a") as file:

    writer = csv.writer(file)
    writer.writerow([name,number])
```

- Similarly, we can write a dictionary as follows within the CSV file:

```python
import csv

name = input("Name: ")
number = input("Number: ")

with open("phonebook.csv", "a") as file:

    writer = csv.DictWriter(file, fieldnames=["name", "number"])
    writer.writerow({"name": name, "number": number})
```

---

## Third-Party Libraries

- One of the advantages of Python is its massive user base and similarly large number of third-party libraries.
- You can install the CS50 Library on your own computer by typing `pip install cs50`, provided you have [Python](https://python.org/) installed.
- Considering other libraries, David demoed the use of `cowsay` and `qrcode`.