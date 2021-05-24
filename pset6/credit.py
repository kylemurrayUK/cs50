import re
from cs50 import get_int

# gets every other number starting from the second to last or last depending on the option chosen


def get_numbers(option, cardnumber):
    if(option == 1):
        start = 1
        end = 2
        amountofincrements = int(len(str(cardnumber)) / 2)
    elif(option == 2):
        start = 0
        end = 1
        # in case its even, this section could do with some work however
        if((len(str(cardnumber)) % 2) == 0):
            amountofincrements = int(len(str(cardnumber)) / 2)
        else:
            amountofincrements = int(len(str(cardnumber)) / 2) + 1
    step = 2
    y = []
    # incrementing through number
    for i in range(amountofincrements):
        x = slice(start, end, step)
        y.append(cardnumber[x])
        start = start + 2
        end = end + 2

    return(y)


def main():
    while (True):
        cardNo = get_int("Number: ")
        checkNumeric = re.findall("/W", str(cardNo))
        if (checkNumeric != True):
            break
    # returns two lists of the alternate numbers
    firstset = get_numbers(1, str(cardNo))
    secondset = get_numbers(2, str(cardNo))

    secondsetdigits = []
    firstsetdigits = []
    # breaks down the list into individual digits and converts them to ints.  Checking len as there is an issue in my get_numbers function 
    # around odd numbers 
    if(len(str(cardNo)) == 15):
        for i in firstset:
            digit = int(i) * 2
            if(digit > 9):
                firstdigit = (get_numbers(2, str(digit)))
                seconddigit = (get_numbers(1, str(digit)))
                secondsetdigits.append(int(firstdigit[0]))
                secondsetdigits.append(int(seconddigit[0]))
            else:
                secondsetdigits.append(digit)

        for i in secondset:
            firstsetdigits.append(int(i))
    else:
        for i in secondset:
            digit = int(i) * 2
            if(digit > 9):
                firstdigit = (get_numbers(2, str(digit)))
                seconddigit = (get_numbers(1, str(digit)))
                secondsetdigits.append(int(firstdigit[0]))
                secondsetdigits.append(int(seconddigit[0]))
            else:
                secondsetdigits.append(digit)

        for i in firstset:
            firstsetdigits.append(int(i))
    # adding lists of int digits togher
    sumofdigits = sum(firstsetdigits) + sum(secondsetdigits)
    # if multiple of ten then it must be valid
    if(sumofdigits % 10 == 0):
        valid = True
    else:
        valid = False
    
    # converting cardNo into string so I can slice the first two digits out
    cardNoasstring = str(cardNo)
    firstdigit = cardNoasstring[slice(0, 1, 1)]
    seconddigit = cardNoasstring[slice(1, 2, 1)]
    # deciding which type of card is it based on the first digits and if it has passed its tests
    if (valid == True and len(str(cardNo)) > 12):
        if (firstdigit == "3" and (seconddigit == "4" or seconddigit == "7")):
            print("AMEX")
        elif (firstdigit == "5" and (seconddigit == "1" or seconddigit == "2"
                                     or seconddigit == "3" or seconddigit == "4"
                                     or seconddigit == "5")):
            print("MASTERCARD")
        elif (firstdigit == "4"):
            print("VISA")
    else:
        print("INVALID")


main()