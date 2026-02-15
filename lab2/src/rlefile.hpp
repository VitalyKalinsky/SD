#ifndef RLEFILE_HPP
#define RLEFILE_HPP

#include "basefile.hpp"
#include "mystring.hpp"

class RleFile : public BaseFile
{
private:
    MyString compress(const void* buf, size_t n_bytes) const;
    MyString decompress(const void* buf, size_t n_bytes) const;

public:
    RleFile();
    RleFile(const char *filename, const char *mode);
    RleFile(FILE *fp);
    
    size_t write(const void *buf, size_t n_bytes);
    size_t read(void *buf, size_t n_bytes);
};

#endif