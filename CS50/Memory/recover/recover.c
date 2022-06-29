#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
const int BLOCK_SIZE = 512;


int main(int argc, char *argv[])
{

    //ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover [file name]\n");
        return 1;
    }
    //remeber file name
    char *infile = argv[1];

    //check if can open a file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }




    //defines a new type called BYTE to be uint_8
    typedef uint8_t BYTE;

    //dynamicly obtain a memory for buffer
    BYTE *buffer = malloc(BLOCK_SIZE * (sizeof(BYTE)));

    //tryed to malloc memory for filename, but actualy works witf any number of memory, why???
    char *filename = malloc(8 * sizeof(char));

    //dynamicly obtain a memory for filename ###.jpg\0
    //dynamicly obtain a memory for jpg counter, to count jpg's for nane
    //int *jpg_counter = malloc(3 * sizeof(int));
    int jpg_counter = 0;

    //open new file
    sprintf(filename, "%03i.jpg", jpg_counter);
    FILE *img = fopen(filename, "w");

    //chack if ok
    if (img == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    //read until the end
    //read 512 bytes into buffer
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {

        // check if its JPEG?
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            //if first just write first block
            if (jpg_counter == 0)
            {
                jpg_counter++;
                fwrite(buffer, BLOCK_SIZE, 1, img);
            }

            //if not firs, close last one and start new
            //and write new
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", jpg_counter);
                img = fopen(filename, "w");

                //check if ok
                if (img == NULL)
                {
                    printf("Could not open file.\n");
                    return 1;
                }
                fwrite(buffer, BLOCK_SIZE, 1, img);
                jpg_counter++;
            }
        }
        // if its not firs, bet same img
        else if (jpg_counter > 0)
        {
            fwrite(buffer, BLOCK_SIZE, 1, img);
        }
    }
    //dree memmory
    fclose(img);
    fclose(file);
    free(buffer);
    free(filename);

}