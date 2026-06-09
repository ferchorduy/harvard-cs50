#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// is_locked[i][j] means i is locked in over j
int is_locked[MAX][MAX]; // bool, 0 or 1

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
char candidates[MAX][50];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
int vote(int rank, char name[], int ranks[]); // return bool, 0 or 1
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
int creates_cycle(int winner, int loser);
void print_winner(void);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        strcpy(candidates[i], argv[i + 1]);
    }

    // Clear graph of is_locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            is_locked[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        printf("Voter #%i\n", i + 1);
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            char name[50];
            printf("Rank %i: ", j + 1);
            scanf("%s", name);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
int vote(int rank, char name[], int ranks[]) // return bool, 0 or 1
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return 1;
        }
    }
    return 0;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (j > i)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
            else
            {
                continue;
            }
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {

            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else continue;
        }
    }
    for (int i = 0; i < pair_count; i++)
    {
        printf("winner: %i, loser: %i\n", pairs[i].winner, pairs[i].loser);
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int swap_counter = -1;
    for (int i = 0; i < pair_count - 1; i++)
    {
        swap_counter = 0;
        for (int j = 0; j < pair_count - 1; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] <
            preferences[pairs[j+1].winner][pairs[j+1].loser])
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j+1];
                pairs[j+1] = temp;
                swap_counter++;
            }
        }
        if (swap_counter == 0) break;
    }
    for (int i = 0; i < pair_count; i++)
    {
        printf("winner: %i, loser: %i\n", pairs[i].winner, pairs[i].loser);
        printf("%i\n", preferences[pairs[i].winner][pairs[i].loser]);
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!creates_cycle(pairs[i].winner, pairs[i].loser))
        {
            is_locked[pairs[i].winner][pairs[i].loser] = 1;
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", is_locked[i][j]);
        }
        printf("\n");
    }
}

// Returns bool if a pair locking creates a cycle
int creates_cycle(int winner, int loser)
{
    if (loser == winner) return 1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (is_locked[loser][i])
        {
            if (creates_cycle(winner, i)) return 1;
        }
    }
    return 0;
}

// Print the winner of the election
void print_winner(void)
{
    int toggle = 0;
    int winner;
    // whichever number does not appear in losers of pairs, thats the winner
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (is_locked[pairs[j].winner][pairs[j].loser] == 1 && i == pairs[j].loser)
            {
                toggle = 1;
                break;
            }
        }

        if (toggle == 0)
        {
            winner = i;
            printf("%i\n", winner);
            printf("%s\n", candidates[winner]);
            break;
        }

        toggle = 0;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", is_locked[i][j]);
        }
        printf("\n");
    }

    printf("%i\n", winner);
    printf("%s\n", candidates[winner]);
}