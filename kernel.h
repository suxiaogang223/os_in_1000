#pragma once
struct sbiret {
    long error;
    long value;
};

#define PANIC(fmt, ...)                                         \
    do {                                                        \
        printf("PANIC at %s:%d: " fmt "\n", __FILE__, __LINE__, \
               ##__VA_ARGS__);                                  \
        for (;;) {                                              \
            __asm__ __volatile__("wfi");                        \
        }                                                       \
    } while (0)