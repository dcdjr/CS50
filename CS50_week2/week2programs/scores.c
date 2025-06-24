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
