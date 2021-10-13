#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

/* This program determines which of two Scrabble words is worth more.
In the game of Scrabble, players create words to score points, 
and the number of points is the sum of the point values of each letter in the word. */

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // identify who is the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int len = strlen(word); // length of word to loop through it
    int sum = 0; // variable to track the sum of points
    for (int i = 0; i < len; i++)
    {
        int str = toupper(word[i]); // turn each letter to uppercase to avoid case sensitivity
        if (str >= 65 && str <= 90) // if the letter is between A and Z letters
        {
            int n = str - 65; // determine the place of the letter in alphabet
            sum += POINTS[n]; // find the score value of the letter and add it to sum
        }
    }
    return sum;
}