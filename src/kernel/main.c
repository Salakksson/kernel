#include "incl/idt.h"
#include "incl/isr.h"
#include "incl/keyboard.h"
#include "incl/picirq.h"
#include <limine.h>

#define U64(a) (*(uint64_t*)(&a)) 

void kernel_main()
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
