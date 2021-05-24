from cs50 import get_string

text = get_string("Text: ")
letters = 0
# always at least one word so words initialized to 1
words = 1
sentences = 0

# runs through every letter in the text
for letter in text:
    if(letter == " "):
        words = words + 1
    if(letter == "." or letter == "!" or letter == "?"):
        sentences = sentences + 1
    if(letter.isalpha()):
        letters = letters + 1

# not having to declare floats makes the code much cleaner in python
L = (letters / words) * 100
S = (sentences / words) * 100

index = round(0.0588 * L - 0.296 * S - 15.8)

if(index < 1):
    print("Before Grade 1")
elif(index > 16):
    print("Grade 16+")
else:
    print(f"Grade {index}")