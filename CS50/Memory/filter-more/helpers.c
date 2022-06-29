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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            double newR = 0;
            double newG = 0;
            double newB = 0;
            double GXsumRed = 0;
            double GXsumGreen = 0;
            double GXsumBlue = 0;
            double GYsumRed = 0;
            double GYsumGreen = 0;
            double GYsumBlue = 0;
            //make 3x3 pixcel average
            for (int near_row = (row - 1); near_row <= (row + 1); near_row++)
            {
                for (int near_column = (column - 1); near_column <= (column + 1); near_column++)
                {
                    //if its in a range of image
                    if ((near_row >= 0 && near_row < height) && (near_column >= 0 && near_column < width))
                    {
                        //for Gx
                        // use forla for corners
                        if (near_row != row && near_column != column)
                        {
                            //by formula be right side
                            if (near_column < column)
                            {
                                GXsumRed += copy[near_row][near_column].rgbtRed * -1;
                                GXsumGreen += copy[near_row][near_column].rgbtGreen * -1;
                                GXsumBlue += copy[near_row][near_column].rgbtBlue * -1;
                            }
                            //by formula for left side
                            else if (near_column > column)
                            {
                                GXsumRed += copy[near_row][near_column].rgbtRed;
                                GXsumGreen += copy[near_row][near_column].rgbtGreen;
                                GXsumBlue += copy[near_row][near_column].rgbtBlue;
                            }
                        }
                        //for middle part
                        if (near_row == row && near_column != column)
                        {
                            //for left sidye by formula
                            if (near_column < column)
                            {
                                GXsumRed += copy[near_row][near_column].rgbtRed * -2;
                                GXsumGreen += copy[near_row][near_column].rgbtGreen * -2;
                                GXsumBlue += copy[near_row][near_column].rgbtBlue * -2;
                            }
                            if (near_column > column)
                            {
                                GXsumRed += copy[near_row][near_column].rgbtRed * 2;
                                GXsumGreen += copy[near_row][near_column].rgbtGreen * 2;
                                GXsumBlue += copy[near_row][near_column].rgbtBlue * 2;
                            }
                        }
                        //for Gy
                        if (near_row != row && near_column != column)
                        {
                            //by formula be right side
                            if (near_row < row)
                            {
                                GYsumRed += copy[near_row][near_column].rgbtRed * -1;
                                GYsumGreen += copy[near_row][near_column].rgbtGreen * -1;
                                GYsumBlue += copy[near_row][near_column].rgbtBlue * -1;
                            }
                            //by formula for left side
                            if (near_row > row)
                            {
                                GYsumRed += copy[near_row][near_column].rgbtRed;
                                GYsumGreen += copy[near_row][near_column].rgbtGreen;
                                GYsumBlue += copy[near_row][near_column].rgbtBlue;
                            }
                        }
                        //for middle part
                        if (near_column == column && near_row != row)
                        {
                            //for up sidye by formula
                            if (near_row < row)
                            {
                                GYsumRed += copy[near_row][near_column].rgbtRed * -2;
                                GYsumGreen += copy[near_row][near_column].rgbtGreen * -2;
                                GYsumBlue += copy[near_row][near_column].rgbtBlue * -2;
                            }
                            if (near_row > row)
                            {
                                GYsumRed += copy[near_row][near_column].rgbtRed * 2;
                                GYsumGreen += copy[near_row][near_column].rgbtGreen * 2;
                                GYsumBlue += copy[near_row][near_column].rgbtBlue * 2;
                            }
                        }
                    }
                }
            }
            newR = (sqrt(pow(GXsumRed, 2) + pow(GYsumRed, 2)));
            newG = (sqrt(pow(GXsumGreen, 2) + pow(GYsumGreen, 2)));
            newB = (sqrt(pow(GXsumBlue, 2) + pow(GYsumBlue, 2)));

            // make sure that values is in rage 0 - 255 24bit colour
            // if its more or less, mak min or max
            if (newR < 0)
            {
                newR = 0;
            }
            //
            else if (newR > 255)
            {
                newR = 255;
            }
            //
            if (newG < 0)
            {
                newG = 0;
            }
            //
            else if (newG > 255)
            {
                newG = 255;
            }
            //
            if (newB < 0)
            {
                newB = 0;
            }
            //
            else if (newB > 255)
            {
                newB = 255;
            }

            image[row][column].rgbtRed = round(newR);
            image[row][column].rgbtGreen = round(newG);
            image[row][column].rgbtBlue = round(newB);
        }
    }
    return;
}
