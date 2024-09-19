#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale - black-white
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // all red, green, blue are set to 0x00 => black
    // all red, green, blue are set to 0xff => white
    // grayscale => all red, green, blue are the same value
    // gia tri red, green, blue cua anh goc la high thi gia tri moi cua no cung la high va nguoc lai
    // to ensure each pixel of the new image still has the same general brightness or darkness as the old image,
    // you can take the average of the red, green, and blue values to determine what shade of grey to make the new pixel.
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    /* - An image can be converted to sepia by taking each pixel, and computing new red, green, and blue values based on the original values of the three.
       - For each pixel, the sepia color values should be calculated based on the original color values per the below.

            sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
            sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
            sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
     */
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            image[i][j].rgbtRed = (sepiaRed <= 255) ? sepiaRed : 255;
            image[i][j].rgbtGreen = (sepiaGreen <= 255) ? sepiaGreen : 255;
            image[i][j].rgbtBlue = (sepiaBlue <= 255) ? sepiaBlue : 255;
        }
    }
    return;
}

// Reflect image horizontally
void swap(RGBTRIPLE *a, RGBTRIPLE *b) {
    RGBTRIPLE tmp = *a;
    *a = *b;
    *b = tmp;
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    /*
    - Any pixels on the left side of the image should end up on the right, and vice versa.
    - All of the original pixels of the original image will still be present in the reflected image, 
    it’s just that those pixels may have been rearranged to be in a different place in the image.
    */
   for(int i = 0; i < height; i++) {
        for(int j = 0; j < width / 2; j++) {
            swap(&image[i][j], &image[i][width - j - 1]);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /*
    - use the “box blur,” which works by taking each pixel and, for each color value, 
    giving it a new value by averaging the color values of neighboring pixels.
    - tức là lấy các số lân cận nó để làm giá trị mới cho nó.
    ví dụ:
    1 2  3  4
    5 6  7  8
    8 10 11 12
    thì ở pixel 6 sẽ lấy giá trị mới là trung bình cộng (1 + 2 + 3 + 5 + 6 + 7 + 8 + 10 + 11) / 9
    */
    RGBTRIPLE copy[height][width]; //tránh việc khi có pixel thay đổi giá trị thì sẽ ko ảnh hướng đến các pixel khác
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            copy[i][j] = image[i][j];
        }
    }
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int countRed = 0, countGreen = 0, countBlue = 0;
            for(int x = i-1; x <= i+1; x++) {
                for(int y = j-1; y <= j+1; y++) {
                    if(x >= 0 && x < height && y >= 0 && y < width) {
                        sumRed += copy[x][y].rgbtRed;
                        sumGreen += copy[x][y].rgbtGreen;
                        sumBlue += copy[x][y].rgbtBlue;
                        countRed++;
                        countGreen++;
                        countBlue++;
                    }
                }
            }
            image[i][j].rgbtRed = round(sumRed * 1.0 / countRed);
            image[i][j].rgbtGreen = round(sumGreen * 1.0 / countGreen);
            image[i][j].rgbtBlue = round(sumBlue * 1.0 / countBlue);
        }
    }
    return;
}
