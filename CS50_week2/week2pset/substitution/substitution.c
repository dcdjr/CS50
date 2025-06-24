#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int isAlphabetical(string key);
int checkDuplicates(string key);
void encryptMessage(string message, string key);
string makeKeyUppercase(string key);

const int ALPHABET_SIZE = 26;
const char ALPHABET_UPPER[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                               'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
const char ALPHABET_LOWER[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                               'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int main(int argc, string argv[])
{
    if (argc == 2 && isAlphabetical(argv[1]))
    {
        argv[1] = makeKeyUppercase(argv[1]);
        if (checkDuplicates(argv[1]) == 0)
        {
            if (strlen(argv[1]) == 26)
            {
                const string key = argv[1];
                string message = get_string("plaintext:  ");
                encryptMessage(message, key);
                return 0;
            }
            else
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
        }
        else
        {
            printf("The key must contain each letter of the alphabet exactly once. \n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

int checkDuplicates(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (key[i] == key[j])
            {
                return 1;
            }
        }
    }
    return 0;
}

void encryptMessage(string message, string key)
{
    char encryptedMessage[strlen(message) + 1];
    encryptedMessage[strlen(message)] = '\0';
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        if (isalpha(message[i]))
        {
            if (islower(message[i]))
            {
                for (int j = 0; j < ALPHABET_SIZE; j++)
                {
                    if (message[i] == ALPHABET_LOWER[j])
                    {
                        encryptedMessage[i] = tolower(key[j]);
                    }
                }
            }
            else
            {
                for (int j = 0; j < ALPHABET_SIZE; j++)
                {
                    if (message[i] == ALPHABET_UPPER[j])
                    {
                        encryptedMessage[i] = key[j];
                    }
                }
            }
        }
        else
        {
            encryptedMessage[i] = message[i];
        }
    }
    printf("ciphertext: %s\n", encryptedMessage);
}

int isAlphabetical(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}

string makeKeyUppercase(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        key[i] = toupper(key[i]);
    }
    return key;
}
