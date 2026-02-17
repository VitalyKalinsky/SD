#include "RleFile.hpp"
#include <cstring>
#include <iostream>
using namespace std;

RleFile::RleFile() : BaseFile()
{
#ifndef NDEBUG
    cout << "Constructor_def called for RleFile_" << this << endl;
#endif
}
RleFile::RleFile(const char *filename, const char *mode) : BaseFile(filename, mode)
{
#ifndef NDEBUG
    cout << "Full_Constructor called for RleFile_" << this << endl;
#endif
}
RleFile::RleFile(FILE *fp) : BaseFile(fp)
{
#ifndef NDEBUG
    cout << "File_Constructor called for RleFile_" << this << endl;
#endif
}
RleFile::~RleFile()
{
#ifndef NDEBUG
    cout << "Destructor called for RleFile_" << this << endl;
#endif
}
MyString RleFile::compress(const void *buf, size_t n_bytes) const
{
    const unsigned char *data = static_cast<const unsigned char *>(buf);
    char *temp_buf = new char[2 * n_bytes + 1];
    size_t pos = 0;
    size_t i = 0;
    while (i < n_bytes)
    {
        unsigned char current = data[i];
        unsigned char count = 1;

        while (i + count < n_bytes && data[i + count] == current && count < 255)
        {
            count++;
        }

        temp_buf[pos++] = static_cast<char>(current);
        temp_buf[pos++] = static_cast<char>(count);

        i += count;
    }

    temp_buf[pos] = '\0';
    MyString result(temp_buf);
    delete[] temp_buf;

    return result;
}

MyString RleFile::decompress(const void *buf, size_t n_bytes) const
{
    const unsigned char *data = static_cast<const unsigned char *>(buf);

    size_t decompressed_size = 0; // размер запакованных данных
    size_t i = 0;
    while (i + 1 < n_bytes)
    {
        unsigned char count = data[i + 1];
        decompressed_size += count;
        i += 2;
    }

    char *temp_buf = new char[decompressed_size + 1];
    size_t pos = 0;

    i = 0;
    while (i + 1 < n_bytes)
    {
        unsigned char value = data[i];
        unsigned char count = data[i + 1];

        for (int j = 0; j < count; j++)
        {
            temp_buf[pos++] = static_cast<char>(value);
        }

        i += 2;
    }

    temp_buf[pos] = '\0';
    MyString result(temp_buf);
    delete[] temp_buf;
    return result;
}

size_t RleFile::write(const void *buf, size_t n_bytes)
{
    if (!is_open() || !buf || n_bytes == 0)
    {
        return 0;
    }

    MyString compressed = compress(buf, n_bytes);
    size_t written = write_raw(compressed.c_str(), compressed.get_length());

    return (written == compressed.get_length()) ? written : 0;
}

size_t RleFile::read(void *buf, size_t n_bytes)
{
    if (!is_open() || !buf || n_bytes == 0)
    {
        return 0;
    }

    char *compressed_buf = new char[2 * n_bytes]; // буфер для чтения сжатых данных
    size_t read_compressed = read_raw(compressed_buf, 2 * n_bytes);
    if (read_compressed == 0)
    {
        delete[] compressed_buf;
        return 0;
    }

    MyString decompressed = decompress(compressed_buf, read_compressed);
    delete[] compressed_buf;

    size_t bytes_to_copy = (decompressed.get_length() < n_bytes) ? decompressed.get_length() : n_bytes;
    memcpy(buf, decompressed.c_str(), bytes_to_copy);

    return bytes_to_copy;
}