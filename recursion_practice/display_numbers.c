#include <cs50.h>
#include <stdio.h>

void count_numbers(int n);

int main(void)
{
    int number = get_int("Please enter a number: ");
    printf("The natural numbers are : ");
    count_numbers(number);
}

int m = 1;

void count_numbers(int n)
{
    if (m == n)
    {
        printf("%d\n", n);
        return;
    }
    else 
    {
        printf("%d\n", m);
        m += 1;
        return count_numbers(m + (n - m));
    }
}