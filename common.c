#include "common.h"

void putchar(char ch);

void printf(const char* fmt, ...) {
    va_list vargs;
    va_start(vargs, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;           // skip '%'
            switch (*fmt) {  // scan next char
                case '\0':   // % as end of fmt
                    putchar('%');
                    goto end;
                case '%':  // print %
                    putchar('%');
                    break;
                case 's': {  // print string
                    const char* s = va_arg(vargs, const char*);
                    while (*s) {
                        putchar(*s);
                        s++;
                    }
                    break;
                }
                case 'd': {  // print int
                    int value = va_arg(vargs, int);
                    unsigned magnitude =
                        value;  // https://github.com/nuta/operating-system-in-1000-lines/issues/64
                    if (value < 0) {
                        putchar('-');
                        magnitude = -magnitude;
                    }

                    unsigned divisor = 1;
                    while (magnitude / divisor > 9) divisor *= 10;

                    while (divisor > 0) {
                        putchar('0' + magnitude / divisor);
                        magnitude %= divisor;
                        divisor /= 10;
                    }

                    break;
                }
                case 'x': {  // print as 16
                    unsigned value = va_arg(vargs, unsigned);
                    for (int i = 7; i >= 0; i--) {
                        unsigned nibble = (value >> (i * 4)) & 0xf;
                        putchar("0123456789abcdef"[nibble]);
                    }
                }
            }
        } else {  // print char
            putchar(*fmt);
        }
        fmt++;
    }
end:
    va_end(vargs);
}