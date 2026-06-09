#include "helpers.h"
#include <math.h>

RGBTRIPLE get_average(int i, int j, int height, int width, RGBTRIPLE copy[height][width]);
RGBTRIPLE get_edge(int i, int j, int height, int width, RGBTRIPLE copy[height][width]);
double above_255_check(double edge_value);

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            RGBTRIPLE edge = get_edge(i, j, height, width, copy);
            image[i][j] = edge;
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

RGBTRIPLE get_edge(int i, int j, int height, int width, RGBTRIPLE copy[height][width])
{
    int sum_red_gx = 0, sum_green_gx = 0, sum_blue_gx = 0;
    int sum_red_gy = 0, sum_green_gy = 0, sum_blue_gy = 0;

    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            if (i + di < 0 || i + di >= height || j + dj < 0 || j + dj >= width) continue;

            sum_red_gx += copy[i + di][j + dj].rgbtRed * Gx[di + 1][dj + 1];
            sum_red_gy += copy[i + di][j + dj].rgbtRed * Gy[di + 1][dj + 1];
            sum_green_gx += copy[i + di][j + dj].rgbtGreen * Gx[di + 1][dj + 1];
            sum_green_gy += copy[i + di][j + dj].rgbtGreen * Gy[di + 1][dj + 1];
            sum_blue_gx += copy[i + di][j + dj].rgbtBlue * Gx[di + 1][dj + 1];
            sum_blue_gy += copy[i + di][j + dj].rgbtBlue * Gy[di + 1][dj + 1];
        }
    }
    
    RGBTRIPLE edge;
    edge.rgbtRed = round(above_255_check(sqrt((sum_red_gx * (double)sum_red_gx) + (sum_red_gy * (double)sum_red_gy))));
    edge.rgbtGreen = round(above_255_check(sqrt((sum_green_gx * (double)sum_green_gx) + (sum_green_gy * (double)sum_green_gy))));
    edge.rgbtBlue = round(above_255_check(sqrt((sum_blue_gx * (double)sum_blue_gx) + (sum_blue_gy * (double)sum_blue_gy))));

    return edge;

}

double above_255_check(double edge_value)
{
    if (edge_value >= 255) return 255;
    return edge_value;
}