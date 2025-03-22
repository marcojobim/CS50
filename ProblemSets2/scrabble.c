#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char word1[50];
    char word2[50];
    int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    printf("Scrabble Game\n");

    // Get Words from user
    printf("Player 1: ");
    scanf("%s", word1);
    printf("Player 2: ");
    scanf("%s", word2);

    // Calculates points for word 1
    int size_w1 = strlen(word1);
    int sum_w1 = 0;
    for (int i = 0; i < size_w1; i++)
    {
        sum_w1 += points[toupper(word1[i]) - 65];
    }

    // Calculates points for word 2 (Same way)
    int size_w2 = strlen(word2);
    int sum_w2 = 0;
    for (int i = 0; i < size_w2; i++)
    {
        sum_w2 += points[toupper(word2[i]) - 65];
    }

    // Comparing sums
    if (sum_w1 > sum_w2)
    {
        printf("Player 1 wins!");
    }
    else if (sum_w1 < sum_w2)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }

    return 0;
}