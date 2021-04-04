#include <stdio.h>
#include <cs50.h>

int counter = 0;
void collatz_c(int n);
int multi(int a, int b);

int main(void)
{
    int a = get_int("Number: ");
    
    int b = get_int("Times By: ");
    
    printf("Equals: %d", multi(a, b));
    //printf("%d\n", counter);
}

void collatz_c(int n)
{
    if (n == 1)
    {
        return;
    }
    else if (n % 2 == 0)
    {
        counter += 1;
        return collatz_c(n / 2);
    }
    else if (n % 2 > 0)
    {
        counter += 1;
        return collatz_c((n * 3) + 1);
    }
}

int multi(int a, int b)
{
    if (b == 1)
        return a;
    else
        return a + multi(a, (b - 1));
}