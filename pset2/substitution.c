#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//Prototypes
int valid_alphabetical(string text);
int check_repetition(string text);

int main(int argc, string argv[])
{
    string key = argv[1];
    //makes sense to do this in a if else chain as we do not want to execute anything if it does not pass these checks
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (valid_alphabetical(key) > 0)
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }
    else if (check_repetition(key) > 0)
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }
    else //cipher goes here
    {
        //have to initialise ciphertext as equaling plaintext to make sure ciphertext is the same length
        string plaintext = get_string("plaintext: ");
        string ciphertext = plaintext;

        for (int i = 0, n = strlen(plaintext); i < n; i++)
        {
            //checks if the character is alphabetical. If so then the text just stays the same
            if ((plaintext[i] < 65) || (plaintext[i] > 122) || (plaintext[i] > 90 && plaintext[i] < 97))
            {
                ciphertext[i] = ciphertext[i];
            }
            else if (isupper(plaintext[i]))
            {
                int letter = plaintext[i] - 65;
                ciphertext[i] = toupper(key[letter]);
            }
            else
            {
                int letter = plaintext[i] - 97;
                ciphertext[i] = tolower(key[letter]);
            }
        }
        printf("ciphertext: %s\n", ciphertext);
    }
}

int valid_alphabetical(string text)
{
    int checker = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //check that letter against the numberical values between a - z and A - Z
        if ((text[i] < 65) || (text[i] > 122) || (text[i] > 90 && text[i] < 97))
        {
            checker += 1;
        }
    }
    return checker;
}

int check_repetition(string text)
{
    int checker = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //first thing we do is creating a char that will contain the letter we are checking in thsi current search
        char temp = text[i];
        //searching through the string again
        for (int j = 0, o = strlen(text); j < o; j++)
        {
            //inevitably the character will always match itself at least once so to account for that when the current count matches the count of the letter we are on I will minus one
            if (j == i)
            {
                checker -= 1;
            } //if the letters match the program adds one to the checker
            if (temp == text[j])
            {
                checker += 1;
            }
        }

    } //gives checker as either 0 or higher than 0, ie true of false
    return checker;
}