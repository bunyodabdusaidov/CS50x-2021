#include <cs50.h>
#include <stdio.h>
#include <string.h>

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

    int voter_count = get_int("Number of voters: ");

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
        if (strcmp(name, candidates[i].name) == 0)
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
    int max = 0;
    int n = 0;
    int j = 0;
    char *winners[MAX];
    bool all_equal = true;

    for (int i = 0; i < candidate_count - 1; i++)
    {
        if (candidates[i].votes != candidates[i+1].votes)
        {
            all_equal = false;
            break;
        }
    }
    //printf("all_equal: %i\n", all_equal);

    if (all_equal)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            winners[i] = candidates[i].name;
            //printf("winners[i]: %s\n", winners[i]);
        }
    }
    else
    {
        max = candidates[0].votes;
        for (int i = 1; i < candidate_count; i++)
        {
            //printf("candidate: %s\n", candidates[i].name);   
            if (max < candidates[candidate_count].votes)
            {
                max = candidates[i].votes;
                n = i;
                //printf("candidate: %s\n", candidates[i].name);
            }
        }

        winners[j] = candidates[n].name;
        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[n].votes == candidates[i].votes & strcmp(candidates[n].name, candidates[i].name) != 0)
            {
                winners[++j] = candidates[i].name;
            }
        }
    }
    

    int array_len = 0;
    while (winners[array_len])
    {
        array_len++;
    }
    //printf("array_len: %i\n", array_len);
    for (int i = 0; i < array_len - 1; i++)
    {
        char *temp;
        for (int j = i+1; j < array_len - 1; j++)
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

