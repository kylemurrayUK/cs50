#include <stdio.h>
#include <cs50.h>

int fact(int n);

int main(void)
{
    int number = get_int("Please enter a number: ");
    printf("Factor is: %d\n", fact(number));
}

int fact(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return n * fact(n - 1);
    }
}