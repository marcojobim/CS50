#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover infile\n");
        return 1;
    }

    char *filepath = argv[1];

    FILE *input = fopen(filepath, "rb");
    if (input == NULL)
    {
        printf("Could not open the file\n");
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];
    int file_open = 0;
    char file_name[10];
    FILE *output = NULL;

    while (fread(buffer, sizeof(uint8_t), BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] >= 0xE0 && buffer[3] <= 0xEF))
        {
            if (output != NULL)
            {
                fclose(output);
            }

            sprintf(file_name, "%03d.jpg", file_open);
            output = fopen(file_name, "wb");

            if (output == NULL)
            {
                printf("Could not create file %s\n", file_name);
                fclose(input);
                return 1;
            }
            file_open++;
        }
        if (output != NULL)
        {
            fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, output);
        }
    }
    if (output != NULL)
    {
        fclose(output);
    }
    fclose(input);
    return 0;
}