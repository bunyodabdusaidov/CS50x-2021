from sys import argv
from csv import DictReader, reader

def dna():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return 1
        
    data = read_file(argv[1])
    sequence = read_file(argv[2])
    strs_values = {}

    print(data)
    print(sequence)

    strs = []
    for key, value in data.items():
        for s in value:
            strs.append(s)
        break
    
    print(strs)
    
    n = 0
    while n < len(strs):
        i = 0
        k = len(strs[n])
        tmp = ""
        occur = set()
        number = 0
        #print("initial occurance")
        while tmp != strs[n]:
            tmp = sequence[i:k]
            #print(tmp)
            i += 1
            k += 1
            if k >= len(sequence):
                break
        
        i -= 1
        k -= 1
        print(f"sequence[{i}:{k}] = {tmp}")
        
        #print("consequtive occurances")
        for j in range(i, len(sequence), len(strs[n])):
            tmp = sequence[j:k]
            #print(tmp)
            
            if tmp != strs[n]:
                occur.add(number)
                number = 0
            
            k += len(strs[n])
            number += 1
        
        strs_values[strs[n]] = max(occur)
        n += 1
    
    print(strs_values)

    for name, strs in data.items():
        if strs == strs_values:
            #print(f"strs = {strs}")
            print(name)
            return 0
    
    print("No Match")


def read_file(file):
    if file.endswith('.csv'):
        data = {}

        with open(argv[1], 'r') as file:
            reader = DictReader(file)
            fieldnames = reader.fieldnames

            for row in reader:
                strs = {}
                for i in range(1, len(fieldnames)):
                    strs[fieldnames[i]] = int(row[fieldnames[i]])
                
                data[row['name']] = strs
        
        return data
    
    elif file.endswith('.txt'):
        sequence = ""

        with open(argv[2], 'r') as file:
            sequence = file.read()

        return sequence


dna()
