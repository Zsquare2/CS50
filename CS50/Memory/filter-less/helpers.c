#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            float r = image[row][column].rgbtRed;
            float g = image[row][column].rgbtGreen;
            float b = image[row][column].rgbtBlue;

            int average = round((r + g + b) / 3);

            image[row][column].rgbtRed = average;
            image[row][column].rgbtGreen = average;
            image[row][column].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            double r = image[row][column].rgbtRed;
            double g = image[row][column].rgbtGreen;
            double b = image[row][column].rgbtBlue;

            // convert to sepia value

            int sepiaRed =   round((0.393 * r) + (0.769 * g) + (0.189 * b));
            int sepiaGreen = round((0.349 * r) + (0.686 * g) + (0.168 * b));
            int sepiaBlue =  round((0.272 * r) + (0.534 * g) + (0.131 * b));
            // make sure that values is in rage 0 - 255 24bit colour
            // if its more or less, mak min or max
            if (sepiaRed < 0)
            {
                sepiaRed = 0;
            }
            //
            else if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            //
            if (sepiaGreen < 0)
            {
                sepiaGreen = 0;
            }
            //
            else if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            //
            if (sepiaBlue < 0)
            {
                sepiaBlue = 0;
            }
            //
            else if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            // change values
            image[row][column].rgbtRed = sepiaRed;
            image[row][column].rgbtGreen = sepiaGreen;
            image[row][column].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
//    int back = width;
    for (int row = 0; row < height; row++)
    {
        double temp;
        for (int column = 0, back = width - 1; column < width / 2; column++, back--)
        {
            temp = image[row][column].rgbtRed;
            image[row][column].rgbtRed = image[row][back].rgbtRed;
            image[row][back].rgbtRed = temp;

            temp = image[row][column].rgbtGreen;
            image[row][column].rgbtGreen = image[row][back].rgbtGreen;
            image[row][back].rgbtGreen = temp;

            temp = image[row][column].rgbtBlue;
            image[row][column].rgbtBlue = image[row][back].rgbtBlue;
            image[row][back].rgbtBlue = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make image copy
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    //for every pixcel
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            double averageR = 0;
            double averageG = 0;
            double averageB = 0;
            double sumRed = 0;
            double sumGreen = 0;
            double sumBlue = 0;
            int ok_counter = 0;
            //make 3x3 pixcel average
            for (int blure_row = (row - 1); blure_row <= (row + 1); blure_row++)
            {
                for (int blure_column = (column - 1); blure_column <= (column + 1); blure_column++)
                {
                    //if its in a range of image
                    if ((blure_row >= 0 && blure_row < height) && (blure_column >= 0 && blure_column < width))
                    {
                        ok_counter++;
                        sumRed += copy[blure_row][blure_column].rgbtRed;
                        sumGreen += copy[blure_row][blure_column].rgbtGreen;
                        sumBlue += copy[blure_row][blure_column].rgbtBlue;
                    }
                }
            }
            averageR = sumRed / ok_counter;
            averageG = sumGreen / ok_counter;
            averageB = sumBlue / ok_counter;

            image[row][column].rgbtRed = round(averageR);
            image[row][column].rgbtGreen = round(averageG);
            image[row][column].rgbtBlue = round(averageB);
        }
    }
    return;
}
