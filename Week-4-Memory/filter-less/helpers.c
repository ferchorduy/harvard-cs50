#include "helpers.h"
#include <math.h>

int sepia_check(int sepia_value);
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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepiaBlue = (0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue);
            float sepiaGreen = (0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue);
            float sepiaRed = (0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue);
            image[i][j].rgbtBlue = sepia_check(round(sepiaBlue));
            image[i][j].rgbtGreen = sepia_check(round(sepiaGreen));
            image[i][j].rgbtRed = sepia_check(round(sepiaRed));
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

// Checks if a sepia color conversion results in a value higher than the max limit of 255
int sepia_check(int sepia_value)
{
    if (sepia_value >= 255) return 255;
    return sepia_value;
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