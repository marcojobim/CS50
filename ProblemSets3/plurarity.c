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
int vote(char name[], int candidate_count);
void print_winner(int candidate_count);

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

    printf("Numbers of voters: ");
    int voter_count;
    scanf("%d", &voter_count);
    getchar(); // Cleaning buffer

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        char name[50];
        printf("Vote: ");
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = '\0';

        int verify = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (strcmp(name, candidates[j].name) == 0)
                verify = 1;
        }
        if (verify == 0)
        {
            printf("Invalid Vote.\n");
            i--;
        }

        vote(name, candidate_count);
    }

    // Display winner of election
    print_winner(candidate_count);
}

// Update vote totals given a new vote
int vote(char *name, int candidate_count)
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(name, candidates[j].name) == 0)
        {
            candidates[j].votes++;
            return 0;
        }
    }
    return 1;
}

// Print the winner (or winners) of the election
void print_winner(int candidate_count)
{
    int most_voted = 0;
    int max_votes = candidates[0].votes;

    for (int i = 1; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
            most_voted = i;
        }
    }

    int draw[MAX];
    int draw_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes)
        {
            draw[draw_count] = i;
            draw_count++;
        }
    }

    if (draw_count == 1)
    {
        printf("Winner: %s, %d votes", candidates[most_voted].name, max_votes);
        return;
    }

    else
    {
        printf("Draw: \n");

        for (int i = 0; i < draw_count; i++)
        {
            printf("%s, %d votes\n", candidates[draw[i]].name, max_votes);
        }
        return;
    }
}