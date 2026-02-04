#include "mystring.hpp"
#include <cstring>
#include <cassert>
#include <iostream>
using namespace std;

void MyString::reallocate(size_t new_capacity)
{
    if (new_capacity <= capacity)
        return;

    char *new_data = new char[new_capacity];
    if (data != nullptr)
    {
        memcpy(new_data, data, length + 1);
        delete[] data;
    }
    data = new_data;
    capacity = new_capacity;
}

void MyString::copy_from(const char *str, size_t len)
{
    if (len + 1 > capacity)
    {
        reallocate(len + 1);
    }
    memcpy(data, str, len);
    data[len] = '\0';
    length = len;
}

MyString::MyString() : data(nullptr), length(0), capacity(0)
{
    reallocate(16);
    data[0] = '\0';
}

MyString::MyString(const char *str) : data(nullptr), length(0), capacity(0)
{
    if (str != nullptr)
    {
        length = strlen(str);
        reallocate(length + 1);
        strcpy(data, str);
    }
    else
    {
        reallocate(16);
        data[0] = '\0';
    }
}

MyString::MyString(const MyString &other) : data(nullptr), length(0), capacity(0)
{
    if (other.data != nullptr)
    {
        length = other.length;
        reallocate(other.capacity);
        strcpy(data, other.data);
    }
    else
    {
        reallocate(16);
        data[0] = '\0';
    }
}

MyString::~MyString()
{
    delete[] data;
    data = nullptr;
}

MyString &MyString::operator=(const MyString &other)
{
    if (this != &other)
    {
        if (other.length + 1 <= capacity)
        {
            strcpy(data, other.data);
            length = other.length;
        }
        else
        {
            delete[] data;
            length = other.length;
            capacity = other.capacity;
            data = new char[capacity];
            strcpy(data, other.data);
        }
    }
    return *this;
}

char MyString::get(int i) const
{
    if (i < 0 || i >= static_cast<int>(length))
    {
        return '\0';
    }
    return data[i];
}

void MyString::set(int i, char c)
{
    if (i < 0 || i >= static_cast<int>(length))
    {
        return;
    }
    data[i] = c;
}

void MyString::set_new_string(const char *str)
{
    if (str == nullptr)
    {
        data[0] = '\0';
        length = 0;
        return;
    }

    size_t new_length = strlen(str);
    if (new_length + 1 <= capacity)
    {
        strcpy(data, str);
        length = new_length;
    }
    else
    {
        delete[] data;
        length = new_length;
        capacity = length + 1;
        data = new char[capacity];
        strcpy(data, str);
    }
}

void MyString::print() const
{
    cout << data << endl;
}

void MyString::read_line() {
    const size_t INITIAL_CAPACITY = 16;
    const size_t CHUNK_SIZE = 256;
    
    if (capacity < INITIAL_CAPACITY) {
        delete[] data;
        capacity = INITIAL_CAPACITY;
        data = new char[capacity];
    }
    cin.clear();
    size_t pos = 0;    
    while (true) {
        if (pos + 1 >= capacity) {
            capacity = (pos + CHUNK_SIZE) * 2;
            char* new_data = new char[capacity];
            if (pos > 0) {
                memcpy(new_data, data, pos);
            }
            delete[] data;
            data = new_data;
        }
        
        char ch;
        cin.get(ch);
        
        if (ch == '\n') {
            break;
        }
        
        data[pos++] = ch;
    }
    
    data[pos] = '\0';
    length = pos;
}

size_t MyString::get_length() const
{
    return length;
}

size_t MyString::get_capacity() const
{
    return capacity;
}

const char *MyString::c_str() const
{
    return data ? data : "";
}