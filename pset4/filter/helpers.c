#include "helpers.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //nested for loops to go through each pixel row by row - this is extensively used through the program
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //using float and then using round function to ensure correct rounding when converted to int
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = round(average);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calc midpoint to act as axis for reflection
            float midpoint = (width - 1) / 2.0;
            if (j < midpoint)
            {
                //tmp variable to hold original value for copying
                RGBTRIPLE tmp = image[i][j];
                int dest = (midpoint - j) + midpoint;
                image[i][j] = image[i][dest];
                image[i][dest] = tmp;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //declaring a space in the memory heap the same size as image
    RGBTRIPLE(*imagecopy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    //copying  image into the new table
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imagecopy[i][j] = image[i][j];
        }
    }
    //starting the process of going through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // have opted for to go through each case (ie top-edge, top-right-corner etc). This was so I could
            // fully understand the process and work through each scenario. In hindsight I would opt for a loop
            // that would use a counter to count up how many successful values it has pulled so I know what to divide
            // by to work out the average. I did not previously know you could detect value that are not in the multi-
            // dimensional array. This would have made the function (edge) much quicker, although the actual process was
            // fairly easy to work out - it would have saved a lot of lines of code and time!
            int averageRed;
            int averageBlue;
            int averageGreen;

            //TOP-LEFT-CORNER
            if (i == 0 && j == 0)
            {
                //order of pixels in matrix accessed is a scattered in this effect.
                averageRed = round((imagecopy[i][j + 1].rgbtRed + imagecopy[i + 1][j].rgbtRed +
                                    imagecopy[i + 1][j + 1].rgbtRed + imagecopy[i][j].rgbtRed) / 4.0);

                averageBlue = round((imagecopy[i][j + 1].rgbtBlue + imagecopy[i + 1][j].rgbtBlue +
                                     imagecopy[i + 1][j + 1].rgbtBlue + imagecopy[i][j].rgbtBlue) / 4.0);

                averageGreen = round((imagecopy[i][j + 1].rgbtGreen + imagecopy[i + 1][j].rgbtGreen +
                                      imagecopy[i + 1][j + 1].rgbtGreen +  + imagecopy[i][j].rgbtGreen) / 4.0);
            }
            //TOP-EDGE
            else if (i == 0 && (j > 0 && j < (width - 1)))
            {
                averageRed = round((imagecopy[i][j + 1].rgbtRed +
                                    imagecopy[i + 1][j + 1].rgbtRed + imagecopy[i + 1][j].rgbtRed + imagecopy[i + 1][j - 1].rgbtRed
                                    + imagecopy[i][j - 1].rgbtRed + imagecopy[i][j].rgbtRed) / 6.0);

                averageBlue = round((imagecopy[i][j + 1].rgbtBlue +
                                     imagecopy[i + 1][j + 1].rgbtBlue + imagecopy[i + 1][j].rgbtBlue + imagecopy[i + 1][j - 1].rgbtBlue
                                     + imagecopy[i][j - 1].rgbtBlue + imagecopy[i][j].rgbtBlue) / 6.0);

                averageGreen = round((imagecopy[i][j + 1].rgbtGreen +
                                      imagecopy[i + 1][j + 1].rgbtGreen + imagecopy[i + 1][j].rgbtGreen + imagecopy[i + 1][j - 1].rgbtGreen
                                      + imagecopy[i][j - 1].rgbtGreen + imagecopy[i][j].rgbtGreen) / 6.0); // you have checked this one
            }
            //TOP-RIGHT-CORNER
            else if (i == 0 && j == (width - 1))
            {
                averageRed = round((imagecopy[i][j - 1].rgbtRed +
                                    imagecopy[i + 1][j].rgbtRed + imagecopy[i + 1][j - 1].rgbtRed
                                    + imagecopy[i][j].rgbtRed) / 4.0);

                averageBlue = round((imagecopy[i][j - 1].rgbtBlue +
                                     imagecopy[i + 1][j].rgbtBlue + imagecopy[i + 1][j - 1].rgbtBlue
                                     + imagecopy[i][j].rgbtBlue) / 4.0);

                averageGreen = round((imagecopy[i][j - 1].rgbtGreen +
                                      imagecopy[i + 1][j].rgbtGreen + imagecopy[i + 1][j - 1].rgbtGreen
                                      + imagecopy[i][j].rgbtGreen) / 4.0);
            }
            //RIGHT-EDGE
            else if ((i > 0 && i < (height - 1)) && j == (width - 1))
            {
                averageRed = round((imagecopy[i + 1][j].rgbtRed +
                                    imagecopy[i + 1][j - 1].rgbtRed + imagecopy[i][j - 1].rgbtRed + imagecopy[i - 1][j - 1].rgbtRed
                                    + imagecopy[i - 1][j].rgbtRed + imagecopy[i][j].rgbtRed) / 6.0);

                averageBlue = round((imagecopy[i + 1][j].rgbtBlue +
                                     imagecopy[i + 1][j - 1].rgbtBlue + imagecopy[i][j - 1].rgbtBlue + imagecopy[i - 1][j - 1].rgbtBlue
                                     + imagecopy[i - 1][j].rgbtBlue + imagecopy[i][j].rgbtBlue) / 6.0);

                averageGreen = round((imagecopy[i + 1][j].rgbtGreen +
                                      imagecopy[i + 1][j - 1].rgbtGreen + imagecopy[i][j - 1].rgbtGreen + imagecopy[i - 1][j - 1].rgbtGreen
                                      + imagecopy[i - 1][j].rgbtGreen + imagecopy[i][j].rgbtGreen) / 6.0);
            }
            //BOTTOM-RIGHT-CORNER
            else if (i == (height - 1) && j == (width - 1))
            {
                averageRed = round((imagecopy[i][j - 1].rgbtRed +
                                    imagecopy[i - 1][j - 1].rgbtRed + imagecopy[i - 1][j].rgbtRed
                                    + imagecopy[i][j].rgbtRed) / 4.0);

                averageBlue = round((imagecopy[i][j - 1].rgbtBlue +
                                     imagecopy[i - 1][j - 1].rgbtBlue + imagecopy[i - 1][j].rgbtBlue
                                     + imagecopy[i][j].rgbtBlue) / 4.0);

                averageGreen = round((imagecopy[i][j - 1].rgbtGreen +
                                      imagecopy[i - 1][j - 1].rgbtGreen + imagecopy[i - 1][j].rgbtGreen
                                      + imagecopy[i][j].rgbtGreen) / 4.0);
            }
            //BOTTOM-EDGE
            else if (i == (height - 1) && (j > 0 && j < (width - 1)))
            {
                averageRed = round((imagecopy[i][j + 1].rgbtRed +
                                    imagecopy[i - 1][j + 1].rgbtRed + imagecopy[i - 1][j].rgbtRed + imagecopy[i - 1][j - 1].rgbtRed
                                    + imagecopy[i][j - 1].rgbtRed + imagecopy[i][j].rgbtRed) / 6.0);

                averageBlue = round((imagecopy[i][j + 1].rgbtBlue +
                                     imagecopy[i - 1][j + 1].rgbtBlue + imagecopy[i - 1][j].rgbtBlue + imagecopy[i - 1][j - 1].rgbtBlue
                                     + imagecopy[i][j - 1].rgbtBlue + imagecopy[i][j].rgbtBlue) / 6.0);

                averageGreen = round((imagecopy[i][j + 1].rgbtGreen +
                                      imagecopy[i - 1][j + 1].rgbtGreen + imagecopy[i - 1][j].rgbtGreen + imagecopy[i - 1][j - 1].rgbtGreen
                                      + imagecopy[i][j - 1].rgbtGreen + imagecopy[i][j].rgbtGreen) / 6.0);
            }
            //BOTTOM-LEFT-CORNER
            else if (i == (height - 1) && j == 0)
            {
                averageRed = round((imagecopy[i][j + 1].rgbtRed +
                                    imagecopy[i - 1][j + 1].rgbtRed + imagecopy[i - 1][j].rgbtRed
                                    + imagecopy[i][j].rgbtRed) / 4.0);

                averageBlue = round((imagecopy[i][j + 1].rgbtBlue +
                                     imagecopy[i - 1][j + 1].rgbtBlue + imagecopy[i - 1][j].rgbtBlue
                                     + imagecopy[i][j].rgbtBlue) / 4.0);

                averageGreen = round((imagecopy[i][j + 1].rgbtGreen +
                                      imagecopy[i - 1][j + 1].rgbtGreen + imagecopy[i - 1][j].rgbtGreen
                                      + imagecopy[i][j].rgbtGreen) / 4.0);
            }
            //LEFT-EDGE
            else if (j == 0 && (i > 0 && i < (height - 1)))
            {
                averageRed = round((imagecopy[i + 1][j].rgbtRed +
                                    imagecopy[i + 1][j + 1].rgbtRed + imagecopy[i][j + 1].rgbtRed + imagecopy[i - 1][j + 1].rgbtRed
                                    + imagecopy[i - 1][j].rgbtRed + imagecopy[i][j].rgbtRed) / 6.0);

                averageBlue = round((imagecopy[i + 1][j].rgbtBlue +
                                     imagecopy[i + 1][j + 1].rgbtBlue + imagecopy[i][j + 1].rgbtBlue + imagecopy[i - 1][j + 1].rgbtBlue
                                     + imagecopy[i - 1][j].rgbtBlue + imagecopy[i][j].rgbtBlue) / 6.0);

                averageGreen = round((imagecopy[i + 1][j].rgbtGreen +
                                      imagecopy[i + 1][j + 1].rgbtGreen + imagecopy[i][j + 1].rgbtGreen + imagecopy[i - 1][j + 1].rgbtGreen
                                      + imagecopy[i - 1][j].rgbtGreen + imagecopy[i][j].rgbtGreen) / 6.0);
            }
            //MIDDLE-PIXEL
            else
            {
                averageRed = round((imagecopy[i - 1][j - 1].rgbtRed +
                                    imagecopy[i][j - 1].rgbtRed + imagecopy[i + 1][j - 1].rgbtRed + imagecopy[i + 1][j].rgbtRed
                                    + imagecopy[i + 1][j + 1].rgbtRed + imagecopy[i][j + 1].rgbtRed + imagecopy[i - 1][j + 1].rgbtRed
                                    + imagecopy[i - 1][j].rgbtRed + imagecopy[i][j].rgbtRed) / 9.0);

                averageBlue = round((imagecopy[i - 1][j - 1].rgbtBlue +
                                     imagecopy[i][j - 1].rgbtBlue + imagecopy[i + 1][j - 1].rgbtBlue + imagecopy[i + 1][j].rgbtBlue
                                     + imagecopy[i + 1][j + 1].rgbtBlue + imagecopy[i][j + 1].rgbtBlue + imagecopy[i - 1][j + 1].rgbtBlue
                                     + imagecopy[i - 1][j].rgbtBlue + imagecopy[i][j].rgbtBlue) / 9.0);

                averageGreen = round((imagecopy[i - 1][j - 1].rgbtGreen +
                                      imagecopy[i][j - 1].rgbtGreen + imagecopy[i + 1][j - 1].rgbtGreen + imagecopy[i + 1][j].rgbtGreen
                                      + imagecopy[i + 1][j + 1].rgbtGreen + imagecopy[i][j + 1].rgbtGreen + imagecopy[i - 1][j + 1].rgbtGreen
                                      + imagecopy[i - 1][j].rgbtGreen + imagecopy[i][j].rgbtGreen) / 9.0);
            }
            //having this declaration here saved many lines of code rather than having it in each nested if statement
            image[i][j].rgbtRed = averageRed;
            image[i][j].rgbtBlue = averageBlue;
            image[i][j].rgbtGreen = averageGreen;
        }
    }
    //remembering to free colloc'd memory
    free(imagecopy);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //declaring a space in the memory heap the same size as image
    RGBTRIPLE(*imagecopy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    //copying  image into the new table
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imagecopy[i][j] = image[i][j];
        }
    }
    //starting the process of going through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int RedGx;
            int RedGy;
            int BlueGx;
            int BlueGy;
            int GreenGx;
            int GreenGy;

            //TOP-LEFT-CORNER
            if (i == 0 && j == 0)
            {
                //two pixels per row. They go centre, centre-right, bottom-right,
                //bottom-centre, bottom-left, left-centre, top-right, top-centre,
                //top-right where applicable
                RedGx = round((imagecopy[i][j].rgbtRed * 0.0) + (imagecopy[i][j + 1].rgbtRed * 2.0)
                              + (imagecopy[i + 1][j + 1].rgbtRed * 1) + (imagecopy[i + 1][j].rgbtRed * 0));
                RedGy = round((imagecopy[i][j + 1].rgbtRed * 0.0) + (imagecopy[i + 1][j].rgbtRed * 2.0)
                              + (imagecopy[i + 1][j + 1].rgbtRed * 1.0) + (imagecopy[i][j].rgbtRed * 0.0));

                BlueGx = round((imagecopy[i][j + 1].rgbtBlue * 2.0) + (imagecopy[i + 1][j].rgbtBlue * 0.0)
                               + (imagecopy[i + 1][j + 1].rgbtBlue * 1.0) + (imagecopy[i][j].rgbtBlue * 0.0));
                BlueGy = round((imagecopy[i][j + 1].rgbtBlue * 0.0) + (imagecopy[i + 1][j].rgbtBlue * 2.0)
                               + (imagecopy[i + 1][j + 1].rgbtBlue * 1.0) + (imagecopy[i][j].rgbtBlue * 0.0));

                GreenGx = round((imagecopy[i][j + 1].rgbtGreen * 2.0) + (imagecopy[i + 1][j].rgbtGreen * 0.0)
                                + (imagecopy[i + 1][j + 1].rgbtGreen * 1.0) + (imagecopy[i][j].rgbtGreen * 0.0));
                GreenGy = round((imagecopy[i][j + 1].rgbtGreen * 0.0) + (imagecopy[i + 1][j].rgbtGreen * 2.0)
                                + (imagecopy[i + 1][j + 1].rgbtGreen * 1.0) + (imagecopy[i][j].rgbtGreen * 0.0));
            }
            //TOP-EDGE
            else if (i == 0 && (j > 0 && j < (width - 1)))
            {
                RedGx = round((imagecopy[i][j].rgbtRed * 0.0) + (imagecopy[i][j + 1].rgbtRed * 2.0)
                              + (imagecopy[i + 1][j + 1].rgbtRed * 1) + (imagecopy[i + 1][j].rgbtRed * 0)
                              + (imagecopy[i + 1][j - 1].rgbtRed * -1.0) + (imagecopy[i][j - 1].rgbtRed * -2.0));
                RedGy = round((imagecopy[i][j].rgbtRed * 0.0) + (imagecopy[i][j + 1].rgbtRed * 0.0)
                              + (imagecopy[i + 1][j + 1].rgbtRed * 1) + (imagecopy[i + 1][j].rgbtRed * 2.0)
                              + (imagecopy[i + 1][j - 1].rgbtRed * 1.0) + (imagecopy[i][j - 1].rgbtRed * 0.0));

                BlueGx = round((imagecopy[i][j].rgbtBlue * 0.0) + (imagecopy[i][j + 1].rgbtBlue * 2.0)
                               + (imagecopy[i + 1][j + 1].rgbtBlue * 1) + (imagecopy[i + 1][j].rgbtBlue * 0)
                               + (imagecopy[i + 1][j - 1].rgbtBlue * -1.0) + (imagecopy[i][j - 1].rgbtBlue * -2.0));
                BlueGy = round((imagecopy[i][j].rgbtBlue * 0.0) + (imagecopy[i][j + 1].rgbtBlue * 0.0)
                               + (imagecopy[i + 1][j + 1].rgbtBlue * 1) + (imagecopy[i + 1][j].rgbtBlue * 2.0)
                               + (imagecopy[i + 1][j - 1].rgbtBlue * 1.0) + (imagecopy[i][j - 1].rgbtBlue * 0.0));


                GreenGx = round((imagecopy[i][j].rgbtGreen * 0.0) + (imagecopy[i][j + 1].rgbtGreen * 2.0)
                                + (imagecopy[i + 1][j + 1].rgbtGreen * 1) + (imagecopy[i + 1][j].rgbtGreen * 0)
                                + (imagecopy[i + 1][j - 1].rgbtGreen * -1.0) + (imagecopy[i][j - 1].rgbtGreen * -2.0));
                GreenGy = round((imagecopy[i][j].rgbtGreen * 0.0) + (imagecopy[i][j + 1].rgbtGreen * 0.0)
                                + (imagecopy[i + 1][j + 1].rgbtGreen * 1) + (imagecopy[i + 1][j].rgbtGreen * 2.0)
                                + (imagecopy[i + 1][j - 1].rgbtGreen * 1.0) + (imagecopy[i][j - 1].rgbtGreen * 0.0));
            }
            //TOP-RIGHT-CORNER
            else if (i == 0 && j == (width - 1))
            {
                RedGx = round((imagecopy[i][j].rgbtRed * 0.0) + (imagecopy[i + 1][j].rgbtRed * 0.0)
                              + (imagecopy[i + 1][j - 1].rgbtRed * -1.0) + (imagecopy[i][j - 1].rgbtRed * -2.0));
                RedGy = round((imagecopy[i][j].rgbtRed * 0.0) + (imagecopy[i + 1][j].rgbtRed * 2.0)
                              + (imagecopy[i + 1][j - 1].rgbtRed * 1.0) + (imagecopy[i][j - 1].rgbtRed * 0.0));

                BlueGx = round((imagecopy[i][j].rgbtBlue * 0.0) + (imagecopy[i + 1][j].rgbtBlue * 0.0)
                               + (imagecopy[i + 1][j - 1].rgbtBlue * -1.0) + (imagecopy[i][j - 1].rgbtBlue * -2.0));
                BlueGy = round((imagecopy[i][j].rgbtBlue * 0.0) + (imagecopy[i + 1][j].rgbtBlue * 2.0)
                               + (imagecopy[i + 1][j - 1].rgbtBlue * 1.0) + (imagecopy[i][j - 1].rgbtBlue * 0.0));

                GreenGx = round((imagecopy[i][j].rgbtGreen * 0.0) + (imagecopy[i + 1][j].rgbtGreen * 0.0)
                                + (imagecopy[i + 1][j - 1].rgbtGreen * -1.0) + (imagecopy[i][j - 1].rgbtGreen * -2.0));
                GreenGy = round((imagecopy[i][j].rgbtGreen * 0.0) + (imagecopy[i + 1][j].rgbtGreen * 2.0)
                                + (imagecopy[i + 1][j - 1].rgbtGreen * 1.0) + (imagecopy[i][j - 1].rgbtGreen * 0.0));
            }
            //RIGHT-EDGE
            else if ((i > 0 && i < (height - 1)) && j == (width - 1))
            {
                RedGx = round((imagecopy[i][j].rgbtRed * 0.0) + (imagecopy[i + 1][j].rgbtRed * 0.0)
                              + (imagecopy[i + 1][j - 1].rgbtRed * -1.0) + (imagecopy[i][j - 1].rgbtRed * -2.0)
                              + (imagecopy[i - 1][j - 1].rgbtRed * -1.0) + (imagecopy[i - 1][j].rgbtRed * 0.0));
                RedGy = round((imagecopy[i][j].rgbtRed * 0.0) + (imagecopy[i + 1][j].rgbtRed * 2.0)
                              + (imagecopy[i + 1][j - 1].rgbtRed * 1.0) + (imagecopy[i][j - 1].rgbtRed * 0.0)
                              + (imagecopy[i - 1][j - 1].rgbtRed * -1.0) + (imagecopy[i - 1][j].rgbtRed * -2.0));

                BlueGx = round((imagecopy[i][j].rgbtBlue * 0.0) + (imagecopy[i + 1][j].rgbtBlue * 0.0)
                               + (imagecopy[i + 1][j - 1].rgbtBlue * -1.0) + (imagecopy[i][j - 1].rgbtBlue * -2.0)
                               + (imagecopy[i - 1][j - 1].rgbtBlue * -1.0) + (imagecopy[i - 1][j].rgbtBlue * 0.0));
                BlueGy = round((imagecopy[i][j].rgbtBlue * 0.0) + (imagecopy[i + 1][j].rgbtBlue * 2.0)
                               + (imagecopy[i + 1][j - 1].rgbtBlue * 1.0) + (imagecopy[i][j - 1].rgbtBlue * 0.0)
                               + (imagecopy[i - 1][j - 1].rgbtBlue * -1.0) + (imagecopy[i - 1][j].rgbtBlue * -2.0));

                GreenGx = round((imagecopy[i][j].rgbtGreen * 0.0) + (imagecopy[i + 1][j].rgbtGreen * 0.0)
                                + (imagecopy[i + 1][j - 1].rgbtGreen * -1.0) + (imagecopy[i][j - 1].rgbtGreen * -2.0)
                                + (imagecopy[i - 1][j - 1].rgbtGreen * -1.0) + (imagecopy[i - 1][j].rgbtGreen * 0.0));
                GreenGy = round((imagecopy[i][j].rgbtGreen * 0.0) + (imagecopy[i + 1][j].rgbtGreen * 2.0)
                                + (imagecopy[i + 1][j - 1].rgbtGreen * 1.0) + (imagecopy[i][j - 1].rgbtGreen * 0.0)
                                + (imagecopy[i - 1][j - 1].rgbtGreen * -1.0) + (imagecopy[i - 1][j].rgbtGreen * -2.0));
            }
            //BOTTOM-RIGHT-CORNER
            else if (i == (height - 1) && j == (width - 1))
            {
                RedGx = round((imagecopy[i][j].rgbtRed * 0.0) + (imagecopy[i][j - 1].rgbtRed * -2.0)
                              + (imagecopy[i - 1][j - 1].rgbtRed * -1.0) + (imagecopy[i - 1][j].rgbtRed * 0.0));
                RedGy = round((imagecopy[i][j].rgbtRed * 0.0) + (imagecopy[i][j - 1].rgbtRed * 0.0)
                              + (imagecopy[i - 1][j - 1].rgbtRed * -1.0) + (imagecopy[i - 1][j].rgbtRed * -2.0));

                BlueGx = round((imagecopy[i][j].rgbtBlue * 0.0) + (imagecopy[i][j - 1].rgbtBlue * -2.0)
                               + (imagecopy[i - 1][j - 1].rgbtBlue * -1.0) + (imagecopy[i - 1][j].rgbtBlue * 0.0));
                BlueGy = round((imagecopy[i][j].rgbtBlue * 0.0) + (imagecopy[i][j - 1].rgbtBlue * 0.0)
                               + (imagecopy[i - 1][j - 1].rgbtBlue * -1.0) + (imagecopy[i - 1][j].rgbtBlue * -2.0));

                GreenGx = round((imagecopy[i][j].rgbtGreen * 0.0) + (imagecopy[i][j - 1].rgbtGreen * -2.0)
                                + (imagecopy[i - 1][j - 1].rgbtGreen * -1.0) + (imagecopy[i - 1][j].rgbtGreen * 0.0));
                GreenGy = round((imagecopy[i][j].rgbtGreen * 0.0) + (imagecopy[i][j - 1].rgbtGreen * 0.0)
                                + (imagecopy[i - 1][j - 1].rgbtGreen * -1.0) + (imagecopy[i - 1][j].rgbtGreen * -2.0));
            }
            //BOTTOM-EDGE
            else if (i == (height - 1) && (j > 0 && j < (width - 1)))
            {
                RedGx = round((imagecopy[i][j].rgbtRed * 0.0) + (imagecopy[i][j + 1].rgbtRed * 2.0)
                              + (imagecopy[i][j - 1].rgbtRed * -2.0) + (imagecopy[i - 1][j - 1].rgbtRed * -1.0)
                              + (imagecopy[i - 1][j].rgbtRed * 0.0) + (imagecopy[i - 1][j + 1].rgbtRed * 1.0));
                RedGy = round((imagecopy[i][j].rgbtRed * 0.0) + (imagecopy[i][j + 1].rgbtRed * 0.0)
                              + (imagecopy[i][j - 1].rgbtRed * 0.0) + (imagecopy[i - 1][j - 1].rgbtRed * -1.0)
                              + (imagecopy[i - 1][j].rgbtRed * -2.0) + (imagecopy[i - 1][j + 1].rgbtRed * -1.0));

                BlueGx = round((imagecopy[i][j].rgbtBlue * 0.0) + (imagecopy[i][j + 1].rgbtBlue * 2.0)
                               + (imagecopy[i][j - 1].rgbtBlue * -2.0) + (imagecopy[i - 1][j - 1].rgbtBlue * -1.0)
                               + (imagecopy[i - 1][j].rgbtBlue * 0.0) + (imagecopy[i - 1][j + 1].rgbtBlue * 1.0));
                BlueGy = round((imagecopy[i][j].rgbtBlue * 0.0) + (imagecopy[i][j + 1].rgbtBlue * 0.0)
                               + (imagecopy[i][j - 1].rgbtBlue * 0.0) + (imagecopy[i - 1][j - 1].rgbtBlue * -1.0)
                               + (imagecopy[i - 1][j].rgbtBlue * -2.0) + (imagecopy[i - 1][j + 1].rgbtBlue * -1.0));

                GreenGx = round((imagecopy[i][j].rgbtGreen * 0.0) + (imagecopy[i][j + 1].rgbtGreen * 2.0)
                                + (imagecopy[i][j - 1].rgbtGreen * -2.0) + (imagecopy[i - 1][j - 1].rgbtGreen * -1.0)
                                + (imagecopy[i - 1][j].rgbtGreen * 0.0) + (imagecopy[i - 1][j + 1].rgbtGreen * 1.0));
                GreenGy = round((imagecopy[i][j].rgbtGreen * 0.0) + (imagecopy[i][j + 1].rgbtGreen * 0.0)
                                + (imagecopy[i][j - 1].rgbtGreen * 0.0) + (imagecopy[i - 1][j - 1].rgbtGreen * -1.0)
                                + (imagecopy[i - 1][j].rgbtGreen * -2.0) + (imagecopy[i - 1][j + 1].rgbtGreen * -1.0));
            }
            //BOTTOM-LEFT-CORNER
            else if (i == (height - 1) && j == 0)
            {
                RedGx = round((imagecopy[i][j].rgbtRed * 0.0) + (imagecopy[i][j + 1].rgbtRed * 2.0)
                              + (imagecopy[i - 1][j].rgbtRed * 0.0) + (imagecopy[i - 1][j + 1].rgbtRed * 1.0));
                RedGy = round((imagecopy[i][j].rgbtRed * 0.0) + (imagecopy[i][j + 1].rgbtRed * 0.0)
                              + (imagecopy[i - 1][j].rgbtRed * -2.0) + (imagecopy[i - 1][j + 1].rgbtRed * -1.0));

                BlueGx = round((imagecopy[i][j].rgbtBlue * 0.0) + (imagecopy[i][j + 1].rgbtBlue * 2.0)
                               + (imagecopy[i - 1][j].rgbtBlue * 0.0) + (imagecopy[i - 1][j + 1].rgbtBlue * 1.0));
                BlueGy = round((imagecopy[i][j].rgbtBlue * 0.0) + (imagecopy[i][j + 1].rgbtBlue * 0.0)
                               + (imagecopy[i - 1][j].rgbtBlue * -2.0) + (imagecopy[i - 1][j + 1].rgbtBlue * -1.0));

                GreenGx = round((imagecopy[i][j].rgbtGreen * 0.0) + (imagecopy[i][j + 1].rgbtGreen * 2.0)
                                + (imagecopy[i - 1][j].rgbtGreen * 0.0) + (imagecopy[i - 1][j + 1].rgbtGreen * 1.0));
                GreenGy = round((imagecopy[i][j].rgbtGreen * 0.0) + (imagecopy[i][j + 1].rgbtGreen * 0.0)
                                + (imagecopy[i - 1][j].rgbtGreen * -2.0) + (imagecopy[i - 1][j + 1].rgbtGreen * -1.0));
            }
            //LEFT-EDGE
            else if (j == 0 && (i > 0 && i < (height - 1)))
            {
                RedGx = round((imagecopy[i][j].rgbtRed * 0.0) + (imagecopy[i][j + 1].rgbtRed * 2.0)
                              + (imagecopy[i + 1][j + 1].rgbtRed * 1.0) + (imagecopy[i + 1][j].rgbtRed * 0.0)
                              + (imagecopy[i - 1][j].rgbtRed * 0.0) + (imagecopy[i - 1][j + 1].rgbtRed * 1.0));
                RedGy = round((imagecopy[i][j].rgbtRed * 0.0) + (imagecopy[i][j + 1].rgbtRed * 0.0)
                              + (imagecopy[i + 1][j + 1].rgbtRed * 1.0) + (imagecopy[i + 1][j].rgbtRed * 2.0)
                              + (imagecopy[i - 1][j].rgbtRed * -2.0) + (imagecopy[i - 1][j + 1].rgbtRed * -1.0));

                BlueGx = round((imagecopy[i][j].rgbtBlue * 0.0) + (imagecopy[i][j + 1].rgbtBlue * 2.0)
                               + (imagecopy[i + 1][j + 1].rgbtBlue * 1.0) + (imagecopy[i + 1][j].rgbtBlue * 0.0)
                               + (imagecopy[i - 1][j].rgbtBlue * 0.0) + (imagecopy[i - 1][j + 1].rgbtBlue * 1.0));
                BlueGy = round((imagecopy[i][j].rgbtBlue * 0.0) + (imagecopy[i][j + 1].rgbtBlue * 0.0)
                               + (imagecopy[i + 1][j + 1].rgbtBlue * 1.0) + (imagecopy[i + 1][j].rgbtBlue * 2.0)
                               + (imagecopy[i - 1][j].rgbtBlue * -2.0) + (imagecopy[i - 1][j + 1].rgbtBlue * -1.0));

                GreenGx = round((imagecopy[i][j].rgbtGreen * 0.0) + (imagecopy[i][j + 1].rgbtGreen * 2.0)
                                + (imagecopy[i + 1][j + 1].rgbtGreen * 1.0) + (imagecopy[i + 1][j].rgbtGreen * 0.0)
                                + (imagecopy[i - 1][j].rgbtGreen * 0.0) + (imagecopy[i - 1][j + 1].rgbtGreen * 1.0));
                GreenGy = round((imagecopy[i][j].rgbtGreen * 0.0) + (imagecopy[i][j + 1].rgbtGreen * 0.0)
                                + (imagecopy[i + 1][j + 1].rgbtGreen * 1.0) + (imagecopy[i + 1][j].rgbtGreen * 2.0)
                                + (imagecopy[i - 1][j].rgbtGreen * -2.0) + (imagecopy[i - 1][j + 1].rgbtGreen * -1.0));
            }
            //MIDDLE-PIXEL
            else
            {
                RedGx = round((imagecopy[i][j].rgbtRed * 0.0) + (imagecopy[i][j + 1].rgbtRed * 2.0)
                              + (imagecopy[i + 1][j + 1].rgbtRed * 1.0) + (imagecopy[i + 1][j].rgbtRed * 0.0)
                              + (imagecopy[i + 1][j - 1].rgbtRed * -1.0) + (imagecopy[i][j - 1].rgbtRed * -2.0)
                              + (imagecopy[i - 1][j - 1].rgbtRed * -1.0) + (imagecopy[i - 1][j].rgbtRed * 0.0)
                              + (imagecopy[i - 1][j + 1].rgbtRed * 1.0));
                RedGy = round((imagecopy[i][j].rgbtRed * 0.0) + (imagecopy[i][j + 1].rgbtRed * 0.0)
                              + (imagecopy[i + 1][j + 1].rgbtRed * 1.0) + (imagecopy[i + 1][j].rgbtRed * 2.0)
                              + (imagecopy[i + 1][j - 1].rgbtRed * 1.0) + (imagecopy[i][j - 1].rgbtRed * 0.0)
                              + (imagecopy[i - 1][j - 1].rgbtRed * -1.0) + (imagecopy[i - 1][j].rgbtRed * -2.0)
                              + (imagecopy[i - 1][j + 1].rgbtRed * -1.0));

                BlueGx = round((imagecopy[i][j].rgbtBlue * 0.0) + (imagecopy[i][j + 1].rgbtBlue * 2.0)
                               + (imagecopy[i + 1][j + 1].rgbtBlue * 1.0) + (imagecopy[i + 1][j].rgbtBlue * 0.0)
                               + (imagecopy[i + 1][j - 1].rgbtBlue * -1.0) + (imagecopy[i][j - 1].rgbtBlue * -2.0)
                               + (imagecopy[i - 1][j - 1].rgbtBlue * -1.0) + (imagecopy[i - 1][j].rgbtBlue * 0.0)
                               + (imagecopy[i - 1][j + 1].rgbtBlue * 1.0));
                BlueGy = round((imagecopy[i][j].rgbtBlue * 0.0) + (imagecopy[i][j + 1].rgbtBlue * 0.0)
                               + (imagecopy[i + 1][j + 1].rgbtBlue * 1.0) + (imagecopy[i + 1][j].rgbtBlue * 2.0)
                               + (imagecopy[i + 1][j - 1].rgbtBlue * 1.0) + (imagecopy[i][j - 1].rgbtBlue * 0.0)
                               + (imagecopy[i - 1][j - 1].rgbtBlue * -1.0) + (imagecopy[i - 1][j].rgbtBlue * -2.0)
                               + (imagecopy[i - 1][j + 1].rgbtBlue * -1.0));

                GreenGx = round((imagecopy[i][j].rgbtGreen * 0.0) + (imagecopy[i][j + 1].rgbtGreen * 2.0)
                                + (imagecopy[i + 1][j + 1].rgbtGreen * 1.0) + (imagecopy[i + 1][j].rgbtGreen * 0.0)
                                + (imagecopy[i + 1][j - 1].rgbtGreen * -1.0) + (imagecopy[i][j - 1].rgbtGreen * -2.0)
                                + (imagecopy[i - 1][j - 1].rgbtGreen * -1.0) + (imagecopy[i - 1][j].rgbtGreen * 0.0)
                                + (imagecopy[i - 1][j + 1].rgbtGreen * 1.0));
                GreenGy = round((imagecopy[i][j].rgbtGreen * 0.0) + (imagecopy[i][j + 1].rgbtGreen * 0.0)
                                + (imagecopy[i + 1][j + 1].rgbtGreen * 1.0) + (imagecopy[i + 1][j].rgbtGreen * 2.0)
                                + (imagecopy[i + 1][j - 1].rgbtGreen * 1.0) + (imagecopy[i][j - 1].rgbtGreen * 0.0)
                                + (imagecopy[i - 1][j - 1].rgbtGreen * -1.0) + (imagecopy[i - 1][j].rgbtGreen * -2.0)
                                + (imagecopy[i - 1][j + 1].rgbtGreen * -1.0));
            }
            //round function used as throughout the program to ensure proper rounding into ints
            int finalRed = round(sqrt(pow(RedGx, 2) + pow(RedGy, 2)));
            int finalBlue = round(sqrt(pow(BlueGx, 2) + pow(BlueGy, 2)));
            int finalGreen = round(sqrt(pow(GreenGx, 2) + pow(GreenGy, 2)));
            //capping the max colour at 255
            if (finalRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = finalRed;
            }

            if (finalBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = finalBlue;
            }

            if (finalGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = finalGreen;
            }
        }
    }
    //remembering to free colloc'd memory
    free(imagecopy);
    return;
}