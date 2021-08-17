// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    uint8_t *header = malloc(sizeof(uint8_t) * HEADER_SIZE);
    fread(header, sizeof(uint8_t), HEADER_SIZE, input); // read bytes from input to variable
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output); // write bytes from variable to output

    // Read samples from input file and write updated data to output file
    int16_t *sample = malloc(sizeof(int16_t));
    // fread returns number of bytes read, expect same as input, i.e. while not EOF/error
    while (fread(sample, sizeof(int16_t), 1, input) == 1)
    {
        *sample *= factor; // deference value in sample pointer and scale by factor
        fwrite(sample, sizeof(int16_t), 1, output); // write scaled sample to output file
    }


    // Close files
    fclose(input);
    fclose(output);

    // Free dynamic memory
    free(header);
    free(sample);
}
