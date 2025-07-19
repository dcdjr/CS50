#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover filename.raw\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE buffer[512];

    int num_found_jpegs = 0;

    char filename[8];

    FILE *img = NULL;

    while (fread(&buffer, sizeof(buffer), 1, card) != 0)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {
                fclose(img);
            }

            num_found_jpegs++;
            sprintf(filename, "%03i.jpg", num_found_jpegs - 1);
            img = fopen(filename, "w");
        }

        if (img != NULL)
        {
            fwrite(&buffer, sizeof(buffer), 1, img);
        }
    }
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);
    return 0;
}
