#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start;
    int end;
    int years = 0;
    // TODO: Prompt for start size
    do
    {
        start = get_int("Starting Population: ");
    }
    while (start < 9);
    // TODO: Prompt for end size
    do
    {
        end = get_int("End Population: ");
    }
    while (start > end);
    
    // TODO: Calculate number of years until we reach threshold
    while (start < end)
    {
        start = start - (start / 4) + (start / 3);
        years ++;
    }
    // TODO: Print number of years
    printf("Years: %i", years);
}