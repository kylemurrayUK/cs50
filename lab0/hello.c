#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string answer = get_string("Whats your name?");
    printf("Hello, world %s\n", answer);
}