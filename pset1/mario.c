#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    { 
        // Gets desired height off user
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    

    for (int i = 0; i < height; i++)
    {   
        int j = 0;
        int k = 0;
        // prints the right amount of spaces before printing the hash
        for (int l = 1; l < (height - i) ; l++)
        {
            printf(" ");
        }
        
        while (j <= i)
        {
            printf("#");
            j++;
        }
        // The gap in-between the two sides to the pyramid
        printf("  ");
        // Repeats the same process but for the second half of the pyramid
        while (k <= i)
        {
            printf("#");
            k++;
        }
        printf("\n");
    }
}
