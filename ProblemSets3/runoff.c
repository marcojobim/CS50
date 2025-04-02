#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    char name[50];
    int votes;
    int eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
int vote(int voter, int rank, char *name);
void tabulate(void);
int print_winner(void);
int find_min(void);
int is_tie(int min);
void eliminate(int min);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i].name, argv[i + 1]);
        candidates[i].votes = 0;
        candidates[i].eliminated = 0;
    }

    printf("Number of voters: ");
    if (scanf("%d", &voter_count) != 1 || voter_count > MAX_VOTERS)
    {
        printf("Invalid number of voters. Maximum is %i\n", MAX_VOTERS);
        return 3;
    }
    getchar(); // Clear newline from buffer

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            char name[50];
            printf("Rank %i: ", j + 1);
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (1)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        if (print_winner())
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        if (is_tie(min))
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
int vote(int voter, int rank, char *name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return 1;
        }
    }
    return 0;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int candidate_index = preferences[i][j];
            if (candidates[candidate_index].eliminated == 0)
            {
                candidates[candidate_index].votes++;
                break;
            }
        }
    }
}

// Print the winner of the election, if there is one
int print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count / 2)
        {
            printf("Winner:\n %s, Votes: %d\n", candidates[i].name, candidates[i].votes);
            return 1;
        }
    }
    return 0;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count; // Start with max votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == 0 && min > candidates[i].votes)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
int is_tie(int min)
{
    int tie = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == 0 && candidates[i].votes == min)
        {
            tie++;
        }
    }
    if (tie == candidate_count)
        return 1;

    return 0;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = 1;
        }
    }
}