#include "base32file.hpp"
#include <cstring>
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
Base32File::Base32File() : BaseFile(), ENCODING_CHARS("ABCDEFGHIJKLMNOPQRSTUVWXYZ123456") {}
Base32File::Base32File(const char *filename, const char *mode, const char *user_enc_chars) : BaseFile(filename, mode)
{
    if (strlen(user_enc_chars) == 32)
        ENCODING_CHARS = user_enc_chars;
    else
        ENCODING_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
}
Base32File::Base32File(FILE *fp) : BaseFile(fp), ENCODING_CHARS("ABCDEFGHIJKLMNOPQRSTUVWXYZ123456") {}

//  const char ENCODING_CHARS[32] = {
// 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
// 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
// '1', '2', '3', '4', '5', '6'};

// int encoded32_size(int raw_size)
// {
//     return (raw_size * 8 + 4) / 5;
// }

// int decoded32_size(int encode_size)
// {
//     return encode_size * 5 / 8;
// }
// int encode32(const char *raw_data, int raw_size, char *dst)
// {
//     if (raw_data == nullptr || raw_size < 1 || dst == nullptr)
//     {
//         return 1;
//     }
//     int cur_bit = 4;      // в такую степень возводится
//     int cur_enc_byte = 0; // текущий код символа
//     int cur_enc_five = 0; // индекс добавления в dst
//     for (int byte = 0; byte < raw_size; byte++)
//     {
//         for (int bit = 0; bit < 8; bit++)
//         {
//             // cout << ((raw_data[byte] >> (7 - bit)) & 1); // побитовый вывод
//             cur_enc_byte += (((raw_data[byte] >> (7 - bit)) & 1) << cur_bit--);
//             if (cur_bit < 0)
//             {
//                 dst[cur_enc_five++] = ENCODING_CHARS[cur_enc_byte];
//                 cur_bit = 4;
//                 cur_enc_byte = 0;
//             }
//         }
//     }
//     if (cur_enc_byte != 0 || cur_bit != 4)
//     {
//         dst[cur_enc_five++] = ENCODING_CHARS[cur_enc_byte];
//     }
//     return 0;
// }

// int decode32(const char *encoded_data, int encoded_size, char *dst)
// {
//     if (encoded_data == nullptr || encoded_size < 1 || dst == nullptr)
//     {
//         return 1;
//     }

//     int cur_dec_byte = 0;     // текущий  декодирования
//     int bits_in_dec_byte = 0; // сколько бит в текущем декодируемом
//     int cur_dst_index = 0;    // индекс dst
//     for (int byte = 0; byte < encoded_size; byte++)
//     {
//         if ((encoded_data[byte] < 'A' || encoded_data[byte] > 'Z') && (encoded_data[byte] < '1' || encoded_data[byte] > '6'))
//         {
//             return 2;
//         }

//         int char_index = 0; // индекс в массиве ENCODING_CHARS(cur_enc_byte в encode)
//         for (; ENCODING_CHARS[char_index] != encoded_data[byte]; char_index++)
//             ;

//         for (int bit = 4; bit >= 0; bit--)
//         {
//             cur_dec_byte += ((char_index >> bit) & 1) << (7 - (bits_in_dec_byte++));
//             if (bits_in_dec_byte == 8)
//             {
//                 dst[cur_dst_index++] = cur_dec_byte;
//                 cur_dec_byte = 0;
//                 bits_in_dec_byte = 0;
//             }
//         }
//     }
//     return 0;
// }
