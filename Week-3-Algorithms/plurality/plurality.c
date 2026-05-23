#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    char name[50];
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
int is_valid_vote(char name[]); // returns 1 if true, 0 if false
void print_winner(void);

int main(int argc, char *argv[])
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
        strcpy(candidates[i].name, argv[i + 1]);
        candidates[i].votes = 0;
    }

    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);
    
    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        char name[50];
        printf("Vote: ");
        scanf("%s", name);

        // Check for invalid vote
        if (!is_valid_vote(name))
        {
            printf("Invalid vote.\n");
        }
        
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
int is_valid_vote(char name[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return 1;
        }
    }
    return 0;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int highest_vote_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (highest_vote_count < candidates[i].votes) highest_vote_count = candidates[i].votes;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == highest_vote_count)
        {
            printf("%s %d\n", candidates[i].name, candidates[i].votes);
        }
        else
        {
            break;
        }
    }
}