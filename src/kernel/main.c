#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "keyboard.h"
#include "picirq.h"

#define U64(a) (*(uint64_t*)(&a)) 

void kernel_main(gdt_descriptor* gdt_addr)
{
    tty_clear();
    tty_colour(YELLOW, BLACK);
    
    load_idt(&IDT_Descriptor);
    fill_idt();

    irq_init();
    initps2();
    


    // asm("cli\nhlt\n");
    // printf("exited halt (somehow?)\n");
    for(;;);
}
