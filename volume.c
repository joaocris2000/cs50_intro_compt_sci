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

    // TODO: Copy header from input file to output file
    uint8_t *header=malloc(sizeof(uint8_t)*44);
    if (header == NULL)
    {
        printf("Could not get memory.\n");
        return 1;
    }
    fread(header, sizeof(uint8_t), 44, input);
    fwrite(header, sizeof(uint8_t), 44, output);
    free (header);

    // TODO: Read samples from input file and write updated data to output file
    int16_t *sample=malloc(sizeof(int16_t));
    if (sample == NULL)
    {
        printf("Could not get memory.\n");
        return 1;
    }
    while (fread(sample, sizeof(int16_t), 1, input))
    {
        *sample = *sample * factor;
        fwrite(sample, sizeof(int16_t), 1, output);
    }
    free (sample);


    // Close files
    fclose(input);
    fclose(output);
}
