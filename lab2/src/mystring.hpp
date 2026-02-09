#ifndef MYSTRING_HPP
#define MYSTRING_HPP

#include <iostream>

class MyString {
private:
    char* data;
    size_t length;
    size_t capacity;
    
    void reallocate(size_t new_capacity);
    void copy_from(const char* str, size_t len);
    
public:
    MyString();
    MyString(const char* str);
    MyString(const MyString& other);
    ~MyString();
    
    MyString& operator=(const MyString& other);
    
    char get(int i) const;
    void set(int i, char c);
    void set_new_string(const char* str);
    
    void print() const;
    void read_line();
    
    size_t get_length() const;
    size_t get_capacity() const;
    
    const char* c_str() const;
};

#endif