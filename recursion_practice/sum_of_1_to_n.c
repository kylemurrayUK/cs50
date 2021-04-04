#include <cs50.h>
#include <stdio.h>

int sum(int n);

int main(void)
{
    int number = get_int("Input the last number of the range starting from 1 : ");
    
    printf("The sum of 1 to %d : \n%d", number, sum(number));
    
}

int sum(int n)
{
    if (n == 1)
        return 1;
    else
        return n + (sum(n - 1));
}