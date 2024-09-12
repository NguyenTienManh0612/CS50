#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string get_text = get_string("Text: ");
    int num_letters = count_letters(get_text);
    int num_words = count_words(get_text);
    int num_sentences = count_sentences(get_text);
    double L = (double) num_letters / num_words * 100;
    double S = (double) num_sentences / num_words * 100;
    double index = 0.0588 * L - 0.296 * S - 15.8;
    if (round(index) < 1)
        printf("Before Grade 1\n");
    else if (round(index) >= 16)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n", (int) round(index));
}

int count_letters(string text)
{
    int count_letters = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if(isupper(text[i]) || islower(text[i]))
            count_letters++;
    }
    return count_letters;
}

int count_words(string text)
{
    int count_letters = 0;
    int count_spaces = 0;
    // process multiple spaces between words
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        if (isblank(text[i]))
        {
            //remove spaces at the beginning of the text and change multiple spaces into 1 space
            // yet solve with spaces at the end of the text
            if ((isblank(text[i]) && isblank(text[i + 1])) || isblank(text[0]))
            {
                for (int j = i; j < len; j++)
                    text[j] = text[j + 1];
                len--;
                i--;
            }
        }
    }
    // count words
    for (int i = 0; i < len; i++)
    {
        if (isblank(text[i]))
            count_spaces++;
        if (isupper(text[i]) || islower(text[i]))
            count_letters++;
    }
    if (count_letters != 0)
        return (count_spaces + 1);
    else
        return 0;
}

int count_sentences(string text)
{
    int count_sentences = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if(text[i] == '.' || text[i] == '?' || text[i] == '!')
            count_sentences++;
    }
    return count_sentences;
}