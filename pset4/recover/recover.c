#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    //making sure user has entered correct number of arguements
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
    }

    FILE *input = fopen(argv[1], "r");
    //error checking to make sure file is openable
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    //declaring variables including space for the filename, the output pointer, counter for the file names and
    //a buffer
    char *filename = malloc(7);
    FILE *output = fopen("000.jpg", "w");
    int counter = 0;
    BYTE buffer[BLOCK_SIZE];

    while (fread(&buffer, sizeof(BYTE), 512, input) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter == 0)
            {
                fwrite(&buffer, sizeof(BYTE), 512, output);
                counter++;
            }
            else
            {
                fclose(output);
                sprintf(filename, "%03i.jpg", counter);
                output = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), 512, output);
                counter++;
            }
        }
        //only write if we have already found our first image
        else if (counter > 0)
        {
            fwrite(&buffer, sizeof(BYTE), 512, output);
        }
    }
    //remebering to free dynamically allocated memory
    free(filename);
}