import csv
import sys

# this function produces a list of all the repetitions of a certain STR and then returns the highest value. Unless there 
# isn't any matches, in which case it returns 0


def get_repetition(dna, STR):
    repeatcounter = 0
    repetitionlist = []
    for i in range(len(dna)):
        if dna[i:i+(len(STR))] == STR:
            repetitionlist.append(recursive_check(i, dna, STR, repeatcounter))
    if(repetitionlist == []):
        return 0
    return max(repetitionlist)        

# decided to implement a recursive function here as it seemed to best way to check for a chain of STRs


def recursive_check(counter, dna, STR, repeatchecker):
    if dna[counter:counter+(len(STR))] != STR:
        return repeatchecker
    if dna[counter:(counter+(len(STR)))] == STR:
        repeatchecker += 1
        return recursive_check((counter + (len(STR))), dna, STR, repeatchecker)


def main():
    if len(sys.argv) != 3:
        sys.exit("Usage: python tournament.py DATABASE SEQUENCE")
# starting to load database and dna sequence into memory
    database = []
    sequence = ""

    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for rows in reader:
            database.append(rows)
        
    reader = open(sys.argv[2], "r")

    for lines in reader:
        sequence = sequence + lines
    # obtaining a list of the STRs to check
    STRS = ({k for d in database for k in d.keys()})
    
    suspect = {}
    # getting a 'suspect' profile with all the str keys previously obtained, excluding name
    for keys in STRS:
        if(keys != "name"):
            suspect[keys] = str(get_repetition(sequence, keys))
    # this goes over each person in the database, creates a dict of just the strs and there repetitions and then checks 
    # the them against the suspect. If they match it prints the name of that person and returns 0...
    for people in database:
        person_strs = {i: people[i] for i in people if i != 'name'}
        if(person_strs == suspect):
            print(f"{people['name']}")
            return 0
    # ... or it returns no match
    print("No match")


main()