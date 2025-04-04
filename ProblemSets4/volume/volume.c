#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int HEADER_SIZE = 44;

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "rb"); //
    if (input == NULL)
    {
        printf("Couldnt open the file!\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Couldnt open the file!\n");
        return 1;
    }

    float factor = atof(argv[3]);

    int8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    int16_t buffer;

    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    fclose(input);
    fclose(output);
    return 0;
}