#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int n = round(((float) image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3);
            image[i][j].rgbtBlue = n;
            image[i][j].rgbtRed = n;
            image[i][j].rgbtGreen = n;
        }
    }
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1; j < k; j++, k--)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumG = 0;
            int sumR = 0;
            int sumB = 0;
            int count = 0;
            for (int s = i-1; s < i+2; s++)
            {
                for (int k = j-1; k < j+2; k++)
                {
                    if ((s < height) && (s >=0) && (k < width) && (k >=0))
                    {
                        sumG += image[s][k].rgbtGreen;
                        sumR += image[s][k].rgbtRed;
                        sumB += image[s][k].rgbtBlue;
                        count += 1;
                    }
                    else
                    {
                        sumG += 0;
                        sumR += 0;
                        sumB += 0;
                    }
                }
            }
            image[i][j].rgbtGreen = round((float)sumG / count);
            image[i][j].rgbtRed = round((float)sumR / count );
            image[i][j].rgbtBlue = round((float)sumB / count);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int Gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumG = 0;
            int sumg = 0;
            int sumR = 0;
            int sumr = 0;
            int sumB = 0;
            int sumb = 0;

            for (int s = i-1; s < i+2; s++)
            for (int c = 0; c < 3; c++)
            {
                for (int k = j-1; k < j+2; k++)
                for (int d = 0; d < 3; d++)
                {   if ((s < height) && (s >= 0) && (k < width) && (k >=0))
                    {   sumG += image[s][k].rgbtGreen * Gx[c][d];
                        sumg += image[s][k].rgbtGreen * Gy[c][d];
                        sumR += image[s][k].rgbtRed * Gx[c][d];
                        sumr += image[s][k].rgbtRed * Gy[c][d];
                        sumB += image[s][k].rgbtBlue * Gx[c][d];
                        sumb += image[s][k].rgbtBlue * Gy[c][d];
                    }
                    else
                    {
                        sumG += 0;
                        sumg += 0;
                        sumR += 0;
                        sumr += 0;
                        sumB += 0;
                        sumb += 0;
                    }
                }
            }
        int g = round(sqrt(sumG*sumG + sumg*sumg));
        int r = round(sqrt(sumR*sumR + sumr*sumr));
        int b = round(sqrt(sumB*sumB + sumb*sumb));
        if (g > 255)
        {
            g = 255;
        }
        if (r > 255)
        {
            r = 255;
        }
        if (b > 255)
        {
            b = 255;
        }
        image[i][j].rgbtGreen = g;
        image[i][j].rgbtRed = r;
        image[i][j].rgbtBlue = b;

        }
   }
}

