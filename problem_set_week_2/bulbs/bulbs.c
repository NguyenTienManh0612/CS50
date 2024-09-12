#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int byte = 8;

void print_bulb(int bit);
void text2Dec(string text, int arrDec[]);
void dec2Bin(int arrBin[][byte], int arrDec[], int len);

int main(void)
{
    string text = get_string("Message: ");
    int len = strlen(text);
    int arrDec[len];       // store decimal numbers of text
    int arrBin[len][byte]; // store 8-bit binary numbers of each character's decimal numbers
    text2Dec(text, arrDec);
    dec2Bin(arrBin, arrDec, len);
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < 8; j++)
            print_bulb(arrBin[i][j]);
        printf("\n");
    }
}

// Convert text to decimal numbers
void text2Dec(string text, int arrDec[])
{
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalnum(text[i]) || ispunct(text[i]) || isspace(text[i]))
            arrDec[i] = (int) text[i];
    }
}

// Convert decimal numbers to 8-bit binary numbers
void dec2Bin(int arrBin[][byte], int arrDec[], int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = byte - 1; j >= 0; j--)
        {
            arrBin[i][j] = arrDec[i] % 2;
            arrDec[i] /= 2;
        }
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}