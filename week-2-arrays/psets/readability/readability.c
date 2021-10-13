#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float determine_grade(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    int index = determine_grade(letters, words, sentences);

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
    for (int i = 0; i < len; i++)
    {
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            n++;
        }
    }
    return n;
}

int count_words(string text)
{
    int len = strlen(text);
    int n = 1;
    for (int i = 0; i < len; i++)
    {
        if (text[i] == 32)
        {
            n++;
        }
    }
    return n;
}

int count_sentences(string text)
{
    int len = strlen(text);
    int n = 0;
    for (int i = 0; i < len; i++)
    {
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            n++;
        }
    }
    return n;
}

float determine_grade(int letters, int words, int sentences)
{
    float L = ((float)letters / (float)words) * 100;
    float S = ((float)sentences / (float)words) * 100;
    float index = 0.0588 * round(L) - 0.296 * round(S) - 15.8;
    printf("index: %f\n", round(index));
    return round(index);
}