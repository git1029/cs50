#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
typedef uint32_t SIG;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // Get input file name
    char *infile = argv[1];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // Initialize JPEG count
    int count = 0;

    // Initialize outfile name (format: "###.jpg", incl. trailing nul value)
    char *outfile = malloc(sizeof(char) * 8);
    if (outfile == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for outfile name.\n");
        return 1;
    }

    // Initialize outfile pointer
    FILE *outptr = NULL;

    // Initialize block memory
    BYTE *block = malloc(sizeof(BYTE) * 512);
    if (block == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for block.\n");
        return 1;
    }

    // Read 512 B blocks from card until reach EOF
    while (fread(block, sizeof(BYTE) * 512, 1, inptr) == 1)
    {
        // Check for JPEG signature at start of block
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff &&
            block[3] >= 0xe0 && block[3] <= 0xef)
        {
            // Close any open JPEG files
            if (outptr != NULL)
            {
                if (fclose(outptr) != 0)
                {
                    fprintf(stderr, "Could not close %s.\n", outfile);
                    return 2;
                }
            }

            // Update outfile name
            sprintf(outfile, "%03i.jpg", count);

            // Open output file
            outptr = fopen(outfile, "w");
            if (outptr == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", outfile);
                return 3;
            }

            // Increment JPEG count
            count++;
        }

        // Write block(s) to output file
        if (outptr != NULL)
        {
            fwrite(block, sizeof(BYTE) * 512, 1, outptr);
        }
    }

    // Free memory for block
    free(block);

    // Free memory for outfile name
    free(outfile);

    // Close infile
    fclose(inptr);

    // Close outfile
    fclose(outptr);

    return 0;
}