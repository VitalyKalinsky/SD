#ifndef BASE32FILE_HPP
#define BASE32FILE_HPP
#include "basefile.hpp"
#include <cstdio>

class Base32File : public BaseFile
{
private:
    const char *ENCODING_CHARS;

public:
    Base32File();
    Base32File(const char *filename, const char *mode, const char *user_enc_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    Base32File(FILE *fp);

    // size_t write(const void *buf, size_t n_bytes);
    // size_t read(void *buf, size_t n_bytes);

    const char *get_encoding_chars(){
        return ENCODING_CHARS;
    }
};

#endif