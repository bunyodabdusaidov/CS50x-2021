#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int new_pixel;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_pixel = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = new_pixel;
            image[i][j].rgbtGreen = new_pixel;
            image[i][j].rgbtBlue = new_pixel;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        int w = width - 1;
        for (int j = 0; j < round(width / 2); j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][w];
            image[i][w] = temp;
            w--;
        }
    }
    return;
}

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img[height][width];
    int rx; // red channel in x dir
    int gx; // green channel in x dir
    int bx; // blue channel in x dir
    int ry; // red channel in y dir
    int gy; // green channel in y dir
    int by; // blue channel in y dir
    int h = height - 1; // height to compare: the last row
    int w = width - 1; // width to compare: the last element/pixel
    int edges[3]; // r, g, b
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // corners will have 4 pixels to be calculate weighted average
            
            // top left corner
            if (i == 0 && j == 0)
            {
                // gx
                rx = (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed * 1) + (image[i + 1][j].rgbtRed * 0);
                gx = (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen * 1) + (image[i + 1][j].rgbtGreen * 0);
                bx = (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue * 1) + (image[i + 1][j].rgbtBlue * 0);
            
                // gy
                ry = (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 0) + (image[i + 1][j + 1].rgbtRed * 1) + (image[i + 1][j].rgbtRed * 2);
                gy = (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 0) + (image[i + 1][j + 1].rgbtGreen * 1) + (image[i + 1][j].rgbtGreen * 2);
                by = (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 0) + (image[i + 1][j + 1].rgbtBlue * 1) + (image[i + 1][j].rgbtBlue * 2);
            }
            // top right corner
            else if (i == 0 && j == w)
            {
                // gx
                rx = (image[i][j].rgbtRed * 0) + (image[i][j - 1].rgbtRed * -2) + (image[i + 1][j - 1].rgbtRed * -1) + (image[i + 1][j].rgbtRed * 0);
                gx = (image[i][j].rgbtGreen * 0) + (image[i][j - 1].rgbtGreen * -2) + (image[i + 1][j - 1].rgbtGreen * -1) + (image[i + 1][j].rgbtGreen * 0);
                bx = (image[i][j].rgbtBlue * 0) + (image[i][j - 1].rgbtBlue * -2) + (image[i + 1][j - 1].rgbtBlue * -1) + (image[i + 1][j].rgbtBlue * 0);

                // gy
                ry = (image[i][j].rgbtRed * 0) + (image[i][j - 1].rgbtRed * 0) + (image[i + 1][j - 1].rgbtRed * 1) + (image[i + 1][j].rgbtRed * 2);
                gy = (image[i][j].rgbtGreen * 0) + (image[i][j - 1].rgbtGreen * 0) + (image[i + 1][j - 1].rgbtGreen * 1) + (image[i + 1][j].rgbtGreen * 2);
                by = (image[i][j].rgbtBlue * 0) + (image[i][j - 1].rgbtBlue * 0) + (image[i + 1][j - 1].rgbtBlue * 1) + (image[i + 1][j].rgbtBlue * 2);
            }
            // bottom left corner
            else if (i == h && j == 0)
            {
                // gx
                rx = (image[i][j].rgbtRed * 0) + (image[i - 1][j].rgbtRed * 0) + (image[i - 1][j + 1].rgbtRed * 1) + (image[i][j + 1].rgbtRed * 2);
                gx = (image[i][j].rgbtGreen * 0) + (image[i - 1][j].rgbtGreen * 0) + (image[i - 1][j + 1].rgbtGreen * 1) + (image[i][j + 1].rgbtGreen * 2);
                bx = (image[i][j].rgbtBlue * 0) + (image[i - 1][j].rgbtBlue * 0) + (image[i - 1][j + 1].rgbtBlue * 1) + (image[i][j + 1].rgbtBlue * 2);

                // gy
                ry = (image[i][j].rgbtRed * 0) + (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1) + (image[i][j + 1].rgbtRed * 0);
                gy = (image[i][j].rgbtGreen * 0) + (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1) + (image[i][j + 1].rgbtGreen * 0);
                by = (image[i][j].rgbtBlue * 0) + (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1) + (image[i][j + 1].rgbtBlue * 0);
            }
            // bottom right corner
            else if (i == h && j == w)
            {
                // gx
                rx = (image[i][j].rgbtRed * 0) + (image[i][j - 1].rgbtRed * -2) + (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * 0);
                gx = (image[i][j].rgbtGreen * 0) + (image[i][j - 1].rgbtGreen * -2) + (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * 0);
                bx = (image[i][j].rgbtBlue * 0) + (image[i][j - 1].rgbtBlue * -2) + (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * 0);

                // gy
                ry = (image[i][j].rgbtRed * 0) + (image[i][j - 1].rgbtRed * 0) + (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2);
                gy = (image[i][j].rgbtGreen * 0) + (image[i][j - 1].rgbtGreen * 0) + (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2);
                by = (image[i][j].rgbtBlue * 0) + (image[i][j - 1].rgbtBlue * 0) + (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2);
            }
            // top edge
            else if (i == 0 && j != 0 && j != w)
            {
                // gx
                rx = (image[i][j].rgbtRed * 0) + (image[i][j - 1].rgbtRed * -2) + (image[i + 1][j - 1].rgbtRed * -1) + (image[i + 1][j].rgbtRed * 0) + (image[i + 1][j + 1].rgbtRed * 1) + (image[i][j + 1].rgbtRed * 2);
                gx = (image[i][j].rgbtGreen * 0) + (image[i][j - 1].rgbtGreen * -2) + (image[i + 1][j - 1].rgbtGreen * -1) + (image[i + 1][j].rgbtGreen * 0) + (image[i + 1][j + 1].rgbtGreen * 1) + (image[i][j + 1].rgbtGreen * 2);
                bx = (image[i][j].rgbtBlue * 0) + (image[i][j - 1].rgbtBlue * -2) + (image[i + 1][j - 1].rgbtBlue * -1) + (image[i + 1][j].rgbtBlue * 0) + (image[i + 1][j + 1].rgbtBlue * 1) + (image[i][j + 1].rgbtBlue * 2);

                // gy
                ry = (image[i][j].rgbtRed * 0) + (image[i][j - 1].rgbtRed * 0) + (image[i + 1][j - 1].rgbtRed * 1) + (image[i + 1][j].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed * 1) + (image[i][j + 1].rgbtRed * 0);
                gy = (image[i][j].rgbtGreen * 0) + (image[i][j - 1].rgbtGreen * 0) + (image[i + 1][j - 1].rgbtGreen * 1) + (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen * 1) + (image[i][j + 1].rgbtGreen * 0);
                by = (image[i][j].rgbtBlue * 0) + (image[i][j - 1].rgbtBlue * 0) + (image[i + 1][j - 1].rgbtBlue * 1) + (image[i + 1][j].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue * 1) + (image[i][j + 1].rgbtBlue * 0);
            }
            // bottom edge
            else if (i == h && j != 0 && j != w)
            {
                // gx
                rx = (image[i][j].rgbtRed * 0) + (image[i][j - 1].rgbtRed * -2) + (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * 0) + (image[i - 1][j + 1].rgbtRed * 1) + (image[i][j + 1].rgbtRed * 2);
                gx = (image[i][j].rgbtGreen * 0) + (image[i][j - 1].rgbtGreen * -2) + (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * 0) + (image[i - 1][j + 1].rgbtGreen * 1) + (image[i][j + 1].rgbtGreen * 2);
                bx = (image[i][j].rgbtBlue * 0) + (image[i][j - 1].rgbtBlue * -2) + (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * 0) + (image[i - 1][j + 1].rgbtBlue * 1) + (image[i][j + 1].rgbtBlue * 2);

                // gy
                ry = (image[i][j].rgbtRed * 0) + (image[i][j - 1].rgbtRed * 0) + (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1) + (image[i][j + 1].rgbtRed * 0);
                gy = (image[i][j].rgbtGreen * 0) + (image[i][j - 1].rgbtGreen * 0) + (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1) + (image[i][j + 1].rgbtGreen * 0);
                by = (image[i][j].rgbtBlue * 0) + (image[i][j - 1].rgbtBlue * 0) + (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1) + (image[i][j + 1].rgbtBlue * 0);
            }
            // left edge
            else if (j == 0 && i != 0 && i != h)
            {
                // gx
                rx = (image[i][j].rgbtRed * 0) + (image[i - 1][j].rgbtRed * 0) + (image[i - 1][j + 1].rgbtRed * 1) + (image[i][j + 1].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed * 1) + (image[i  + 1][j].rgbtRed * 0);
                gx = (image[i][j].rgbtGreen * 0) + (image[i - 1][j].rgbtGreen * 0) + (image[i - 1][j + 1].rgbtGreen * 1) + (image[i][j + 1].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen * 1) + (image[i + 1][j].rgbtGreen * 0);
                bx = (image[i][j].rgbtBlue * 0) + (image[i - 1][j].rgbtBlue * 0) + (image[i - 1][j + 1].rgbtBlue * 1) + (image[i][j + 1].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue * 1) + (image[i  + 1][j].rgbtBlue * 0);
                
                // gy
                ry = (image[i][j].rgbtRed * 0) + (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j - 1].rgbtRed * -1) + (image[i][j + 1].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed * 1) + (image[i  + 1][j].rgbtRed * 0);
                gy = (image[i][j].rgbtGreen * 0) + (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j - 1].rgbtGreen * -1) + (image[i][j + 1].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen * 1) + (image[i + 1][j].rgbtGreen * 0);
                by = (image[i][j].rgbtBlue * 0) + (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j - 1].rgbtBlue * -1) + (image[i][j + 1].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue * 1) + (image[i  + 1][j].rgbtBlue * 0);
            }
            
            edges[0] = round(sqrt(pow(rx, 2) + pow(ry, 2)));
            edges[1] = round(sqrt(pow(gx, 2) + pow(gy, 2)));
            edges[2] = round(sqrt(pow(bx, 2) + pow(by, 2)));
            for (int n = 0; n < 3; n++)
            {
                if (edges[n] > 255)
                {
                    edges[n] = 255;
                }
            }
            img[i][j].rgbtRed = edges[0];
            img[i][j].rgbtGreen = edges[1];
            img[i][j].rgbtBlue = edges[2];
            printf("%i %i %i\n", img[i][j].rgbtRed, img[i][j].rgbtGreen, img[i][j].rgbtBlue);
        }
    }
    image = img;
    return;
}
