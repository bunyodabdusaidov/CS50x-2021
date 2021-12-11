from sys import argv
from csv import DictReader, reader


def dna():
    # Check for correct number of command-line arguments
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return 1
        
    data = read_file(argv[1])  # Get data in dictionary format
    sequence = read_file(argv[2])  # Get sequence in string format
    dna = count_strs(data, sequence)  # Get STRs and their occurances from sequence in dictionary format
    
    # Check if dna exists in data.csv
    for name, strs in data.items():
        # If exists, print the name to whom the dna belongs
        if strs == dna:
            print(name)
            return 0
    # If dna doesn't exist in data.csv, print `No Match``
    print("No Match")


def count_strs(data, sequence):
    """
    Count STRs in sequence (str). Use data (dict) get STR name. 
    Return dictionary containing STRs and values from the sequence
    """

    strs_values = {}  # Dict to store STRs and its occurances

    strs = data.values()  # Get values from data (dict)
    strs = list(strs)[0]  # Get first element from list of STRs
    strs = list(strs.keys())  # Store the STR names as a list

    # Compute the longest run of consecutive repeats of the STR in sequence
    for i in range(len(strs)):
        count = 0  # Count repeats
        pattern = strs[i]  # Get the pattern (STR) from strs list
        while pattern in sequence:
            count += 1
            pattern += strs[i]  # Concatinate current pattern and current STR to check for existance
        strs_values[strs[i]] = count  # Store STR and its value (count) in strs_values dictionary
    
    return strs_values
    

def read_file(file):
    """Read file to dict or str depending on if it's .csv or .txt file"""

    # If file type is .csv
    if file.endswith('.csv'):
        data = {} 
        
        # Read .csv file as Dictionary
        with open(argv[1], 'r') as file:
            reader = DictReader(file)  # Dictionary reader
            fieldnames = reader.fieldnames[1:]  # Get fieldnames except `name` field

            # Build nested dictionary ('name':{'STR':number})
            for row in reader:
                strs = {}  
                for i in range(len(fieldnames)):
                    strs[fieldnames[i]] = int(row[fieldnames[i]])  # Store STR name as key and its number as value in strs (dict)
                
                data[row['name']] = strs  # Store name as key and strs (dict) as value in data (dict)
        
        return data
    
    # If file type is .txt
    elif file.endswith('.txt'):
        sequence = ""

        with open(argv[2], 'r') as file:
            sequence = file.read()

        return sequence


dna()
