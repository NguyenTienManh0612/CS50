from cs50 import get_string

def count_letters(text):
    count_letters = 0
    for char in text:
        if char.isalpha():
            count_letters += 1
    return count_letters

def count_words(text):
    list_words = text.split()
    return len(list_words)

def count_sentences(text):
    count_sentences = 0
    for char in text:
        if char == '.' or char == '?' or char == '!':
            count_sentences += 1
    return count_sentences

def main():
    text = get_string("Text: ")

    num_letters = count_letters(text)
    num_words = count_words(text)
    num_sentences = count_sentences(text)

    L = num_letters / num_words * 100
    S = num_sentences / num_words * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    if round(index) < 1:
        print("Before Grade 1")
    elif round(index) >= 16:
        print("Grade 16+")
    else:
        print("Grade", int(round(index)))

main()
