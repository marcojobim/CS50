// Implements a spell-checker

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "dictionary.h"

// Default dictionary
#define DICTIONARY "dictionaries/large"

int main(int argc, char *argv[])
{
    // Check for correct number of args
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./speller [DICTIONARY] text\n");
        return 1;
    }

    // Benchmarks
    double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0;

    // Determine dictionary to use
    char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;

    // Load dictionary
    clock_t start = clock();
    bool loaded = load(dictionary);
    clock_t end = clock();
    time_load = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }

    // Try to open text
    char *text = (argc == 3) ? argv[2] : argv[1];
    FILE *file = fopen(text, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", text);
        unload();
        return 1;
    }

    printf("\nMISSPELLED WORDS\n\n");

    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH + 1];

    char c;
    while (fread(&c, sizeof(char), 1, file))
    {
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            word[index] = c;
            index++;

            if (index > LENGTH)
            {
                while (fread(&c, sizeof(char), 1, file) && isalpha(c))
                    ;
                index = 0;
            }
        }
        else if (isdigit(c))
        {
            while (fread(&c, sizeof(char), 1, file) && isalnum(c))
                ;
            index = 0;
        }
        else if (index > 0)
        {
            word[index] = '\0';
            words++;

            start = clock();
            bool misspelled = !check(word);
            end = clock();

            time_check += ((double)(end - start)) / CLOCKS_PER_SEC;

            if (misspelled)
            {
                printf("%s\n", word);
                misspellings++;
            }

            index = 0;
        }
    }

    if (ferror(file))
    {
        fclose(file);
        printf("Error reading %s.\n", text);
        unload();
        return 1;
    }

    fclose(file);

    // Dictionary size
    start = clock();
    unsigned int n = size();
    end = clock();
    time_size = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Unload dictionary
    start = clock();
    bool unloaded = unload();
    end = clock();
    time_unload = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }

    // Report benchmarks
    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", n);
    printf("WORDS IN TEXT:        %d\n", words);
    printf("TIME IN load:         %.2f\n", time_load);
    printf("TIME IN check:        %.2f\n", time_check);
    printf("TIME IN size:         %.2f\n", time_size);
    printf("TIME IN unload:       %.2f\n", time_unload);
    printf("TIME IN TOTAL:        %.2f\n\n",
           time_load + time_check + time_size + time_unload);

    return 0;
}