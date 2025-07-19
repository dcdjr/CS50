#include "helpers.h"
#include <math.h>

float PIXEL_BYTE_AMOUNT = 3.0;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) /
                            PIXEL_BYTE_AMOUNT);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int pixelCounter = 0;
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            for (int h = i - 1; h <= i + 1; h++)
            {
                for (int k = j - 1; k <= j + 1; k++)
                {
                    if (h >= 0 && h < height && k >= 0 && k < width)
                    {
                        pixelCounter++;
                        sumRed += image[h][k].rgbtRed;
                        sumGreen += image[h][k].rgbtGreen;
                        sumBlue += image[h][k].rgbtBlue;
                    }
                }
            }
            int avgRed = round((float) sumRed / pixelCounter);
            int avgGreen = round((float) sumGreen / pixelCounter);
            int avgBlue = round((float) sumBlue / pixelCounter);
            tempImage[i][j].rgbtRed = avgRed;
            tempImage[i][j].rgbtGreen = avgGreen;
            tempImage[i][j].rgbtBlue = avgBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tempImage[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // creates copy of image so as not to edit the memory of the original during the filtering
    // process
    RGBTRIPLE tempImage[height][width];

    // initializes convolutional matrices Gx and Gy to apply to the image
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // iterates through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gx_red = 0;
            int gy_red = 0;
            int gx_green = 0;
            int gy_green = 0;
            int gx_blue = 0;
            int gy_blue = 0;
            int new_red_channel_value;
            int new_green_channel_value;
            int new_blue_channel_value;
            // iterates through the 8 pixels that are between 1 row and 1 column away from the
            // current pixel, including the current pixel
            for (int h = i - 1; h <= i + 1; h++)
            {
                for (int k = j - 1; k <= j + 1; k++)
                {
                    if (h >= 0 && h < height && k >= 0 && k < width)
                    {
                        gx_red += Gx[h - i + 1][k - j + 1] * image[h][k].rgbtRed;
                        gy_red += Gy[h - i + 1][k - j + 1] * image[h][k].rgbtRed;

                        gx_green += Gx[h - i + 1][k - j + 1] * image[h][k].rgbtGreen;
                        gy_green += Gy[h - i + 1][k - j + 1] * image[h][k].rgbtGreen;

                        gx_blue += Gx[h - i + 1][k - j + 1] * image[h][k].rgbtBlue;
                        gy_blue += Gy[h - i + 1][k - j + 1] * image[h][k].rgbtBlue;
                    }
                }
            }
            new_red_channel_value = round(sqrt((gx_red * gx_red) + (gy_red * gy_red)));
            if (new_red_channel_value > 255)
            {
                new_red_channel_value = 255;
            }
            new_green_channel_value = round(sqrt((gx_green * gx_green) + (gy_green * gy_green)));
            if (new_green_channel_value > 255)
            {
                new_green_channel_value = 255;
            }
            new_blue_channel_value = round(sqrt((gx_blue * gx_blue) + (gy_blue * gy_blue)));
            if (new_blue_channel_value > 255)
            {
                new_blue_channel_value = 255;
            }
            tempImage[i][j].rgbtRed = new_red_channel_value;
            tempImage[i][j].rgbtGreen = new_green_channel_value;
            tempImage[i][j].rgbtBlue = new_blue_channel_value;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tempImage[i][j];
        }
    }
}
