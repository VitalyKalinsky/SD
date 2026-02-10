#ifndef BASEFILE_HPP
#define BASEFILE_HPP

#include <cstdio>

class BaseFile
{
private:
    FILE *file_ptr;
    const char *open_mode;

public:
    BaseFile();
    BaseFile(const char *filename, const char *mode);
    BaseFile(FILE *fp);

    ~BaseFile();

    bool is_open() const;
    bool can_read() const;
    bool can_write() const;

    size_t write_raw(const void *buf, size_t n_bytes);
    size_t read_raw(void *buf, size_t n_bytes);

    size_t write(const void *buf, size_t n_bytes);
    size_t read(void *buf, size_t n_bytes);

    long tell() const;
    bool seek(long offset);

    bool close();
};

#endif