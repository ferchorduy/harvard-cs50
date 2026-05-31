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
    uint8_t *header_pointer = malloc(HEADER_SIZE);
    uint8_t byte;
    uint16_t sample;
    if (header_pointer == NULL) return 1;

    // TODO: Copy header from input file to output file
    for (int i = 0; i < HEADER_SIZE; i++)
    {
        fread(&byte, sizeof(uint8_t), 1, input);
        fwrite(&byte, sizeof(uint8_t), 1, output);
    }

    // TODO: Read samples from input file and write updated data to output file
    while (fread(&sample, sizeof(uint16_t), 1, input) != 0)
    {
        sample *= factor;
        fwrite(&sample, sizeof(uint16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
    free(header_pointer);
    header_pointer = NULL;
    return 0;
}
