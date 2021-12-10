import re
from nltk import tokenize

def readability():
    text = input("Text: ")
    words = text.split(' ')
    sentences = list(filter(None, re.split('[.!?]', text)))
    letters = str.join("", re.findall('\w', text))

    print(len(letters))
    print(len(words))
    print(len(sentences))

    L = float(len(letters)) / float(len(words)) * 100
    S = float(len(sentences)) / float(len(words)) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")

    #print(L)
    #print(S)
    #print(index)
    print(f"letters = {letters}")
    print(f"words = {words}")
    print(f"sentences = {sentences}")


readability()