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

    /*
    function: fread(buffer, 1, 512, card): có syntax của fread là:
                size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
        ptr (ở đây là buffer) là con trỏ đến nơi sẽ chứa dữ liệu được đọc từ file.
        size là kích thước của mỗi phần tử cần đọc (ở đây là 1, tức là đọc từng byte một).
        count là số lượng phần tử cần đọc (ở đây là 512, tức là đọc 512 byte mỗi lần).
        stream là file mà ta đang đọc (ở đây là card).
    Như vậy, fread(buffer, 1, 512, card) có nghĩa là đọc 512 bytes từ file card vào mảng buffer.

    fread(buffer, 1, 512, card) == 512:
        fread trả về số lượng phần tử đã được đọc từ file (ở đây là số lượng byte).
        Điều kiện == 512 kiểm tra xem fread có thực sự đọc đủ 512 bytes hay không.
        Nếu số bytes đọc được ít hơn 512 (tức là đến cuối file), fread sẽ trả về số lượng byte nhỏ hơn 512, hoặc nếu không đọc được gì (EOF), nó trả về 0.
    Vòng lặp while:
        dùng để tiếp tục đọc từng khối 512 bytes từ file card cho đến khi không còn đủ 512 bytes để đọc (tức là khi file đã hết dữ liệu hoặc gặp lỗi).
        Mỗi lần lặp, 512 bytes từ file sẽ được lưu vào buffer, và nếu điều kiện == 512 là đúng (tức là vẫn đọc đủ 512 bytes), chương trình sẽ tiếp tục xử lý dữ liệu trong buffer (ở đây là kiểm tra xem khối dữ liệu đó có phải là khối bắt đầu của một ảnh JPEG).
    */
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
