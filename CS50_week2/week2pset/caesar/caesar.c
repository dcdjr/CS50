#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string encryptMessage(string message, int key);
int isNumber(string number);

const int ALPHABET_SIZE = 26;
const char ALPHABET_UPPER[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                               'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
const char ALPHABET_LOWER[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                               'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int main(int argc, string argv[])
{
    if (argc == 2 && isNumber(argv[1]))
    {
        const int key = atoi(argv[1]);
        string message = get_string("plaintext:  ");
        printf("ciphertext: %s\n", encryptMessage(message, key));
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

string encryptMessage(string message, int key)
{
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        if (isalpha(message[i]))
        {
            if (islower(message[i]))
            {
                message[i] = ALPHABET_LOWER[((message[i] - 97) + key) % 26];
            }
            else
            {
                message[i] = ALPHABET_UPPER[((message[i] - 65) + key) % 26];
            }
        }
    }
    return message;
}

int isNumber(string number)
{
    for (int i = 0, n = strlen(number); i < n; i++)
    {
        if (isdigit(number[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}
