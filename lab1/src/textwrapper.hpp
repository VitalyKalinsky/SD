#ifndef TEXTWRAPPER_HPP
#define TEXTWRAPPER_HPP

#include "mystring.hpp"

class TextWrapper
{
private:
    MyString input_text;
    int max_line_length;
    char **words;
    int word_count;

    void find_words();
    void cleanup();
    bool is_separator(char c) const;
    void process_word(int word_length, const char *c_str, int word_start);
    void print_big_word(int word_length, int &cur_length, int index) const;

public:
    TextWrapper(const MyString &input, int width = 40);
    ~TextWrapper();

    void print_wrapped() const;
};

#endif