from cs50 import get_int

while (True):
    # get desired height off user
    height = get_int("Height: ")
    if (height >= 1 and height <= 8):
        break


for i in range(height):
    j = 0
    k = 0
    # prints the right amount of spaces before printing the hash
    for l in range(1, height - i, 1):
        print(" ", end="")
    
    while(j <= i):
        print("#", end="")
        j += 1
    # The gap in-between the two sides to the pyramid
    print("  ", end="")
    # Repeats the same process but for the second half of the pyramid
    while(k <= i):
        print("#", end="")
        k += 1
    print("")