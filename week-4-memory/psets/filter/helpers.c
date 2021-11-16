#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{   
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int new_pixel = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = new_pixel;
            image[i][j].rgbtGreen = new_pixel;
            image[i][j].rgbtRed = new_pixel;
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
            int original[] = {image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue};
            int sepia[3];

            sepia[0] = round(.393 * original[0] + .769 * original[1] + .189 * original[2]);
            sepia[1] = round(.349 * original[0] + .686 * original[1] + .168 * original[2]);
            sepia[2] = round(.272 * original[0] + .534 * original[1] + .131 * original[2]);

            for (int n = 0; n < 3; n++)
            {
                if (sepia[n] > 255)
                {
                    sepia[n] = 255;
                }
            }

            image[i][j].rgbtBlue = sepia[2];
            image[i][j].rgbtGreen = sepia[1];
            image[i][j].rgbtRed = sepia[0];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int half = round(width / 2);
    for (int i = 0; i < height; i++)
    {
        int w = width;
        printf("w: %i\n", half);
        for (int j = 0; j < half; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][w-1];
            image[i][w-1] = temp;

            w--;
        }
    }
    return;
}

// Blur image
void blur(int h, int w, RGBTRIPLE image[h][w])
{    
    int red;
    int green;
    int blue;
    int height = h - 1;
    int width = w - 1;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            // top left corner (first row)
            if (i == 0 && j == 0)
            {
                red = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed +image[i + 1][j].rgbtRed) / 4.0);
                green = round((image[i][j].rgbtGreen + image[i][j+ 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 4.0);
                blue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 4.0);
                //printf("top left corner: i = %i, j = %i\n", i, j);
            }
            // top right corner (first row)
            else if (i == 0 && j == width)
            {
                red = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) / 4.0);
                green = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 4.0);
                blue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 4.0);
                //printf("top right corner: i = %i, j = %i\n", i, j);
            }
            // bottom left corner (last row)
            else if (i == height && j == 0)
            {
                red = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed) / 4.0);
                green = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen) / 4.0);
                blue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue) / 4.0);
                //printf("bottom left corner: i = %i, j = %i\n", i, j);
            }
            // bottom right corner (last row)
            else if (i == height && j == width)
            {
                red = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed) / 4.0);
                green = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen) /
                    4.0);
                blue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue) / 4.0);
                //printf("bottom right corner: i = %i, j = %i\n", i, j);
            }

            // top edges
            else if (i == 0 && j != 0 && j != width)
            {
                printf("top edge\n");
                red = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed +
                 image[i][j + 1].rgbtRed) / 6.0);
                printf("red: %i + %i + %i + %i + %i + %i\n", image[i][j].rgbtRed, image[i][j - 1].rgbtRed, image[i + 1][j - 1].rgbtRed, image[i + 1][j].rgbtRed, image[i + 1][j + 1].rgbtRed, image[i][j + 1].rgbtRed);
;                
                green = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen 
                + image[i][j + 1].rgbtGreen) / 6.0);
                printf("green: %i + %i + %i + %i + %i + %i\n", image[i][j].rgbtGreen, image[i][j - 1].rgbtGreen, image[i + 1][j - 1].rgbtGreen, image[i + 1][j].rgbtGreen, image[i + 1][j + 1].rgbtGreen, image[i][j + 1].rgbtGreen);

                blue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                 image[i][j + 1].rgbtBlue) / 6.0);
                printf("blue: %i + %i + %i + %i + %i + %i\n", image[i][j].rgbtBlue, image[i][j - 1].rgbtBlue, image[i + 1][j - 1].rgbtBlue, image[i + 1][j].rgbtBlue, image[i + 1][j + 1].rgbtBlue, image[i][j + 1].rgbtBlue);

                //printf("top edge: i = %i, j = %i\n", i, j);
            }
            // bottom edges
            else if (i == height && j != 0 && j != width)
            {
                printf("bottom edge\n");
                red = round((image[i][j].rgbtRed + image[height][j - 1].rgbtRed + image[height - 1][j - 1].rgbtRed + image[height - 1][j].rgbtRed + image[height - 1][j +
                 1].rgbtRed + image[height][j + 1].rgbtRed) / 6.0);
                printf("red: %i + %i + %i + %i + %i + %i\n", image[i][j].rgbtRed, image[height][j - 1].rgbtRed, image[height - 1][j - 1].rgbtRed, image[height - 1][j].rgbtRed, image[height - 1][j + 1].rgbtRed, image[height][j + 1].rgbtRed);

                green = round((image[i][j].rgbtGreen + image[height][j - 1].rgbtGreen + image[height - 1][j - 1].rgbtGreen + image[height - 1][j].rgbtGreen + image[height -
                 1][j + 1].rgbtGreen + image[height][j + 1].rgbtGreen) / 6.0);
                printf("green: %i + %i + %i + %i + %i + %i\n", image[i][j].rgbtGreen, image[height][j - 1].rgbtGreen, image[height - 1][j - 1].rgbtGreen, image[height - 1][j].rgbtGreen, image[height - 1][j + 1].rgbtGreen, image[height][j + 1].rgbtGreen);

                blue = round((image[i][j].rgbtBlue + image[height][j - 1].rgbtBlue + image[height - 1][j - 1].rgbtBlue + image[height - 1][j].rgbtBlue + image[height -
                 1][j + 1].rgbtBlue + image[height][j + 1].rgbtBlue) / 6.0);
                printf("blue: %i + %i + %i + %i + %i + %i\n", image[i][j].rgbtBlue, image[height][j - 1].rgbtBlue, image[height - 1][j - 1].rgbtBlue, image[height - 1][j].rgbtBlue, image[height - 1][j + 1].rgbtBlue, image[height][j + 1].rgbtBlue);

                //printf("bottom edge: i = %i, j = %i\n", i, j);
            }
            // left edges
            else if (j == 0 && i != 0 && i != height)
            {
                printf("left edge\n");
                red = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i
                 + 1][j].rgbtRed) / 6.0);
                printf("red: %i + %i + %i + %i + %i + %i\n", image[i][j].rgbtRed, image[i - 1][j].rgbtRed, image[i - 1][j + 1].rgbtRed, image[i][j + 1].rgbtRed, image[i + 1][j + 1].rgbtRed, image[i + 1][j].rgbtRed);

                green = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen
                 + image[i + 1][j].rgbtGreen) / 6.0);
                printf("green: %i + %i + %i + %i + %i + %i\n", image[i][j].rgbtGreen, image[i - 1][j].rgbtGreen, image[i - 1][j + 1].rgbtGreen, image[i][j + 1].rgbtGreen, image[i + 1][j + 1].rgbtGreen, image[i + 1][j].rgbtGreen);

                blue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                 image[i + 1][j].rgbtBlue) / 6.0);
                printf("blue: %i + %i + %i + %i + %i + %i\n", image[i][j].rgbtBlue, image[i - 1][j].rgbtBlue, image[i - 1][j + 1].rgbtBlue, image[i][j + 1].rgbtBlue, image[i + 1][j + 1].rgbtBlue, image[i + 1][j].rgbtBlue);

                //printf("left edge: i = %i, j = %i\n", i, j);
            }
            // right edges
            else if (j == width && i != 0 && i != height)
            {
                printf("right edge\n");
                red = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i
                 + 1][j].rgbtRed) / 6.0);
                printf("red: %i + %i + %i + %i + %i + %i\n", image[i][j].rgbtRed, image[i - 1][j].rgbtRed, image[i - 1][j - 1].rgbtRed, image[i][j - 1].rgbtRed, image[i + 1][j - 1].rgbtRed, image[i + 1][j].rgbtRed);

                green = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen
                 + image[i + 1][j].rgbtGreen) / 6.0);
                printf("green: %i + %i + %i + %i + %i + %i\n", image[i][j].rgbtGreen, image[i - 1][j].rgbtGreen, image[i - 1][j - 1].rgbtGreen, image[i][j - 1].rgbtGreen, image[i + 1][j - 1].rgbtGreen, image[i + 1][j].rgbtGreen);

                blue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue
                 + image[i + 1][j].rgbtBlue) / 6.0);
                printf("blue: %i + %i + %i + %i + %i + %i\n", image[i][j].rgbtBlue, image[i - 1][j].rgbtBlue, image[i - 1][j - 1].rgbtBlue, image[i][j - 1].rgbtBlue, image[i + 1][j - 1].rgbtBlue, image[i + 1][j].rgbtBlue);

                //printf("right edge: i = %i, j = %i\n", i, j);
            }
            // the remaining cases (middle pixels)
            else
            {
                printf("middle\n");
                red = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i
                 + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 9.0);
                printf("red: %i + %i + %i + %i + %i + %i + %i + %i + %i\n", image[i][j].rgbtRed, image[i - 1][j].rgbtRed, image[i - 1][j + 1].rgbtRed, image[i][j + 1].rgbtRed, image[i + 1][j + 1].rgbtRed, image[i
                 + 1][j].rgbtRed, image[i + 1][j - 1].rgbtRed, image[i][j - 1].rgbtRed, image[i - 1][j - 1].rgbtRed);

                green = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen
                 + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 9.0);
                printf("green: %i + %i + %i + %i + %i + %i + %i + %i + %i\n", image[i][j].rgbtGreen, image[i - 1][j].rgbtGreen, image[i - 1][j + 1].rgbtGreen, image[i][j + 1].rgbtGreen, image[i + 1][j + 1].rgbtGreen, image[i + 1][j].rgbtGreen, image[i + 1][j - 1].rgbtGreen, image[i][j - 1].rgbtGreen, image[i - 1][j - 1].rgbtGreen);

                blue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                 image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 9.0);
                printf("blue: %i + %i + %i + %i + %i + %i + %i + %i + %i\n", image[i][j].rgbtBlue, image[i - 1][j].rgbtBlue, image[i - 1][j + 1].rgbtBlue, image[i][j + 1].rgbtBlue, image[i + 1][j + 1].rgbtBlue, 
                 image[i + 1][j].rgbtBlue, image[i + 1][j - 1].rgbtBlue, image[i][j - 1].rgbtBlue, image[i - 1][j - 1].rgbtBlue);
                //printf("middle: i = %i, j = %i\n", i, j);
            }
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
            printf("%i %i %i\n", image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
        }
    }
    return;
}
