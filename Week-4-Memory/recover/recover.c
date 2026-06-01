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
    fread(buffer, SIGNATURE_SIZE, 1, input);

    if (buffer[0] != 0xFF || buffer[1] != 0xD8 || buffer[2] != 0xFF || buffer[3] >> 4 != 0xE)
    {
        fclose(input);
        printf("Unsupported file format.\n");
        return 1;
    }

    fseek(input, 0, SEEK_SET);

    while (fread(buffer, BLOCK_SIZE, 1, input))
    {

    }

    // uint8_t buffer[BLOCK_SIZE];
    // uint8_t byte;
    // while (fread(buffer, BLOCK_SIZE, 1, input) == 1)
    // {

    //     fread(buffer, sizeof(uint8_t), SIGNATURE_SIZE, input);

    //     if (buffer[0] != 0xFF || buffer[1] != 0xD8 || buffer[2] != 0xFF || buffer[3] >> 4 != 0xE)
    //     {
    //         fclose(input);
    //         printf("Unsupported file format.\n");
    //         return 1;
    //     }

    //     char filename[8];
    //     FILE *output = fopen(filename, "wb");
    //     fwrite(buffer, sizeof(uint8_t), SIGNATURE_SIZE, output);
    //     while (fread(&byte, sizeof(uint8_t), BLOCK_SIZE, input))
    //     {
    //         fwrite(&byte, sizeof(uint8_t), BLOCK_SIZE, output);
    //     }
    //     fclose(output);
    //   }

    return 0;
}