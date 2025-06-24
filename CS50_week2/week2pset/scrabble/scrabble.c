#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int computeScore(string word);
void determineWinner(int score1, int score2);
string makeWordLowercase(string word);

const int POINTS[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    string player1Word = get_string("Player 1: ");
    string player2Word = get_string("Player 2: ");

    int score1 = computeScore(player1Word);
    int score2 = computeScore(player2Word);

    determineWinner(score1, score2);
}

int computeScore(string word)
{
    int points = 0;
    string newWordLowercase = makeWordLowercase(word);
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        points += POINTS[word[i] - 97];
    }
    return points;
}

void determineWinner(int score1, int score2)
{
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

string makeWordLowercase(string word)
{
    string wordLowercase = word;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        wordLowercase[i] = tolower(word[i]);
    }
    return wordLowercase;
}
