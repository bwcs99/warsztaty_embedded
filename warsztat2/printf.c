#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>

#define VA_ARGS_LENGTH_PRIV( _1,    _2,   _3,   _4,   _5,   _6,   _7,   _8,   _9,  _10, \
                             _11,  _12,  _13,  _14,  _15,  _16,  _17,  _18,  _19,  _20, \
                             _21,  _22,  _23,  _24,  _25,  _26,  _27,  _28,  _29,  _30, \
                             _31,  _32,  _33,  _34,  _35,  _36,  _37,  _38,  _39,  _40, \
                             _41,  _42,  _43,  _44,  _45,  _46,  _47,  _48,  _49,  _50, \
                             _51,  _52,  _53,  _54,  _55,  _56,  _57,  _58,  _59,  _60, \
                             _61,  _62,  _63,  _64,  _65,  _66,  _67,  _68,  _69,  _70, \
                             _71,  _72,  _73,  _74,  _75,  _76,  _77,  _78,  _79,  _80, \
                             _81,  _82,  _83,  _84,  _85,  _86,  _87,  _88,  _89,  _90, \
                             _91,  _92,  _93,  _94,  _95,  _96,  _97,  _98,  _99, _100, \
                            _101, _102, _103, _104, _105, _106, _107, _108, _109, _110, \
                            _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, \
                            _121, _122, _123, _124, _125, _126, _127, _128,   _N,  ...) _N

#define VA_ARGS_LENGTH(...) VA_ARGS_LENGTH_PRIV(__VA_ARGS__,  \
                 128, 127, 126, 125, 124, 123, 122, 121, 120, \
            119, 118, 117, 116, 115, 114, 113, 112, 111, 110, \
            109, 108, 107, 106, 105, 104, 103, 102, 101, 100, \
             99,  98,  97,  96,  95,  94,  93,  92,  91,  90, \
             89,  88,  87,  86,  85,  84,  83,  82,  81,  80, \
             79,  78,  77,  76,  75,  74,  73,  72,  71,  70, \
             69,  68,  67,  66,  65,  64,  63,  62,  61,  60, \
             59,  58,  57,  56,  55,  54,  53,  52,  51,  50, \
             49,  48,  47,  46,  45,  44,  43,  42,  41,  40, \
             39,  38,  37,  36,  35,  34,  33,  32,  31,  30, \
             29,  28,  27,  26,  25,  24,  23,  22,  21,  20, \
             19,  18,  17,  16,  15,  14,  13,  12,  11,  10, \
              9,   8,   7,   6,   5,   4,   3,   2,   1)


static int my_printf(const char* format_p, ...);

static size_t convert_int_to_byte_array(const int number, char buffer[]);

bool check_number_of_arguments(const char* format_p, size_t format_length, size_t number_of_arguments)
{
    size_t current_number_of_arguments = 0;

    for(size_t i = 0 ; i < format_length ; i++)
    {
        if(format_p[i] == '%')
        {
            i += 1;

            if(i < format_length)
            {
                switch(format_p[i])
                {
                    case 'c':
                        current_number_of_arguments += 1;
                        break;
                    case 'd':
                        current_number_of_arguments += 1;
                        break;
                    default:
                        break;
                }

            }
        }
    }

    if(current_number_of_arguments == number_of_arguments)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static int my_printf(const char* format_p, ...)
{
    /* Think about check if number of '%' equals LENGTH(...)! */


    if (format_p == NULL)
    {
        return -1;
    }

    const size_t format_length = strlen(format_p);

    if (format_length == 0)
    {
        return -1;
    }

    va_list va_args;
    va_start(va_args, format_p);

 /*   if(!check_number_of_arguments(format_p, format_length, number_of_arguments))
    {
        perror("Niepoprawna liczba argumentów ! \n");
        return -1;
    } */

    enum { STDOUT = 0 };

    size_t buffer_inserted_elements = 0;
    const size_t buffer_length = 256;

    ssize_t number_of_bytes_written = 0;

    size_t offset = 0;

    /* Think about buffer overflow or too many write calls! */
    char buffer[buffer_length];
    (void)memset(&buffer[0], 0, sizeof(buffer));

    for (size_t i = 0; i < format_length; ++i)
    {
        /* TODO: do not forget about corner case like: printf("%%"); */
        if (format_p[i] == '%')
        {
            i += 1;

            switch (format_p[i])
            {
                case '%':
                {
                    buffer[buffer_inserted_elements] = '%';
                    buffer_inserted_elements++;
                    break;
                }

                case 'c':
                {
                    /* second argument to 'va_arg' is of promotable type 'char'; 
                     * this va_arg has undefined behavior because arguments will be promoted to 'int' */
                    const char val = (char)va_arg(va_args, int);
                    buffer[buffer_inserted_elements] = val;
                    buffer_inserted_elements += 1;
                    break;
                }

                case 'd':
                {
                    const int val = (int)va_arg(va_args, int);
                    buffer_inserted_elements += convert_int_to_byte_array(val, &buffer[buffer_inserted_elements]);
                    break;
                }

                default:
                    break;
            }
        }
        else
        {
            buffer[buffer_inserted_elements] = format_p[i];
            buffer_inserted_elements += 1;
        }

        if(buffer_inserted_elements == buffer_length)
        {
            ssize_t bytes_written = write(STDOUT, &buffer[0], buffer_inserted_elements);

            if(bytes_written == -1)
            {
                perror("Fatalnie - nie udało się wypisać części napisu ! \n");
                return -1;
            }
            else
            {
                number_of_bytes_written += bytes_written;

                buffer_inserted_elements = 0;
                (void)memset(&buffer[0], 0, sizeof(buffer));
            }


        }

    }

    va_end(va_args);

    if(format_length < buffer_length)
    {
        ssize_t bytes_written = write(STDOUT, &buffer[0], buffer_inserted_elements);

        if(bytes_written == -1)
        {
            perror("Fatalnie - nie udało się wypisać części napisu ! \n");
            return -1;
        }
        else
        {
            return (int)bytes_written;
        }

    }

    ssize_t bytes_written = write(STDOUT, &buffer[0], buffer_inserted_elements);

    if(bytes_written == -1)
    {
        perror("Fatalnie - nie udało się wypisać części napisu ! \n");
        return -1;
    }

    number_of_bytes_written += bytes_written;
    return (int)number_of_bytes_written;
    
}

static size_t convert_int_to_byte_array(const int number, char buffer[])
{
    // STEP1: calculate how many characters will we have including 'minus'
    int copy_number = number;
    size_t internal_buffer_size = 0;

    if (number < 0)
    {
        internal_buffer_size++;
        copy_number *= -1;
    }

    while (copy_number > 0)
    {
        internal_buffer_size++;
        copy_number /= 10;
    }

    // STEP2: create buffer by using VLA feature
    char internal_buffer[internal_buffer_size];

    // STEP3: assign once again original number
    if (number < 0)
    {
        copy_number = number * -1;
    }
    else
    {
        copy_number = number;
    }

    /* STEP4: Save digits for our internal buffer
     *        Digits got from any number will be in reverse order (modulo operation)
     *
     * Example:
     *          From 125 we want: '1', '2', '5' but
     * 
     *          1) 125 % 10 = 5; 125 / 10 = 12
     *          2) 12  % 10 = 2; 12  / 10 = 1;
     *          3) 1   % 10 = 1; 1   / 10 = 0;
     * 
     *          In internal buffer we will have ['5', '2', '1']
     */
    size_t j = 0;

    while (copy_number > 0)
    {
        const char digit = (char)(copy_number % 10);

        // We need to add 48 because of '0' start in 48 position in ASCII table.
        internal_buffer[j] = digit + 48;
        j++;

        copy_number /= 10;
    }

    if (number < 0)
    {
        internal_buffer[internal_buffer_size - 1] = '-';
    }

    // assign from VLA to buffer
    for (size_t i = 0; i < internal_buffer_size; ++i)
    {
        buffer[i] = internal_buffer[internal_buffer_size - i - 1];
    }

    return internal_buffer_size;
}



int main(void)
{
    my_printf("Example: %c %d %d\n", 'C', 99, -101);

/*    my_printf("Ala %d ma %c kota %d\n", 1, 'a');

    my_printf("Ala %d ma kota\n", 1, 2);

    my_printf("Ala %d %c %d %c ma kota\n", 1, 'a', 1, 'b', 0); */

    my_printf("The C library function void *memset(void *str, int c, size_t n) %d copies the character c \
    (an unsigned char) to the %c first n characters of the string pointed to, by the argument str %d.\n", 1, 'a', 2);

    my_printf("Upon successful %d %c %d %c completion, write() and pwrite() shall return the number of \
    bytes actually written to the file associated with fildes. \
    This number shall never be greater than nbyte. Otherwise, -1 \
    shall be returned and errno set to indicate the error.\n", 1, 'a', 2, 'b');

    my_printf("zip  is  a  compression  and  file packaging utility for Unix, VMS, MSDOS, OS/2, Windows 9x/NT/XP, Minix, Atari, Macintosh, \
    Amiga, and Acorn RISC OS. %d It is analogous to a combination of the Unix commands tar(1) and compress(1) and  is  compatible \
    with PKZIP (Phil Katz's ZIP for MSDOS systems).\n", 10000); 

    return 0;
}