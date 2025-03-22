#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char key[26];
    char plain_text[200];

    strncpy(key, argv[1], sizeof(key) - 1);

    printf("Plain Text: ");
    fgets(plain_text, 200, stdin);

    char encrypted_text[200];
    int i = 0;
    while (plain_text[i] != '\0')
    {
        if (isalpha(plain_text[i]))
        {
            encrypted_text[i] = key[toupper(plain_text[i]) - 65];
        }
        i++;
    }

    printf("Encrypted Text: %s", encrypted_text);

    return 0;
}