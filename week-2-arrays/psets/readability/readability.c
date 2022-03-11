#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

/* This program determines the grade level that is required to understand the given text.
The code uses The Coleman-Liau index formula.
The Coleman-Liau index of a text is designed to output what (U.S.) grade level is needed to understand the text. 

link to description of the problem: https://cs50.harvard.edu/x/2021/psets/2/readability/
*/

// function prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int determine_grade(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: "); // get input
    int letters = count_letters(text); // number of letters
    int words = count_words(text); // number of words
    int sentences = count_sentences(text); // number of sentences
    int index = determine_grade(letters, words, sentences); // grade level

    // display corresponding message according to the grade
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
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int len = strlen(text);
    int n = 0;
    // loop through text 
    for (int i = 0; i < len; i++)
    {
        // check if character in text is a valid letter using ASCII
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            // if character in text is a letter (lowercase or uppercase), increment n
            n++;
        }
    }
    return n;
}

int count_words(string text)
{
    int len = strlen(text);
    int n = 1;
    // loop through text
    for (int i = 0; i < len; i++)
    {
        // check if character is a space character using ASCII
        if (text[i] == 32)
        {
            // if character is a space character, increment n
            n++;
        }
    }
    return n;
}

int count_sentences(string text)
{
    int len = strlen(text);
    int n = 0;
    // loop through text
    for (int i = 0; i < len; i++)
    {
        // check if character is . or ! or ? character using ASCII
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            // if character is . or ! or ? character, increment n
            n++;
        }
    }
    return n;
}

int determine_grade(int letters, int words, int sentences)
{
    // using Coleman-Liau's formula, calculate the grade level needed to understand the text
    float L = ((float)letters / (float)words) * 100; // average number of letters per 100 words in the text
    float S = ((float)sentences / (float)words) * 100; // average number of sentences per 100 words in the text
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}