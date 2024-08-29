#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int ave = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = ave;
            image[i][j].rgbtGreen = ave;
            image[i][j].rgbtBlue = ave;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    uint8_t tr, tg, tb;
    for (int i = 0; i < height; i++)
    {
        int k = width - 1;
        for (int j = 0; j < width; j++)
        {
            if (j < k)
            {
                uint8_t r = image[i][j].rgbtRed;
                uint8_t g = image[i][j].rgbtGreen;
                uint8_t b = image[i][j].rgbtBlue;
                image[i][j].rgbtRed = image[i][k].rgbtRed;
                image[i][j].rgbtGreen = image[i][k].rgbtGreen;
                image[i][j].rgbtBlue = image[i][k].rgbtBlue;
                image[i][k].rgbtRed = r;
                image[i][k].rgbtGreen = g;
                image[i][k].rgbtBlue = b;
            }
            k--;
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
            int count = 0;
            int sum1 = 0;
            int sum2 = 0;
            int sum3 = 0;
            int ave1 = 0;
            int ave2 = 0;
            int ave3 = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                if ((k >= 0) && (k < height))
                {
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        if ((l >= 0) && (l < width))
                        {
                            sum1 += image[k][l].rgbtRed;
                            sum2 += image[k][l].rgbtGreen;
                            sum3 += image[k][l].rgbtBlue;
                            count++;
                        }
                    }
                }
            }
            ave1 = round(sum1 / (float) count);
            ave2 = round(sum2 / (float) count);
            ave3 = round(sum3 / (float) count);
            copy[i][j].rgbtRed = ave1;
            copy[i][j].rgbtGreen = ave2;
            copy[i][j].rgbtBlue = ave3;
        }
    }
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            image[m][n].rgbtRed = copy[m][n].rgbtRed;
            image[m][n].rgbtGreen = copy[m][n].rgbtGreen;
            image[m][n].rgbtBlue = copy[m][n].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float Gx1 = 0.0;
            float Gy1 = 0.0;
            float Gx2 = 0.0;
            float Gy2 = 0.0;
            float Gx3 = 0.0;
            float Gy3 = 0.0;
            int finalR = 0;
            int finalG = 0;
            int finalB = 0;
            for (int k = 0; k < 3; k++)
            {
                if (((i - 1 + k) >= 0) && ((i - 1 + k) < height))
                {
                    for (int l = 0; l < 3; l++)
                    {
                        if (((j - 1 + l) >= 0) && ((j - 1 + l) < width))
                        {
                            Gx1 += Gx[k][l] * image[i - 1 + k][j - 1 + l].rgbtRed;
                            Gy1 += Gy[k][l] * image[i - 1 + k][j - 1 + l].rgbtRed;
                            Gx2 += Gx[k][l] * image[i - 1 + k][j - 1 + l].rgbtGreen;
                            Gy2 += Gy[k][l] * image[i - 1 + k][j - 1 + l].rgbtGreen;
                            Gx3 += Gx[k][l] * image[i - 1 + k][j - 1 + l].rgbtBlue;
                            Gy3 += Gy[k][l] * image[i - 1 + k][j - 1 + l].rgbtBlue;
                        }
                    }
                }
            }
            finalR = round(sqrt(pow(Gx1, 2) + pow(Gy1, 2)));
            finalG = round(sqrt(pow(Gx2, 2) + pow(Gy2, 2)));
            finalB = round(sqrt(pow(Gx3, 2) + pow(Gy3, 2)));
            if (finalR > 255)
            {
                finalR = 255;
            }
            if (finalG > 255)
            {
                finalG = 255;
            }
            if (finalB > 255)
            {
                finalB = 255;
            }
            copy[i][j].rgbtRed = finalR;
            copy[i][j].rgbtGreen = finalG;
            copy[i][j].rgbtBlue = finalB;
        }
    }
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            image[m][n].rgbtRed = copy[m][n].rgbtRed;
            image[m][n].rgbtGreen = copy[m][n].rgbtGreen;
            image[m][n].rgbtBlue = copy[m][n].rgbtBlue;
        }
    }
    return;
}
