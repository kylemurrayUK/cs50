#include <stdio.h>
#include <cs50.h>
#include <math.h> //i needed to import the math library for the power function. Could have made my own function but this is just as good..probably
#include <stdlib.h> //needed this to exit the console

int getAlternateNumbers(long crdNumber, long counter);

int main(void)
{
    long credit;
    do
    {
        credit = get_long("Number: ");
    } 
    while (credit < 1);
    // amountOfNumbers is 1 to ensure that is gets the last digit
    
    int amountOfNumbers = 1;
    long temp1 = credit;
    
    //gets the length of the number, i think getting rid of the equal sign would make initializing amountOfNumbers to 1 unneeded
    while (temp1 >= 10)
    {
        temp1 = temp1 / 10;
        amountOfNumbers += 1;
    }
    
    long sumOfNumberByTwo = 0;
    int temp;
    long i = 100;

    //gets every other number startings from the second along
    for (int k = 0; k < (amountOfNumbers / 2); k++)
    {
        temp = getAlternateNumbers(credit, i);
        temp = temp * 2;
        //checks if the digit doubled has two digits (ie greater than 10)
        if (temp >= 10)
        {
            int secondDigit;
            secondDigit = getAlternateNumbers(temp, 10);
            
            int firstDigit;
            firstDigit = getAlternateNumbers(temp, 100);
            
            temp = firstDigit + secondDigit;
        }
        //sumOfNumberByTwo is the counters for the doubles digits
        sumOfNumberByTwo = sumOfNumberByTwo + temp;
        i *= 100;
    }
    
    temp = 0;
    long sumOfNumbers = 0;
    long j = 10;
    //gets every other number starting from the first number
    for (int k = 0; k < ((amountOfNumbers + 1) / 2); k++)
    {
        temp = getAlternateNumbers(credit, j);
        sumOfNumbers = sumOfNumbers + temp;
        j *= 100;
    }
    
    temp = sumOfNumbers + sumOfNumberByTwo;
    //start of nesting if statements to determine which card it is and if it is valid
    if ((getAlternateNumbers(temp, 10) > 0) || amountOfNumbers < 13)
    {
        printf("INVALID\n");
        exit(0);
    } // ideally getting the numbers using the power function would be its own function
    else if (getAlternateNumbers(credit, (pow(10, amountOfNumbers))) == 4)
    {
        printf("VISA\n");
        exit(0);
    }  //decided to split the possible correct combinations of the different card types as the if statement would have gotten veeery long
    else if ((getAlternateNumbers(credit, pow(10, amountOfNumbers)) == 3) 
             && (getAlternateNumbers(credit, pow(10, (amountOfNumbers - 1))) == 7))
    {
        printf("AMEX\n");
        exit(0);
    } 
    else if ((getAlternateNumbers(credit, pow(10, amountOfNumbers)) == 3) 
             && (getAlternateNumbers(credit, pow(10, (amountOfNumbers - 1))) == 4))
    {
        printf("AMEX\n");
        exit(0);
    } 
    else if ((getAlternateNumbers(credit, pow(10, amountOfNumbers)) == 5) 
             && (getAlternateNumbers(credit, pow(10, (amountOfNumbers - 1))) == 1))
    {
        printf("MASTERCARD\n");
        exit(0);
    } 
    else if ((getAlternateNumbers(credit, pow(10, amountOfNumbers)) == 5) 
             && (getAlternateNumbers(credit, pow(10, (amountOfNumbers - 1))) == 2))
    {
        printf("MASTERCARD\n");
        exit(0);
    } 
    else if ((getAlternateNumbers(credit, pow(10, amountOfNumbers)) == 5) 
             && (getAlternateNumbers(credit, pow(10, (amountOfNumbers - 1))) == 3))
    {
        printf("MASTERCARD\n");
        exit(0);
    } 
    else if ((getAlternateNumbers(credit, pow(10, amountOfNumbers)) == 5) 
             && (getAlternateNumbers(credit, pow(10, (amountOfNumbers - 1))) == 4))
    {
        printf("MASTERCARD\n");
        exit(0);
    } 
    else if ((getAlternateNumbers(credit, pow(10, amountOfNumbers)) == 5) 
             && (getAlternateNumbers(credit, pow(10, (amountOfNumbers - 1))) == 5))
    {
        printf("MASTERCARD\n");
        exit(0);
    } 
    else
    {
        printf("INVALID\n");
        exit(0);
    }
}

// a commonly used feature so made it a reusable funciton
int getAlternateNumbers(long crdNumber, long counter)
{
    int temp;
    temp = (crdNumber % counter - (crdNumber % (counter / 10))) / (counter / 10);
    return temp;
}

