#include "helpers.h"
#include <math.h>

RGBTRIPLE calc_sepia(RGBTRIPLE rgb);

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over each RGBTRIPLE in image
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Get pixel rgb value
            RGBTRIPLE p = image[y][x];

            // Calculate sepia value
            RGBTRIPLE rgbSepia = calc_sepia(p);

            // Update pixel in image array
            image[y][x] = rgbSepia;
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

    // Initialize average pixel and neighbor counter
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


// Apply sepia filter to individual pixel
RGBTRIPLE calc_sepia(RGBTRIPLE p)
{
    // Calculate new rgb values
    int sepiaRed = round(.393 * p.rgbtRed + .769 * p.rgbtGreen + .189 * p.rgbtBlue);
    int sepiaGreen = round(.349 * p.rgbtRed + .686 * p.rgbtGreen + .168 * p.rgbtBlue);
    int sepiaBlue = round(.272 * p.rgbtRed + .534 * p.rgbtGreen + .131 * p.rgbtBlue);

    // Cap sepia values to 255
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

    // Output sepia pixel
    RGBTRIPLE out;
    out.rgbtRed = sepiaRed;
    out.rgbtGreen = sepiaGreen;
    out.rgbtBlue = sepiaBlue;

    return out;
}