import re


def readability():
    """Using Coleman-Liau's formula, calculate the grade level needed to understand the text"""

    text = input("Text: ")  # Prompt the user for input
    words = text.split(' ')  # Get the list of words by splitting them with whitespace
    sentences = re.split(r'(?<=[^A-Z].[.?]) +(?=[A-Z])', text)  # Use regex to separate text into sentences
    letters = str.join("", re.findall('\w', text))  # Use regex to get only letters

    L = float(len(letters)) / float(len(words)) * 100  # Average number of letters per 100 words in the text
    S = float(len(sentences)) / float(len(words)) * 100  # Average number of sentences per 100 words in the text
    grade = round(0.0588 * L - 0.296 * S - 15.8)  # Get the grade using Coleman-Liau's formula

    # If grade is less than 1
    if grade < 1:
        print("Before Grade 1")
    # If grade is greater than 16
    elif grade > 16:
        print("Grade 16+")
    # If grade is between 1 and 16 (inclusive)
    else:
        print(f"Grade {grade}")


readability()

