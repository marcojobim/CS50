#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int key = atoi(argv[1]);
    char plain_text[200];

    if (key < 0 || key > 26)
    {
        printf("Key is invalid");
        return 1;
    }

    printf("Caesar Cypher\n");

    printf("Plain Text: ");
    fgets(plain_text, 200, stdin);

    char encrypted_text[200];
    int i = 0;
    while (plain_text[i] != '\0')
    {
        if (plain_text[i] >= 65 && plain_text[i] <= 90)
        {
            int p = plain_text[i] - 65;
            int c = (p + key) % 26;
            encrypted_text[i] = c + 65;
        }

        if (plain_text[i] >= 97 && plain_text[i] <= 122)
        {
            int p = plain_text[i] - 97;
            int c = (p + key) % 26;
            encrypted_text[i] = c + 97;
        }
        i++;
    }

    printf("Encrypted Text: %s", encrypted_text);

    return 0;
}