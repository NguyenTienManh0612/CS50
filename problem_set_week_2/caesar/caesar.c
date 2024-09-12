#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    string plaintext;
    if (argc == 2 && only_digits(argv[1]))
    {
        plaintext = get_string("plaintext: ");
        printf("ciphertext: ");
        for (int i = 0, len = strlen(plaintext); i < len; i++)
        {
            printf("%c", rotate(plaintext[i], atoi(argv[1])));
        }
        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    return 0;
}

bool only_digits(string s)
{
    int count = 0;
    int len = strlen(s);
    for (int i = 0; i < len; i++)
    {
        if (isdigit(s[i]))
            count++;
    }
    if (count == len)
        return true;
    else
        return false;
}
// rotate('A', 26) -> return 'A'
char rotate(char c, int n)
{
    int valueChar = (int) c;
    if (isupper(c))
    {
        valueChar += n % 26;
        if (valueChar > 90)
            valueChar -= 26;
    }
    if (islower(c))
    {
        valueChar += n % 26;
        if (valueChar > 122)
            valueChar -= 26;
    }
    if (isdigit(c))
    {
        valueChar += n % 10;
        if (valueChar > 57)
            valueChar -= 10;
    }
    if (ispunct(c))
        return c;
    return (char) valueChar;
}