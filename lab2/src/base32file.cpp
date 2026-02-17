#include "base32file.hpp"
#include <cstring>
#include <iostream>
/**
 * Задание 2.2.1. Base32 кодировщик/декодировщик.
 *
 * Создайте производный класс Base32File, который будет проводить при
 * записи кодировку-декодировку данных, по алгоритму, который вы
 * реализовали в лабораторной работе №4 прошлого семестра.
 *
 * Переопределите методы `read` и `write`, которые будут проводить чтение из
 * файла с декодировкой и запись в файл с кодировкой соответственно.
 *
 * Обратите внимание, что методы `read` и `write` должны иметь ту же логику
 * при последовательном вызове, что и методы `read_raw` и `write_raw` в
 * классе BaseFile, то есть *продолжать* чтение и запись дальше без потери
 * данных.
 *
 * Добавьте возможность пользователю передать в конструктор таблицу
 * кодировки, по умолчанию используется таблица "A..Z1..6".
 */
using namespace std;
const char *const DEFAULT_ENC_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
Base32File::Base32File() : BaseFile(), ENCODING_CHARS(DEFAULT_ENC_CHARS)
{
#ifndef NDEBUG
    cout << "Constructor_def called for Base32File_" << this << endl;
#endif
}
Base32File::Base32File(const char *filename, const char *mode, const char *user_enc_chars) : BaseFile(filename, mode)
{
#ifndef NDEBUG
    cout << "Full_Constructor called for Base32File_" << this << endl;
#endif
    if (strlen(user_enc_chars) == 32)
    {
        ENCODING_CHARS = user_enc_chars;
        for (int i = 0; i < 32; i++)
        {
            for (int j = i + 1; j < 32; j++)
            {
                if (user_enc_chars[i] == user_enc_chars[j])
                {
                    ENCODING_CHARS = DEFAULT_ENC_CHARS;
                }
            }
        }
    }
    else
        ENCODING_CHARS = DEFAULT_ENC_CHARS;
    printf("filename='%s', mode='%s', encoding_chars='%s'\n", filename, mode, ENCODING_CHARS);
}
Base32File::Base32File(FILE *fp) : BaseFile(fp), ENCODING_CHARS(DEFAULT_ENC_CHARS)
{
#ifndef NDEBUG
    cout << "File_Constructor called for Base32File_" << this << endl;
#endif
}
Base32File::~Base32File()
{
#ifndef NDEBUG
    cout << "Destructor called for Base32File_" << this << endl;
#endif
}

int Base32File::encode32(const char *raw_data, int raw_size, char *dst)
{
    if (raw_data == nullptr || raw_size < 1 || dst == nullptr)
    {
        return 1;
    }
    int cur_bit = 4;      // в такую степень возводится
    int cur_enc_byte = 0; // текущий код символа
    int cur_enc_five = 0; // индекс добавления в dst
    for (int byte = 0; byte < raw_size; byte++)
    {
        for (int bit = 0; bit < 8; bit++)
        {
            // cout << ((raw_data[byte] >> (7 - bit)) & 1); // побитовый вывод
            cur_enc_byte += (((raw_data[byte] >> (7 - bit)) & 1) << cur_bit--);
            if (cur_bit < 0)
            {
                dst[cur_enc_five++] = ENCODING_CHARS[cur_enc_byte];
                cur_bit = 4;
                cur_enc_byte = 0;
            }
        }
    }
    if (cur_enc_byte != 0 || cur_bit != 4)
    {
        dst[cur_enc_five++] = ENCODING_CHARS[cur_enc_byte];
    }
    return 0;
}

int Base32File::decode32(const char *encoded_data, int encoded_size, char *dst)
{
    if (encoded_data == nullptr || encoded_size < 1 || dst == nullptr)
    {
        return 1;
    }
    int cur_dec_byte = 0;     // текущий  декодирования
    int bits_in_dec_byte = 0; // сколько бит в текущем декодируемом
    int cur_dst_index = 0;    // индекс dst
    for (int byte = 0; byte < encoded_size; byte++)
    {
        bool in_alphabet = false;
        for (int i = 0; i < 32; i++)
            in_alphabet = in_alphabet || encoded_data[byte] == ENCODING_CHARS[i];

        if (!in_alphabet)
        {
            return 2;
        }

        int char_index = 0; // индекс в массиве ENCODING_CHARS(cur_enc_byte в encode)
        for (; ENCODING_CHARS[char_index] != encoded_data[byte]; char_index++)
            ;

        for (int bit = 4; bit >= 0; bit--)
        {
            cur_dec_byte += ((char_index >> bit) & 1) << (7 - (bits_in_dec_byte++));
            if (bits_in_dec_byte == 8)
            {
                dst[cur_dst_index++] = cur_dec_byte;
                cur_dec_byte = 0;
                bits_in_dec_byte = 0;
            }
        }
    }
    return 0;
}

size_t Base32File::write(const void *buf, size_t n_bytes)
{
    n_bytes = min(n_bytes, strlen(static_cast<const char *>(buf)));
    int enc32_size = encoded32_size(n_bytes);
    char *dst = new char[enc32_size]();
    encode32(static_cast<const char *>(buf), n_bytes, dst);
#ifndef NDEBUG
    cout << "enc32_size: " << enc32_size << endl;

    cout << "Закодировано: ";
    for (int i = 0; i < enc32_size; i++)
    {
        cout << dst[i];
    }
    cout << endl;
#endif
    size_t written = write_raw(dst, enc32_size);
    delete[] dst;
    return written;
}

size_t Base32File::read(void *buf, size_t n_bytes)
{
    int enc32_size = encoded32_size(n_bytes); // сколько байтов в файле весит то, что мы хотим прочитать
    char *encoded_buf = new char[enc32_size];
    size_t bytes_read = read_raw(encoded_buf, enc32_size);
    decode32(encoded_buf, enc32_size, static_cast<char *>(buf));
#ifndef NDEBUG
    cout << "enc32_size: " << enc32_size << endl;
    cout << "Декодировано: ";
    for (int i = 0; i < n_bytes; i++)
    {
        cout << static_cast<char *>(buf)[i];
    }
    cout << endl;
#endif
    delete[] encoded_buf;
    return n_bytes;
}