#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

int main(int argc, char *argv[])
{
    // Ensure correct number of arguments
    if (argc != 3)
    {
        printf("Usage: ./filter infile outfile\n");
        return 1;
    }

    // Get filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // Ask the user for the filter type
    char filter;
    printf("Enter filter type (b for blur, g for grayscale, r for reflection, s for sepia): ");
    scanf(" %c", &filter);

    // Open input file
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // Open output file
    FILE *outptr = fopen(outfile, "wb");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 3;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;

    if (fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr) != 1)
    {
        printf("Error reading BITMAPFILEHEADER\n");
        fclose(inptr);
        fclose(outptr);
        return 4;
    }

    // Read infile's BITMAPINFOHEADER

    if (fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr) != 1)
    {
        printf("Error reading BITMAPINFOHEADER\n");
        fclose(inptr);
        fclose(outptr);
        return 4;
    }

    // Ensure infile is a 24-bit uncompressed BMP 4.0 (allowing top-down images)
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0 || bi.biHeight == 0)

    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 4;
    }

    // Get image dimensions
    int height = abs(bi.biHeight);
    int width = bi.biWidth;
    int topDown = (bi.biHeight < 0); // Check if the image is top-down

    // Allocate memory for image
    RGBTRIPLE(*image)
    [width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        printf("Not enough memory to store image.\n");
        fclose(outptr);
        fclose(inptr);
        return 5;
    }

    // Determine padding for scanlines
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    // Read image data (handle top-down BMPs correctly)
    if (topDown)
    {
        for (int i = 0; i < height; i++)
        {
            fread(image[i], sizeof(RGBTRIPLE), width, inptr);
            fseek(inptr, padding, SEEK_CUR);
        }
    }
    else
    {
        for (int i = height - 1; i >= 0; i--) // Read bottom-up BMP correctly
        {
            fread(image[i], sizeof(RGBTRIPLE), width, inptr);
            fseek(inptr, padding, SEEK_CUR);
        }
    }

    // Apply selected filter
    switch (filter)
    {
    case 'b':
        blur(height, width, image);
        break;
    case 'g':
        grayscale(height, width, image);
        break;
    case 'r':
        reflect(height, width, image);
        break;
    case 's':
        sepia(height, width, image);
        break;
    default:
        printf("Invalid filter selected.\n");
        free(image);
        fclose(inptr);
        fclose(outptr);
        return 6;
    }

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Write new pixel data
    for (int i = 0; i < height; i++)
    {
        fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // Free allocated memory
    free(image);

    // Close files
    fclose(inptr);
    fclose(outptr);
    return 0;
}
