#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <cs50.h>
#include <ctype.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of votes: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string candidate = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(candidate))
        {
            printf("Invalid vote.\n");
        }
    }
    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string candidate)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidate, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max;
    int max_position = 0;
    string winners[MAX];
    int winner_index = 0;
    
    max = candidates[max_position].votes;
    for (int i = 1; i < candidate_count; i++)
    {
        if (max < candidates[i].votes)
        {
            max_position = i;
            max = candidates[max_position].votes;
        }
    }
    winners[winner_index] = candidates[max_position].name;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[max_position].votes == candidates[i].votes && strcmp(candidates[max_position].name, candidates[i].name) != 0)
        {
            winners[++winner_index] = candidates[i].name;
        }
    }

    int array_len = 0;
    while (winners[array_len])
    {
        array_len++;
    }
    
    string temp;
    for (int i = 0; i < array_len - 1; i++)
    {
        for (int j = 1; j < array_len; j++)
        {
            if (strcmp(winners[i], winners[j]) > 0)
            {
                temp = winners[i];
                winners[i] = winners[j];
                winners[j] = temp;
            }
        }
    }

    for (int i = 0; i < array_len; i++)
    {
        printf("%s\n", winners[i]);
    }
}

