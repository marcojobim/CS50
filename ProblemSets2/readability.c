#include <stdio.h>
#include <string.h>
#include <math.h>

#define SIZE 1000

int main(void)
{
    char text[SIZE];
    printf("Text: ");
    fgets(text, SIZE, stdin);

    int letter_count = 0;
    int word_count = 0;
    int sentence_count = 0;
    int i = 0;
    while (text[i] != '\0')
    {
        // Counting Letters
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            letter_count++;
        }

        // Counting Words
        if (text[i] == 32)
        {
            word_count++;
        }

        // Counting Sentences
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            sentence_count++;
        }

        i++;
    }

    if (letter_count != 0)
    {
        word_count++;
    }

    float L = ((float)letter_count / word_count) * 100;
    float S = ((float)sentence_count / word_count) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index < 1)
    {
        printf("Before Grade 1");
    }
    else if (index > 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %d", (int)round(index));
    }

    return 0;
}