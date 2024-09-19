#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*
    voi anh jpeg, 3 byte dau la 0xff (1111 1111 = 255) / 0xd8 (1101 1000 = 216) / 0xff (1111 1111 = 255)
    byte thu 4 co 4 bit dau la: 1110 hay e
 */
int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open memory card
    FILE *card = fopen(argv[1], "r");
    if(card == NULL) {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // a buffer for a block of data, 521 bytes
    uint8_t buffer[512];

    int fileCounter = 0;
    FILE *img = NULL;
    char fileName[8]; // store name like 000.jpg, 001.jpg

    while(fread(buffer, 1, 512, card) == 512) { // 1 = size int byte of memory into which to read
        // Create JPEGs from the data with 3 first bytes are: 0xff 0xd8 0xff
        // the fourth byte has 4 first bits are 1110 or 0xe0 -> 0xef
        // output these by naming each ###.jpg, where ### is three-digit decimal number from 000 on up.
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {

            if(img != NULL) fclose(img);

            //create a new jpeg file
            sprintf(fileName, "%03d.jpg", fileCounter);
            img = fopen(fileName, "w");
            fileCounter++;
        }

        if(img != NULL)
            fwrite(buffer, 1, 512, img);
    }

    if(img != NULL) fclose(img);
    fclose(card);
}
