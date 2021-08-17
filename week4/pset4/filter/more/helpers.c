#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over each RGBTRIPLE in image
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Get pixel rgb value
            RGBTRIPLE p = image[y][x];

            // Calculate average
            int avg = round((p.rgbtBlue + p.rgbtGreen + p.rgbtRed) / 3.0);

            // Update pixel in image array
            image[y][x].rgbtBlue = avg;
            image[y][x].rgbtGreen = avg;
            image[y][x].rgbtRed = avg;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over each RGBTRIPLE in image
    for (int y = 0; y < height; y++)
    {
        // Initialize reversed row array
        RGBTRIPLE reversed[width];

        // Populate row array with image pixels reversed
        for (int x = width - 1; x >= 0; x--)
        {
            int k = width - x - 1;

            reversed[k] = image[y][x];
        }

        // Replace image pixels with reversed pixels
        for (int x = 0; x < width; x++)
        {
            image[y][x] = reversed[x];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialize new image array to hold blurred pixels
    RGBTRIPLE blurred[height][width];

    // Initialize average pixel
    RGBTRIPLE avg;

    // Loop over each RGBTRIPLE in image
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Reset average values for current pixel
            float avgRed = 0.0;
            float avgGreen = 0.0;
            float avgBlue = 0.0;
            int count = 0;

            // Box blur scale
            int scale = 1;

            // Get pixel values surrounding current pixel
            for (int dy = -scale; dy <= scale; dy++)
            {

                for (int dx = -scale; dx <= scale; dx++)
                {
                    // Ignore edge cases
                    if (!(x + dx >= 0 && x + dx < width && y + dy >= 0 && y + dy < height))
                    {
                        continue;
                    }

                    // Get current pixel
                    RGBTRIPLE p = image[y + dy][x + dx];

                    // Add values to averages
                    avgRed += p.rgbtRed;
                    avgGreen += p.rgbtGreen;
                    avgBlue += p.rgbtBlue;

                    // Increment pixel count for average
                    count++;
                }
            }

            // Calculate average
            avg.rgbtRed = round(avgRed / count);
            avg.rgbtGreen = round(avgGreen / count);
            avg.rgbtBlue = round(avgBlue / count);

            // Add blurred pixel to new array
            // NB: can't overwrite original image array yet otherwise new values would feed into next calclation
            blurred[y][x] = avg;
        }
    }

    // Update original image pixels with blurred pixels
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image[y][x] = blurred[y][x];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialize new image array to hold edge pixels
    RGBTRIPLE edges[height][width];

    // Initialize edge pixel
    RGBTRIPLE edge;

    // Sobel kernels
    int gx[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
    int gy[3][3] = { { -1, -2, -1 }, { 0, 0, 0 }, { 1, 2, 1 } };

    // Loop over each RGBTRIPLE in image
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Reset kernel sum values for current pixel
            float gxSum[] = { 0.0, 0.0, 0.0 };
            float gySum[] = { 0.0, 0.0, 0.0 };

            // Get pixel values surrounding current pixel
            for (int dy = -1; dy <= 1; dy++)
            {
                for (int dx = -1; dx <= 1; dx++)
                {
                    // Ignore out of bounds pixels
                    if (!(x + dx >= 0 && x + dx < width && y + dy >= 0 && y + dy < height))
                    {
                        continue;
                    }

                    // Get current pixel
                    RGBTRIPLE p = image[y + dy][x + dx];

                    // Get kernel factors
                    int gxF = gx[dy + 1][dx + 1];
                    int gyF = gy[dy + 1][dx + 1];

                    // Add values to kernel sums
                    gxSum[0] += p.rgbtRed * gxF;
                    gxSum[1] += p.rgbtGreen * gxF;
                    gxSum[2] += p.rgbtBlue * gxF;
                    gySum[0] += p.rgbtRed * gyF;
                    gySum[1] += p.rgbtGreen * gyF;
                    gySum[2] += p.rgbtBlue * gyF;
                }
            }

            // Calculate edge value
            // NB: storing these values in ints rather than RGBTRIPLE edge as RGBTRIPLE byte will overflow if value over 255
            int edgeRed = round(sqrtf(powf(gxSum[0], 2.0) + powf(gySum[0], 2.0)));
            int edgeGreen = round(sqrtf(powf(gxSum[1], 2.0) + powf(gySum[1], 2.0)));
            int edgeBlue = round(sqrtf(powf(gxSum[2], 2.0) + powf(gySum[2], 2.0)));

            // Cap edge values at 255
            if (edgeRed > 255)
            {
                edgeRed = 255;
            }

            if (edgeGreen > 255)
            {
                edgeGreen = 255;
            }

            if (edgeBlue > 255)
            {
                edgeBlue = 255;
            }

            // Set values in edge pixel
            edge.rgbtRed = edgeRed;
            edge.rgbtGreen = edgeGreen;
            edge.rgbtBlue = edgeBlue;

            // Add edge pixel to edges array
            // NB: can't overwrite original image array yet otherwise new values would feed into next calclation
            edges[y][x] = edge;
        }
    }

    // Update original image pixels with edge pixels
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image[y][x] = edges[y][x];
        }
    }

    return;
}
