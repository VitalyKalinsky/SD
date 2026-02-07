#include "textwrapper.hpp"
#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;
TextWrapper::TextWrapper(const MyString &input, int width)
    : input_text(input), max_line_length(width), words(nullptr), word_count(0)
{

    if (max_line_length <= 0)
    {
        max_line_length = 40;
    }

    words = new char *[1024]();
    find_words();
}

TextWrapper::~TextWrapper()
{
    cleanup();
}

void TextWrapper::cleanup()
{
    if (words != nullptr)
    {
        for (int i = 0; i < word_count; i++)
        {
            delete[] words[i];
        }
        delete[] words;
        words = nullptr;
    }
    word_count = 0;
    max_line_length = 0;
}

void TextWrapper::find_words()
{
    int word_start = -1;
    const char *c_str = input_text.c_str();
    char c = c_str[0];

    for (int i = 1; i <= input_text.get_length(); i++)
    {
        if (is_separator(c))
        {
            if (word_start != -1)
            {
                process_word(i - 1 - word_start, c_str, word_start);
                word_start = -1;
            }
        }
        else
        {
            if (word_start == -1)
                word_start = i - 1;
        }
        c = c_str[i];
    }
}

bool TextWrapper::is_separator(char c) const
{
    return c == ' ' || c == '\n' || c == '\0' || c == '\t';
}

void TextWrapper::process_word(int word_length, const char *c_str, int word_start)
{
    words[word_count] = new char[word_length + 1];

    for (int i = 0; i < word_length; i++)
    {
        words[word_count][i] = c_str[word_start + i];
    }

    words[word_count][word_length] = '\0';
    word_count++;
}

void TextWrapper::print_big_word(int word_length, int &cur_length, int index) const
{
    int symbol_counter = 0;
    while (symbol_counter != word_length)
    {
        cout << words[index][symbol_counter++];
        if (++cur_length >= max_line_length && symbol_counter >= max_line_length)
        {
            cout << "\n";
            cur_length = 0;
        }
    }
    cout << " ";
    cur_length++;
}

void TextWrapper::print_wrapped() const
{
    int cur_length = 0;
    int word_length;
    int potential_length;

    for (int i = 0; i < word_count; i++)
    {
        word_length = strlen(words[i]);
        potential_length = cur_length + word_length;
        if (potential_length > max_line_length)
        {
            cout << "\n";
            cur_length = 0;
        }
        if (word_length >= max_line_length)
        {
            print_big_word(word_length, cur_length, i);
            continue;
        }
        cout << words[i] << " ";
        cur_length += word_length + 1;
    }
    cout << endl;
}
