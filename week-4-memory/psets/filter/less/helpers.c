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
        for (int j = 0; j < half; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][w - 1];
            image[i][w - 1] = temp;

            w--;
        }
    }
    return;
}

// Blur image
void blur(int h, int w, RGBTRIPLE image[h][w])
{   
    /* pixels should be calculated from the original pixel, so because
    values are changed in place in original pixel it results in incorrect
    calculation in other pixels. That's why another variable is needed to store 
    the the changes without affecting the original pixel/image.*/

    RGBTRIPLE image2[h][w];
    int red;
    int green;
    int blue;
    int height = h - 1; // it prevents index error
    int width = w - 1; // it prevents index error
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            // corners will have 4 pixels to be added and calculated the average

            // top left corner (first row)
            if (i == 0 && j == 0)
            {
                red = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed) / 4.0);
                green = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen) /
                              4.0);
                blue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 4.0);
            }
            // top right corner (first row)
            else if (i == 0 && j == width)
            {
                red = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) / 4.0);
                green = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) /
                              4.0);
                blue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 4.0);
            }
            // bottom left corner (last row)
            else if (i == height && j == 0)
            {
                red = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed) / 4.0);
                green = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen) /
                              4.0);
                blue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue) / 4.0);
            }
            // bottom right corner (last row)
            else if (i == height && j == width)
            {
                red = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed) / 4.0);
                green = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen) /
                              4.0);
                blue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue) / 4.0);
            }
            // corners will have 6 pixels to be added and calculated the average

            // top edges
            else if (i == 0 && j != 0 && j != width)
            {
                red = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j
                             + 1].rgbtRed + image[i][j + 1].rgbtRed) / 6.0);

                green = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                               image[i + 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen) / 6.0);

                blue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i +
                              1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue) / 6.0);
            }
            // bottom edges
            else if (i == height && j != 0 && j != width)
            {
                red = round((image[i][j].rgbtRed + image[height][j - 1].rgbtRed + image[height - 1][j - 1].rgbtRed + image[height - 1][j].rgbtRed +
                             image[height - 1][j + 1].rgbtRed + image[height][j + 1].rgbtRed) / 6.0);

                green = round((image[i][j].rgbtGreen + image[height][j - 1].rgbtGreen + image[height - 1][j - 1].rgbtGreen + image[height -
                               1][j].rgbtGreen + image[height - 1][j + 1].rgbtGreen + image[height][j + 1].rgbtGreen) / 6.0);

                blue = round((image[i][j].rgbtBlue + image[height][j - 1].rgbtBlue + image[height - 1][j - 1].rgbtBlue + image[height -
                              1][j].rgbtBlue + image[height - 1][j + 1].rgbtBlue + image[height][j + 1].rgbtBlue) / 6.0);
            }
            // left edges
            else if (j == 0 && i != 0 && i != height)
            {
                red = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j
                             + 1].rgbtRed + image[i + 1][j].rgbtRed) / 6.0);

                green = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                               image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 6.0);

                blue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i +
                              1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 6.0);
            }
            // right edges
            else if (j == width && i != 0 && i != height)
            {
                red = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j
                             - 1].rgbtRed + image[i + 1][j].rgbtRed) / 6.0);

                green = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen +
                               image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 6.0);

                blue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i +
                              1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 6.0);
            }
            // middle pixel will have 9 pixels to be added and calculated the average
            // the remaining cases (middle pixels)
            else
            {
                red = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j
                             + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed) /
                            9.0);

                green = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                               image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i -
                                       1][j - 1].rgbtGreen) / 9.0);

                blue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i +
                              1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j -
                                      1].rgbtBlue) / 9.0);
            }
            
            // when the pixel is blured, it will assign the result value to new variable without changing the original pixel
            image2[i][j].rgbtRed = red;
            image2[i][j].rgbtGreen = green;
            image2[i][j].rgbtBlue = blue;
            printf("%i %i %i\n", image2[i][j].rgbtRed, image2[i][j].rgbtGreen, image2[i][j].rgbtBlue);
        }
    }
    image = image2; // assigning original image to image2 will result in changing values of original image which will have the blur effect
    return;
}
