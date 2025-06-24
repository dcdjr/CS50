#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int calculateReadingLevel(string text);
int howManyWords(string text);
int howManyLetters(string text);
int howManySentences(string text);
int outputGrade(int index);

int main(void)
{
    string text = get_string("Text: ");
    int level = calculateReadingLevel(text);
    int output = outputGrade(level);

    if (output == 2)
    {
        printf("Before Grade 1\n");
    }
    else if (output == 1)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", level);
    }
}

int calculateReadingLevel(string text)
{
    int letters = howManyLetters(text);
    int words = howManyWords(text);
    int sentences = howManySentences(text);

    float L = letters * (100.0 / words);
    float S = sentences * (100.0 / words);
    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    return round(index);
}

int howManyWords(string text)
{
    int spaces = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isblank(text[i]))
        {
            spaces++;
        }
    }
    return spaces + 1;
}

int howManyLetters(string text)
{
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

int howManySentences(string text)
{
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '?' || text[i] == '!' || text[i] == '.')
        {
            sentences++;
        }
    }
    return sentences;
}

int outputGrade(int index)
{
    if (index < 1)
    {
        return 2;
    }
    else if (index >= 16)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
