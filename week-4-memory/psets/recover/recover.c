#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // check the correct number of arguments
    if (argc != 2)
    {
        // if the argument is missing, terminate the program with an error message
        printf("Usage: ./%s image\n", argv[0]);
        return 1;
    }
    FILE *card = fopen(argv[1], "r"); // open the input file for reading
    if (card == NULL)
    {
        // if fails to open, terminate the program with an error message
        fclose(card);
        printf("Failed to open %s\n", argv[1]);
        return 1;
    }

    BYTE buffer[512]; // buffer to allocate 512 byte chunks of images
    int imgnum = 0; // number of images
    FILE *img = NULL; // output file
    char *filename = malloc(8 * sizeof(char)); // name of the output files

    while (fread(buffer, sizeof(BYTE), 512, card))
    {
        // if start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", imgnum); // create name of the output file
            img = fopen(filename, "w"); // open the output file for writing
            imgnum++; // increase the naming number
        }
        if (img != NULL)
        {
            // if current image, continue writing
            fwrite(buffer, sizeof(BYTE), 512, img);
        }
    }
    free(filename); // free the memory allocated for storing file name
    fclose(card); // close the input file
    fclose(img); // close the output file

    return 0;
}