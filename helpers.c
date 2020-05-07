#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int n = round (((float) image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen)/3);
            image[i][j].rgbtBlue = n;
            image[i][j].rgbtRed = n;
            image[i][j].rgbtGreen = n;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round (.189 * image[i][j].rgbtBlue + .769 * image[i][j].rgbtGreen + .393 * image[i][j].rgbtRed);
            int sepiaGreen = round (.168 * image[i][j].rgbtBlue + .686 * image[i][j].rgbtGreen + .349 * image[i][j].rgbtRed);
            int sepiaBlue = round (.131 * image[i][j].rgbtBlue + .534 * image[i][j].rgbtGreen + .272 * image[i][j].rgbtRed);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
          image[i][j].rgbtRed = sepiaRed;
          image[i][j].rgbtGreen = sepiaGreen;
          image[i][j].rgbtBlue = sepiaBlue;

        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0 , k = width-1; j < k; j++ ,k--)
        {
              RGBTRIPLE temp = image[i][j];
              image[i][j] = image[i][k];
              image[i][k] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{   for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {   int n = i;
            int m = j;
            if (((i == 0) || (i == height-1)) && ((j == 0) || (j == width-1)))
            {   int sumG = 0;
                int sumR = 0;
                int sumB = 0;
                int count = 0;
                if ((i == 0) && (j == 0))
                {
                    for (int s = 0; s < 2; s++)
                    {
                        for (int k = 0; k < 2; k++)
                        {
                            if ((s < height) && (k < width))
                            {
                                sumG+= image[s][k].rgbtGreen;
                                sumR+= image[s][k].rgbtRed;
                                sumB+= image[s][k].rgbtBlue;
                                count+= 1;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }
                    image[0][0].rgbtGreen = round ((float) sumG/count);
                    image[0][0].rgbtRed = round ((float) sumR/count);
                    image[0][0].rgbtBlue = round ((float) sumB/count);
                }
                else if ((i == 0) && (j == width-1))
                {
                    for (int s = 0; s < 2; s++)
                    {
                        for (int k = width-2; k < width; k++)
                        {
                            if ((s < height) && (k < width))
                            {
                                sumG+= image[s][k].rgbtGreen;
                                sumR+= image[s][k].rgbtRed;
                                sumB+= image[s][k].rgbtBlue;
                                count+= 1;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }
                    image[0][width-1].rgbtGreen = round ((float) sumG/count);
                    image[0][width-1].rgbtRed = round ((float) sumR/count);
                    image[0][width-1].rgbtBlue = round ((float) sumB/count);
                }
                else if ((i == height-1) && (j == 0))
                {
                   for (int s = height-2; s < height; s++)
                    {
                        for (int k = 0; k < 2; k++)
                        {
                            if (((s < height) && (k < width)) && ((s >= 0) && (k >= 0)))
                            {
                                sumG+= image[s][k].rgbtGreen;
                                sumR+= image[s][k].rgbtRed;
                                sumB+= image[s][k].rgbtBlue;
                                count+= 1;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }
                    image[height-1][0].rgbtGreen = round ((float) sumG/count);
                    image[height-1][0].rgbtRed = round ((float) sumR/count);
                    image[height-1][0].rgbtBlue = round ((float) sumB/count);
                }
                else
                {
                   for (int s = height-2; s < height; s++)
                    {
                        for (int k = width-2; k < width; k++)
                        {
                            if (((s < height) && (k < width)) && ((s >= 0) && (k >= 0)))
                            {
                                sumG+= image[s][k].rgbtGreen;
                                sumR+= image[s][k].rgbtRed;
                                sumB+= image[s][k].rgbtBlue;
                                count+= 1;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }
                    image[height-1][width-1].rgbtGreen = round ((float) sumG/count);
                    image[height-1][width-1].rgbtRed = round ((float) sumR/count);
                    image[height-1][width-1].rgbtBlue = round ((float) sumB/count);
                }
            }

            else if ((i == 0) || (i == height-1))
            {   int sumG = 0;
                int sumR = 0;
                int sumB = 0;
                int count = 0;
                if (i == 0)
                {
                    for (int s = 0; s<2; s++)
                    {
                        for (int k = m-1; k < m+2; k++)
                        {    if (((s < height) && (k < width)) && ((s >= 0) && (k >= 0)))
                             {
                                sumG+= image[s][k].rgbtGreen;
                                sumR+= image[s][k].rgbtRed;
                                sumB+= image[s][k].rgbtBlue;
                                count+= 1;
                             }
                             else
                             {
                                 continue;
                             }
                        }
                    }
                image[0][j].rgbtGreen = round ( (float) sumG/count);
                image[0][j].rgbtBlue = round ( (float) sumB/count);
                image[0][j].rgbtRed = round ( (float) sumR/count);
                }
                else
                {
                    for (int s = height-2; s < height; s++)
                    {
                        for (int k = m-1; k < m+2; k++)
                        {   if (((s < height) && (k < width)) && ((s >= 0) && (k >= 0)))
                            {   sumG+= image[s][k].rgbtGreen;
                                sumR+= image[s][k].rgbtRed;
                                sumB+= image[s][k].rgbtBlue;
                                count+=1;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }
                image[height-1][j].rgbtGreen = round ( (float) sumG/count);
                image[height-1][j].rgbtBlue = round ( (float) sumB/count);
                image[height-1][j].rgbtRed = round ( (float) sumR/count);
                }
            }
            else if ((j == 0) || (j == width-1))
            {   int sumG = 0;
                int sumR = 0;
                int sumB = 0;
                int count = 0;

                if (j == 0)
                {
                    for ( int s = n-1; s < n+2; s++)
                    {
                        for (int k = 0; k < 2; k++)
                        {   if (((s < height) && (k < width)) && ((s >= 0) && (k >= 0)))
                            {   sumG+= image[s][k].rgbtGreen;
                                sumR+= image[s][k].rgbtRed;
                                sumB+= image[s][k].rgbtBlue;
                                count+= 1;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }
                image[i][0].rgbtGreen = round ( (float) sumG/count);
                image[i][0].rgbtBlue = round ( (float) sumB/count);
                image[i][0].rgbtRed = round ( (float) sumR/count);
                }
                else
                {
                    for (int s = n-1; s < n+2; s++)
                    {
                        for (int k = width-2; k < width; k++)
                        {   if (((s < height) && (k < width)) && ((s >= 0) && (k >= 0)))
                            {   sumG+= image[s][k].rgbtGreen;
                                sumR+= image[s][k].rgbtRed;
                                sumB+= image[s][k].rgbtBlue;
                                count+= 1;
                            }
                        }
                image[i][width-1].rgbtGreen = round ( (float) sumG/count);
                image[i][width-1].rgbtBlue = round ( (float) sumB/count);
                image[i][width-1].rgbtRed = round ( (float) sumR/count);
                    }
                }
            }
            else
            {    int sumG = 0;
                 int sumR = 0;
                 int sumB = 0;
                 int count = 0;
                for (int s = n-1; s < n+2; s++)
                {
                    for (int k = m-1; k < m+2; k++)
                    {   if (((s < height) && (k < width)) && ((s >= 0) && (k >= 0)))
                        {    sumG+= image[s][k].rgbtGreen;
                             sumR+= image[s][k].rgbtRed;
                             sumB+= image[s][k].rgbtBlue;
                             count+= 1;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                image[i][j].rgbtGreen = round ( (float) sumG/count);
                image[i][j].rgbtBlue = round ( (float) sumB/count);
                image[i][j].rgbtRed = round ( (float) sumR/count);
            }
        }
    }
}













