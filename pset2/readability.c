#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //prompting passage of text from user
    string text = get_string("Text: ");
    
    //calling pre-made functions that will get the S and L value for formula
    float L = ((float) count_letters(text) / count_words(text)) * 100.00;
    float S = ((float) count_sentences(text) /  count_words(text)) * 100.00;
    
    //plugging those values into Coleman-Liau and casting it as an int 
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    
    //sometimes index comes out at a negative number so < 1 covers all of that
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else 
    {
        //could do just one if and else if you did if index inbetween 2 and 15
        printf("Grade %d\n", index);
    }
}
//counts the letters - the numbers represent the text value in ASCII
int count_letters(string text)
{
    int amountOfLetters = 0;
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {   
        //check that letter against the numberical values between a - z and A - Z
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            amountOfLetters += 1;
        }
    }
    return amountOfLetters;
}
//does a very similar thing except the number in the if condition represents the space bar
int count_words(string text)
{
    int amountOfWords = 1;
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 32)
        {
            amountOfWords += 1;
        }
    }
    return amountOfWords;
}
//these could be made into one function but i think its better for them to be separate so I can reuse them later
int count_sentences(string text)
{
    int amountOfSentences = 0;
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            amountOfSentences += 1;
        }
    }
    return amountOfSentences;
}