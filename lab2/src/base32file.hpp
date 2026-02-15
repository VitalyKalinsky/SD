#ifndef BASE32FILE_HPP
#define BASE32FILE_HPP
#include "basefile.hpp"

class Base32File : public BaseFile
{
private:
    const char *ENCODING_CHARS;
    const char *get_encoding_chars()
    {
        return ENCODING_CHARS;
    }
    int encoded32_size(int raw_size) const
    {
        return (raw_size * 8 + 4) / 5;
    }
    int decoded32_size(int encode_size) const
    {
        return encode_size * 5 / 8;
    }
    int encode32(const char *raw_data, int raw_size, char *dst);
    int decode32(const char *encoded_data, int encoded_size, char *dst);
public:
    Base32File();
    Base32File(const char *filename, const char *mode, const char *user_enc_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    Base32File(FILE *fp);

    size_t write(const void *buf, size_t n_bytes);
    size_t read(void *buf, size_t n_bytes);
};

#endif