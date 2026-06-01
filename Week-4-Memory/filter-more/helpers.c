#include "helpers.h"
#include <math.h>

RGBTRIPLE get_average(int i, int j, int height, int width, RGBTRIPLE copy[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtRed = round(average);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
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
            RGBTRIPLE average = get_average(i, j, height, width, copy);
            image[i][j] = average;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    

    return;
}

// Gets the value that the current RGBTRIPLE should be based on the average of the 3x3 grid it's in
RGBTRIPLE get_average(int i, int j, int height, int width, RGBTRIPLE copy[height][width])
{
    int sum_red = 0, sum_green = 0, sum_blue = 0;
    int count = 0;

    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            // check if i+di and j+dj are valid
            if (i + di < 0 || i + di >= height || j + dj < 0 || j + dj >= width) continue;

            // if valid, add to sums, increment count
            else
            {
                sum_red += copy[i + di][j + dj].rgbtRed;
                sum_green += copy[i + di][j + dj].rgbtGreen;
                sum_blue += copy[i + di][j + dj].rgbtBlue;
                count++;
            }
        }
    }

    RGBTRIPLE average;
    average.rgbtRed = round(sum_red / (float)count);
    average.rgbtGreen = round(sum_green / (float)count);
    average.rgbtBlue = round(sum_blue / (float)count);
    // divide sums by count, return RGBTRIPLE
    return average;

}