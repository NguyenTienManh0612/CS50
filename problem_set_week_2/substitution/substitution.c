#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool only_alpha(string s);
void standardize_key(string key);
bool check_duplicate_key(string s);
void match_key(string key, string encrypt);

int main(int argc, string argv[])
{
    string plaintext;
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        if (strlen(argv[1]) == 26)
        {
            if (only_alpha(argv[1]) && check_duplicate_key(argv[1]))
            {
                plaintext = get_string("plaintext: ");
                int len = strlen(plaintext);
                standardize_key(argv[1]);
                printf("ciphertext: ");
                match_key(argv[1], plaintext);
                for (int i = 0; i < len; i++)
                    printf("%c", plaintext[i]);
                printf("\n");
            }
            else
            {
                printf("Key must contain exactly 26 characters once, not including numbers, punctuations or spaces.\n");
                return 1;
            }
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    return 0;
}

bool only_alpha(string s)
{
    int count = 0;
    int len = strlen(s);
    for (int i = 0; i < len; i++)
        if (isalpha(s[i]))
            count++;
    if (count == len)
        return true;
    else
        return false;
}

void standardize_key(string key)
{
    for (int i = 0, len = strlen(key); i < len; i++)
        if (islower(key[i]))
            key[i] = toupper(key[i]);
}

bool check_duplicate_key(string s)
{
    standardize_key(s);
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (s[i] == s[j])
                return false;
        }
    }
    return true;
}

void match_key(string key, string encrypt)
{
    int len = strlen(encrypt);
    for (int i = 0; i < len; i++)
    {
        int dec = (int) encrypt[i]; // stored the decimal type of characters
        if(islower(encrypt[i]))
            encrypt[i] = tolower(key[dec - 'a']);
        if(isupper(encrypt[i]))
            encrypt[i] = key[dec - 'A'];
    }
}