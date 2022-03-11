#include <stdio.h>
#include <string.h>
#include <cs50.h>

/* 
The program simulates a plurality vote election. 
Link: https://cs50.harvard.edu/x/2021/psets/3/plurality/
*/

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
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }
    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max_position = 0; // position of candidate with maximum number of votes
    
    int max = candidates[max_position].votes; // determine the highest number of votes to compare
    for (int i = 1; i <= candidate_count; i++)
    {
        if (max < candidates[i].votes)
        {
            max_position = i;
            max = candidates[max_position].votes;
        }
    }

    printf("%s\n", candidates[max_position].name);
    for (int i = 0; i < candidate_count; i++)
    {
        // determine if there are other candidates with maximum number of votes
        if (candidates[max_position].votes == candidates[i].votes && strcmp(candidates[max_position].name, candidates[i].name) != 0)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}

