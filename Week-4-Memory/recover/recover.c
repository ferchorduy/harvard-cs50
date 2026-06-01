#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SIGNATURE_SIZE 4
#define BLOCK_SIZE 512
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];
    int jpeg_count = 0;
    FILE *output = NULL;
    while (fread(buffer, BLOCK_SIZE, 1, input))
    {
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && buffer[3] >> 4 == 0xE)
        {
            if (output != NULL) fclose(output);
            char filename[8];
            sprintf(filename, "%03i.jpg", jpeg_count);
            output = fopen(filename, "wb");
            jpeg_count++;
        }
        if (output != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, output);
        }
    }
    if (output != NULL) fclose(output);
    fclose(input);
    return 0;
}