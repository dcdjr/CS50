#include <cs50.h>
#include <stdio.h>

int getLength(long number);
int numIterations(long number);
bool isValid(long number, int iterations);
int sumDigitsFromSecondToLastNumber(long number, int iterations);
int sumDigitsFromLastNumber(long number, int iterations);
string whatCard(long number, int iterations);

int main(void)
{
    long number = get_long("Number: ");
    int iterations = numIterations(number);
    printf("%s\n", whatCard(number, iterations));
}

int getLength(long number)
{
    int count = 0;
    do
    {
        number /= 10;
        count++;
    }
    while (number != 0);
    return count;
}

int numIterations(long number)
{
    int iterations;
    int length = getLength(number);
    if (length % 2 == 0)
    {
        iterations = (length / 2);
    }
    else
    {
        iterations = (length / 2) + 1;
    }
    return iterations;
}

bool isValid(long number, int iterations)
{
    int firstSum = sumDigitsFromSecondToLastNumber(number, iterations);
    int secondSum = sumDigitsFromLastNumber(number, iterations);
    return ((firstSum + secondSum) % 10 == 0);
}

int sumDigitsFromSecondToLastNumber(long number, int iterations)
{
    int sum = 0;
    long n = number / 10;
    for (int i = 0; i < iterations; i++)
    {
        int digit = (n % 10) * 2;
        int digit_length = getLength(digit);
        if (digit_length == 1)
        {
            sum += digit;
        }
        else
        {
            for (int j = 0; j < digit_length; j++)
            {
                int digit2 = (digit % 10);
                digit /= 10;
                sum += digit2;
            }
        }
        n /= 100;
    }
    return sum;
}

int sumDigitsFromLastNumber(long number, int iterations)
{
    int sum = 0;
    long n2 = number;
    for (int i = 0; i < iterations; i++)
    {
        int digit = n2 % 10;
        sum += digit;
        n2 /= 100;
    }
    return sum;
}

string whatCard(long number, int iterations)
{
    long placeholder = number;
    int numLength = getLength(number);
    for (int i = 0; i < numLength - 2; i++)
    {
        placeholder /= 10;
    }
    if (isValid(number, iterations))
    {
        if (placeholder / 10 == 4 && (numLength == 16 || numLength == 13))
        {
            return ("VISA");
        }
        else if ((placeholder == 51 || placeholder == 52 || placeholder == 53 ||
                  placeholder == 54 || placeholder == 55) &&
                 numLength == 16)
        {
            return ("MASTERCARD");
        }
        else if ((placeholder == 34 || placeholder == 37) && numLength == 15)
        {
            return ("AMEX");
        }
        else
        {
            return ("INVALID");
        }
    }
    else
    {
        return ("INVALID");
    }
}
