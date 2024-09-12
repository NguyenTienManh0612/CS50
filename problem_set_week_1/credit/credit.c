#include <cs50.h>
#include <stdio.h>

/*
AMEX - 15 digits
MASTERCARD - 16 digits
VISA - 13 and 16 digits
*/
long get_card(void);
int check_card(long credit);
int check_card_type(long credit);

int main(void)
{
    // ask credit card number
    long credit = get_card();

    // check valid card
    int checkValidCard = check_card(credit);
    int checkCardType = check_card_type(credit);
    if (checkValidCard % 10 == 0)
    {
        if (checkCardType == 1)
            printf("AMEX\n");
        if (checkCardType == 2)
            printf("MASTERCARD\n");
        if (checkCardType == 3)
            printf("VISA\n");
        if (checkCardType == 0)
            printf("INVALID\n");
    }
    else
        printf("INVALID\n");
}

long get_card(void)
{
    long credit;
    do
    {
        credit = get_long("Number: ");
    }
    while (credit < 0);
    return credit;
}

int check_card(long credit)
{
    int getDigit;
    int MulEvenPosDigit;
    int sumEvenPos = 0;
    int sumOddPos = 0;
    int checkSum;
    int count = 0;
    while (credit > 0)
    {
        getDigit = credit % 10;
        credit /= 10;
        count++;
        if (count % 2 == 0) // check digit ai even position in credit card number
        {
            MulEvenPosDigit = getDigit * 2; // multiply by 2
            if (MulEvenPosDigit >= 10)      // check digit multiplied by 2 > 10
                sumEvenPos += (MulEvenPosDigit % 10) + (MulEvenPosDigit / 10);
            else
                sumEvenPos += MulEvenPosDigit;
        }
        else
            sumOddPos += getDigit;
    }
    checkSum = sumOddPos + sumEvenPos;
    return checkSum;
}

int check_card_type(long credit)
{
    int amex = 1;
    int mastercard = 2;
    int visa = 3;
    int notCard = 0;
    int getDoubleDigit;
    int getVisa;
    int count = 0;
    while (credit > 0)
    {
        if (credit > 10)
        {
            getDoubleDigit = credit % 100;
        }
        getVisa = credit % 10;
        credit /= 10;
        count++;
    }
    if ((count == 15) && (getDoubleDigit == 34 || getDoubleDigit == 37))
        return amex;
    if (count == 13)
        return visa;
    if (count == 16)
    {
        if (getDoubleDigit == 51 || getDoubleDigit == 52 || getDoubleDigit == 53 || getDoubleDigit == 54 || getDoubleDigit == 55)
            return mastercard;
        if (getVisa == 4)
            return visa;
    }
    return notCard;
}