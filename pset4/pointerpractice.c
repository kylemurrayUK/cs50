#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <cs50.h>

void swap(int *a, int *b);

int main(void)
{
    char x[1];
    printf("X: ");
    scanf("%s", x);
    printf("x equals %s\n", x);



    char *y = malloc(strlen(x) + 1);

    printf("x equals %s\n", x);
    for (int i = 0; i <= strlen(x); i++ )
    {
        y[i] = x[i];
    }

    printf("y equals %s\n", y);
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}