#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float n = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen)/3) ;
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
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((i == 0) && (j == 0))
            {
                image[0][0].rgbtGreen = round ((image[0][0].rgbtGreen + image[0][1].rgbtGreen + image[1][0].rgbtGreen + image[1][1].rgbtGreen)/4);
                image[0][0].rgbtBlue = round ((image[0][0].rgbtBlue + image[0][1].rgbtBlue + image[1][0].rgbtBlue + image[1][1].rgbtBlue)/4);
                image[0][0].rgbtRed = round ((image[0][0].rgbtRed + image[0][1].rgbtRed + image[1][0].rgbtRed + image[1][1].rgbtRed)/4);
                image[0][width-1].rgbtGreen = round ((image[0][width-2].rgbtGreen + image[0][width-1].rgbtGreen + image[1][width-2].rgbtGreen + image[1][width-1].rgbtGreen)/4);
                image[0][width-1].rgbtRed = round ((image[0][width-2].rgbtRed + image[0][width-1].rgbtRed + image[1][width-2].rgbtRed + image[1][width-1].rgbtRed)/4);
                image[0][width-1].rgbtBlue = round ((image[0][width-2].rgbtBlue + image[0][width-1].rgbtBlue + image[1][width-2].rgbtBlue + image[1][width-1].rgbtBlue)/4);
                image[height-1][0].rgbtGreen = round ((image[height-1][0].rgbtGreen + image[height-2][0].rgbtGreen + image[height-2][1].rgbtGreen + image[height-1][1].rgbtGreen)/4);
                image[height-1][0].rgbtBlue = round ((image[height-1][0].rgbtBlue + image[height-2][0].rgbtBlue + image[height-2][1].rgbtBlue + image[height-1][1].rgbtBlue)/4);
                image[height-1][0].rgbtRed = round ((image[height-1][0].rgbtRed + image[height-2][0].rgbtRed + image[height-2][1].rgbtRed + image[height-1][1].rgbtRed)/4);
                image[height-1][0].rgbtBlue = round ((image[height-1][0].rgbtBlue + image[height-2][0].rgbtBlue + image[height-2][1].rgbtBlue + image[height-1][1].rgbtBlue)/4);
                image[height-1][0].rgbtGreen = round ((image[height-1][0].rgbtGreen + image[height-2][0].rgbtGreen + image[height-2][1].rgbtGreen + image[height-1][1].rgbtGreen)/4);
                image[height-1][0].rgbtRed = round ((image[height-1][0].rgbtRed + image[height-2][0].rgbtRed + image[height-2][1].rgbtRed + image[height-1][1].rgbtRed)/4);

            }
             else if ((i == 0) || (i == height-1))
            {   int sumG = 0;
                int sumR = 0;
                int sumB = 0;
                if (i == 0)
                {
                    for (i = 0; i<2; i++)
                    {
                        for (int k = j-1; k < j+2; k++)
                        {
                             sumG+= image[i][k].rgbtGreen;
                             sumR+= image[i][k].rgbtRed;
                             sumB+= image[i][k].rgbtBlue;
                        }
                    }
                image[0][j].rgbtGreen = round (sumG/6);
                image[0][j].rgbtBlue = round (sumB/6);
                image[0][j].rgbtRed = round (sumR/6);
                }
                else
                {
                    for ( i = height-2; i < height; i++)
                    {
                        for (int k = j-1; k < j+2; k++)
                        {
                            sumG+= image[i][k].rgbtGreen;
                            sumR+= image[i][k].rgbtRed;
                            sumB+= image[i][k].rgbtBlue;
                        }
                    }
                image[height-1][j].rgbtGreen = round (sumG/6);
                image[height-1][j].rgbtBlue = round (sumB/6);
                image[height-1][j].rgbtRed = round (sumR/6);
                }
            }
            else if ((j == 0) || (j == width-1))
            {   int sumG = 0;
                int sumR = 0;
                int sumB = 0;

                if (j == 0)
                {
                    for ( int s = i-1; s < i+1; s++)
                    {
                        for (int k = 0; k < 2; k++)
                        {
                            sumG+= image[s][k].rgbtGreen;
                            sumR+= image[s][k].rgbtRed;
                            sumB+= image[s][k].rgbtBlue;
                        }
                    }
                image[i][0].rgbtGreen = round (sumG/6);
                image[i][0].rgbtBlue = round (sumB/6);
                image[i][0].rgbtRed = round (sumR/6);
                }
                else
                {
                    for (i = i-1; i < i+1; i++)
                    {
                        for (int k = width-2; k < width; k++)
                        {
                            sumG+= image[i][k].rgbtGreen;
                            sumR+= image[i][k].rgbtRed;
                            sumB+= image[i][k].rgbtBlue;
                        }
                    }
                image[i][width-1].rgbtGreen = round (sumG/6);
                image[i][width-1].rgbtBlue = round (sumB/6);
                image[i][width-1].rgbtRed = round (sumR/6);
                }
            }
            else
            {   unsigned int sumG = 0;
                unsigned int sumR = 0;
                unsigned int sumB = 0;
                for (int s = i-1; s < i+2; s++)
                {
                    for (int k = j-1; k < j+2; j++)
                    {
                            sumG+= image[s][k].rgbtGreen;
                            sumR+= image[s][k].rgbtRed;
                            sumB+= image[s][k].rgbtBlue;
                    }
                }
                image[i][j].rgbtGreen = round (sumG/9);
                image[i][j].rgbtBlue = round (sumB/9);
                image[i][j].rgbtRed = round (sumR/9);
            }
        }
    }
}






