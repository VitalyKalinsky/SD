#include "BaseFile.hpp"
#include <cstring>
#include <cstdio>
#include <iostream>
using namespace std;

BaseFile::BaseFile() : file_ptr(nullptr), open_mode(nullptr)
{
#ifndef NDEBUG
    cout << "Def_Constructor called for BaseFile_" << this << endl;
#endif
}

BaseFile::BaseFile(const char *filename, const char *mode) : file_ptr(nullptr), open_mode(nullptr)
{
#ifndef NDEBUG
    cout << "Full_Constructor called for BaseFile_" << this << endl;
#endif
    if (filename && mode)
    {
        file_ptr = fopen(filename, mode);
        if (file_ptr)
        {
            open_mode = mode;
        }
    }
}

BaseFile::BaseFile(FILE *fp) : file_ptr(fp)
{
#ifndef NDEBUG
    cout << "File_Constructor called for BaseFile_" << this << endl;
#endif
}

BaseFile::~BaseFile()
{
#ifndef NDEBUG
    cout << "Destructor called for BaseFile_" << this << endl;
#endif
    close();
}

bool BaseFile::is_open() const
{
    return file_ptr != nullptr;
}

bool BaseFile::can_read() const
{
    if (!is_open())
        return false;

    if (open_mode)
    {
        return strchr(open_mode, 'r') != nullptr ||
               strchr(open_mode, '+') != nullptr;
    }

    long current_pos = ftell(file_ptr);
    if (current_pos == -1L)
        return false;

    if (fseek(file_ptr, 0, SEEK_END) != 0)
        return false;
    long end_pos = ftell(file_ptr);

    fseek(file_ptr, current_pos, SEEK_SET);

    return current_pos < end_pos;
}

bool BaseFile::can_write() const
{
    if (!is_open())
    {
        printf("file is closed. cannot write\n");
        return false;
    }

    if (open_mode)
    {
        return strchr(open_mode, 'w') != nullptr ||
               strchr(open_mode, 'a') != nullptr ||
               strchr(open_mode, '+') != nullptr;
    }

    return false;
}

size_t BaseFile::write_raw(const void *buf, size_t n_bytes)
{
    if (!is_open() || !buf || n_bytes == 0)
    {
        return 0;
    }

    size_t written = fwrite(buf, 1, n_bytes, file_ptr);
    return written;
}

size_t BaseFile::write(const void *buf, size_t n_bytes)
{
    return write_raw(buf, n_bytes);
}

size_t BaseFile::read_raw(void *buf, size_t n_bytes)
{
    if (!is_open() || !buf || n_bytes == 0)
    {
        return 0;
    }

    size_t read = fread(buf, 1, n_bytes, file_ptr);
    return read;
}

size_t BaseFile::read(void *buf, size_t n_bytes)
{
    return read_raw(buf, n_bytes);
}

long BaseFile::tell() const
{
    if (!is_open())
    {
        return -1L;
    }

    long pos = ftell(file_ptr);
    return pos;
}

bool BaseFile::seek(long offset)
{
    if (!is_open())
    {
        return false;
    }

    int result = fseek(file_ptr, offset, SEEK_SET);
    return (result == 0);
}

bool BaseFile::close()
{
    if (file_ptr)
    {
        int result = fclose(file_ptr);
        file_ptr = nullptr;
        return (result == 0);
    }
    return true;
}