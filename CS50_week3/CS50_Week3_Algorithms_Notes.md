# CS50_Week3_Algorithms_Notes

## Overview: Problem Solving with Data

When working with data in computer science, we need efficient ways to find and organize information. This week focuses on two fundamental approaches:

- **Searching:** Using algorithms to locate specific data in memory
- **Sorting:** Organizing data in a particular order (covered later in the lecture)

---

## Search Algorithms

### Linear Search

- **Concept:** Examines each element one by one from start to finish
- **Requirements:** No special data organization needed
- **Process:** Check first element, then second, then third, etc., until target is found or all elements are checked
- **Real-world analogy:** Looking through a phone book page by page

### Binary Search

- **Concept:** Repeatedly divides the search space in half
- **Requirements:** Data must be sorted beforehand
- **Process:**
    1. Check the middle element
    2. If target equals middle element, found!
    3. If target is less than middle, search left half
    4. If target is greater than middle, search right half
    5. Repeat until found or search space is empty
- **Real-world analogy:** Looking up a word in a dictionary by opening to the middle and deciding which half contains your word

---

## Algorithm Analysis: Big O Notation

Understanding how algorithms perform as data size grows is crucial. We use **asymptotic notation** to describe running time:

### Notation Types

| Symbol | Meaning | Description |
| --- | --- | --- |
| **O** (Big O) | Upper bound | Worst-case scenario - maximum time an algorithm could take |
| **Ω** (Big Omega) | Lower bound | Best-case scenario - minimum time an algorithm could take |
| **Θ** (Big Theta) | Tight bound | Used when upper and lower bounds are the same |

### Common Running Times

| Running Time | Algorithm Examples | Description |
| --- | --- | --- |
| **O(n²)** | Bubble Sort, Selection Sort | Quadratic - performance degrades quickly with large datasets |
| **O(n log n)** | Merge Sort, Quick Sort | Efficient sorting algorithms |
| **O(n)** | Linear Search | Linear - time increases proportionally with data size |
| **O(log n)** | Binary Search | Logarithmic - very efficient, even with large datasets |
| **O(1)** | Array access by index | Constant - same time regardless of data size |

### Best Case Analysis (Ω)

| Running Time | Algorithm Examples |
| --- | --- |
| **Ω(1)** | Linear Search, Binary Search (when target is found immediately) |

*Note: Most algorithms have different best and worst cases, so Θ notation is less commonly used unless the bounds are identical.*

---

## Implementing Search Algorithms in C

### Basic Linear Search with Numbers

```c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int numbers[] = {20, 500, 10, 5, 100, 1, 50};
    
    int n = get_int("Number: ");
    for (int i = 0; i < 7; i++)
    {
        if (numbers[i] == n)
        {
            printf("Found\n");
            return 0;  // Success
        }
    }
    printf("Not found\n");
    return 1;  // Failure
}
```

### String Search - Common Mistake

```c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string strings[] = {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};
    
    string s = get_string("String: ");
    for (int i = 0; i < 6; i++)
    {
        if (strings[i] == s)  // ❌ This compares memory addresses, not content!
        {
            printf("Found\n");
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}
```

### String Search - Correct Implementation

```c
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string strings[] = {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};
    
    string s = get_string("String: ");
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(strings[i], s) == 0)  // ✅ Compares actual string content
        {
            printf("Found\n");
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}
```

**Key Point:** In C, strings are arrays of characters. Using `==` compares memory addresses, not the actual text content. Always use `strcmp()` for string comparison.

---

## Data Structures: Building More Complex Data

### Problem: Managing Related Information

Consider a phonebook where names and phone numbers are related. Using separate arrays can lead to synchronization issues:

```c
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string names[] = {"David", "John", "Yuliia"};
    string numbers[] = {"+1-617-495-1000", "+1-949-468-2750", "+1-617-495-1000"};
    
    string name = get_string("Name: ");
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(names[i], name) == 0)
        {
            printf("Found %s\n", numbers[i]);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}
```

**Problems with this approach:**
- Data can become misaligned if arrays are modified separately
- Difficult to maintain as the program grows
- No clear relationship between related data

### Solution: Custom Data Structures

Using `typedef struct` to create custom data types:

```c
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Define a custom data type
typedef struct
{
    string name;
    string number;
} person;

int main(void)
{
    person people[3];  // Array of person structures
    
    // Initialize data
    people[0].name = "David";
    people[0].number = "+1-617-495-1000";
    
    people[1].name = "John";
    people[1].number = "+1-949-468-2750";
    
    people[2].name = "Yuliia";
    people[2].number = "+1-617-495-1000";
    
    // Search for a person
    string name = get_string("Name: ");
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(people[i].name, name) == 0)
        {
            printf("Found %s\n", people[i].number);
            return 0;
        }
    }
    printf("Not Found\n");
    return 1;
}
```

### Understanding Structures

```c
typedef struct
{
    string name;
    string number;
} person;
```

- **`typedef`:** Creates a new data type name
- **`struct`:** Groups related variables together
- **`person`:** The name of our new data type
- **Members:** `name` and `number` are the structure’s fields
- **Access:** Use dot notation (`person.name`, `person.number`) to access members

---

## Sorting Algorithms

### Bubble Sort

**Concept:**

Repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order. Passes through the list until it's sorted.

**Time Complexity:**

- Worst: O(n²)
- Average: O(n²)
- Best (already sorted): **O(n)**

**Space Complexity:**

- O(1) (in-place)

**Characteristics:**

- Simple but inefficient for large lists
- **Optimized version stops early** if no swaps were made in a pass
- Stable (preserves relative order of equal elements)

**Ideal use case:**

Small or mostly sorted datasets

---

### Selection Sort

**Concept:**

Divides the list into a sorted and an unsorted part. Repeatedly selects the smallest (or largest) element from the unsorted part and moves it to the end of the sorted part.

**Time Complexity:**

- Worst: O(n²)
- Average: O(n²)
- Best: O(n²) (no optimization for sorted lists)

**Space Complexity:**

- O(1) (in-place)

**Characteristics:**

- Always makes the same number of comparisons, regardless of input
- Simple but inefficient
- Not stable by default (though it can be made stable)

**Ideal use case:**

Rarely used in practice, but good for teaching how sorting works

---

### Merge Sort

**Concept:**

A divide-and-conquer algorithm that divides the array into halves, recursively sorts each half, and then merges them together.

**Time Complexity:**

- Worst: **O(n log n)**
- Average: **O(n log n)**
- Best: **O(n log n)**

**Space Complexity:**

- O(n) (needs extra space for merging)

**Characteristics:**

- Very efficient and consistent performance
- Stable
- Not in-place (due to extra memory usage)

**Ideal use case:**

Large datasets or when stable sort is required

---
