#include <cs50.h>
#include <stdio.h>

int coins;
int coinAdd;
int changeOwed;

int getPositiveChangeOwed(void);
int getNumQuarters(void);
int getNumDimes(void);
int getNumNickels(void);
int getNumPennies(void);

int main(void)
{
    changeOwed = getPositiveChangeOwed();

    int numQuarters = getNumQuarters();
    int numDimes = getNumDimes();
    int numNickels = getNumNickels();
    int numPennies = getNumPennies();

    int sum = numQuarters + numDimes + numNickels + numPennies;

    printf("%i\n", sum);
}

int getPositiveChangeOwed(void)
{
    int n;
    do
    {
        n = get_int("Change owed: ");
    }
    while (n < 1);
    return n;
}

int getNumQuarters(void)
{
    int quarters = changeOwed / 25;
    changeOwed %= 25;
    return quarters;
}

int getNumDimes(void)
{
    int dimes = changeOwed / 10;
    changeOwed %= 10;
    return dimes;
}

int getNumNickels(void)
{
    int nickels = changeOwed / 5;
    changeOwed %= 5;
    return nickels;
}

int getNumPennies(void)
{
    int pennies = changeOwed / 1;
    changeOwed %= 1;
    return pennies;
}
