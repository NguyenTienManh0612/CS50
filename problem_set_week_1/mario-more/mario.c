#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        printf("Height: ");
        scanf("%i", &height);
    }
    while (height < 1 || height > 8);

    for (int i = 0; i < height; i++)
    {
        // left half-pyramid
        for (int j = i; j < height - 1; j++)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("  ");
        // right half-pyramid
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}