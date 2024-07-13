#include "panic.h"
#include "stdarg.h"

int printf(const char*, ...);

void panicf(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    
    const char* prefix;
    const char* colour;

    tty_colour(WHITE, RED);
    printf("Kernel panic!\n");

    vprintf(msg, args);
    va_end(args);
    for(;;) asm("cli\nhlt\n");
}

void panicst(cpustate* frame)
{
    tty_colour(WHITE, RED);
    printf("Kernel panic!\n");
    printf("reached exception: '%s'\n", exception_str[frame->vector]);
    print_cpustate(frame);
    for(;;) asm("cli\nhlt\n");
}

void panicfst(cpustate* frame, const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    
    const char* prefix;
    const char* colour;

    tty_colour(WHITE, RED);
    printf("Kernel panic!\n");

    vprintf(msg, args);
    va_end(args);
    printf("reached exception: '%s'\n", exception_str[frame->vector]);
    print_cpustate(frame);

    for(;;) asm("cli\nhlt\n");
}
