#include <cs50.h>
#include <stdio.h>

int getPositiveHeight(void);
void makePyramid(int n);

int main(void)
{
    int height = getPositiveHeight();
    makePyramid(height);
}

int getPositiveHeight(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);
    return height;
}

void makePyramid(int height)
{
    for (int row = 1; row <= height; row++)
    {
        for (int i = 0; i < height - row; i++)
        {
            printf(" ");
        }
        for (int i = 0; i < row; i++)
        {
            printf("#");
        }
        printf("  ");
        for (int i = 0; i < row; i++)
        {
            printf("#");
        }
        printf("\n");
    }
}
