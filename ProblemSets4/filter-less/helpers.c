#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE gray;
            gray = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtBlue = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepia_red;
            float sepia_green;
            float sepia_blue;

            BYTE original_red = image[i][j].rgbtRed;
            BYTE original_green = image[i][j].rgbtGreen;
            BYTE original_blue = image[i][j].rgbtBlue;

            sepia_red = .393 * original_red + .769 * original_green + .189 * original_blue;
            sepia_green = .349 * original_red + .686 * original_green + .168 * original_blue;
            sepia_blue = .272 * original_red + .534 * original_green + .131 * original_blue;

            if (sepia_red > 255)
                image[i][j].rgbtRed = 255;
            else
            {
                image[i][j].rgbtRed = (BYTE)sepia_red;
            }
            if (sepia_green > 255)
                image[i][j].rgbtGreen = 255;
            else
            {
                image[i][j].rgbtGreen = (BYTE)sepia_green;
            }
            if (sepia_blue > 255)
                image[i][j].rgbtBlue = 255;
            else
            {
                image[i][j].rgbtBlue = (BYTE)sepia_blue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int middle = width / 2;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < middle; j++)
        {
            // Troca os pixels da esquerda com os da direita
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red_sum = 0, green_sum = 0, blue_sum = 0;
            int count = 0;

            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int new_i = i + x;
                    int new_j = j + y;

                    if (new_i >= 0 && new_i < height && new_j >= 0 && new_j < width)
                    {
                        red_sum += copy[new_i][new_j].rgbtRed;
                        green_sum += copy[new_i][new_j].rgbtGreen;
                        blue_sum += copy[new_i][new_j].rgbtBlue;
                        count++;
                    }
                }
            }
            image[i][j].rgbtRed = red_sum / count;
            image[i][j].rgbtGreen = green_sum / count;
            image[i][j].rgbtBlue = blue_sum / count;
        }
    }

    return;
}
