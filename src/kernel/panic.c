#include "panic.h"

#include "isr.h" // Includes pch: tty and printf

int printf(const char*, ...);
void print_interrupt_frame(interrupt_frame* frame);

void panic_if(interrupt_frame* frame)
{
    tty_colour(WHITE, RED);
    printf("Kernel panic!\n");
    printf("reached exception: '%s'\n", exception_str[frame->vector]);
    print_interrupt_frame(frame);
    for(;;) asm("cli\nhlt\n");
}
