#include "../incl/picirq.h"
#include "../incl/isr.h"
#include "../incl/idt.h"
#include "../incl/panic.h"
#include "../incl/ports.h"


#define PIC1_PORT_COMMAND   0x20
#define PIC1_PORT_DATA      0x21
#define PIC2_PORT_COMMAND   0xa0
#define PIC2_PORT_DATA      0xa1

#define PIC_EOI             0x20

#define PIC_REMAP_OFFSET    0x20

// Flags coppied of osdev wiki
#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */

#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

static void pic_send_eoi(uint8_t irq)
{
    if(irq >= 8)
        outb(PIC2_PORT_COMMAND, PIC_EOI);
    outb(PIC1_PORT_COMMAND, PIC_EOI);
}

static void pic_remap(uint8_t offset1, uint8_t offset2)
{
    asm("cli\n");
    outb(PIC1_PORT_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(PIC2_PORT_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_PORT_DATA, offset1);                 // ICW2: Master PIC vector offset
	io_wait();
	outb(PIC2_PORT_DATA, offset2);                 // ICW2: Slave PIC vector offset
    io_wait();
	outb(PIC1_PORT_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	outb(PIC2_PORT_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
	
	outb(PIC1_PORT_DATA, ICW4_8086);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)
	io_wait();
	outb(PIC2_PORT_DATA, ICW4_8086);
	io_wait();
	
	outb(PIC1_PORT_DATA, 0);   // unmask all interrupts
	outb(PIC2_PORT_DATA, 0);   // since interrupt flag is clear this will prevent having to unmask these in the future
}

// void pic_mask_irq(int irq)
// {
//     if (irq < 8)
//     {
//         uint8_t mask = inb(PIC1_PORT_DATA);
//         outb(PIC1_PORT_DATA, mask | 1 << (irq - 8));
//     }
//     else
//     {
//         uint8_t mask = inb(PIC2_PORT_DATA);
//         outb(PIC2_PORT_DATA, mask | 1 << (irq - 8));
//     }
// }

interrupt_handler irq_handlers[16];

void register_irq_handler(int irq, interrupt_handler handler)
{
    irq_handlers[irq] = handler;    
}

void global_irq_handler(cpustate* frame)
{
    uint8_t irq = frame->vector - PIC_REMAP_OFFSET;

    if (irq > 15)
        return panicfst(frame, "attempted irq out of range: irq %d, vector: %d", frame->vector, irq);
    if (!irq_handlers[irq])
        printf("no handler for irq %d\n", irq);
    else
        irq_handlers[irq](frame);

    pic_send_eoi(irq);
}

void irq_int_timer()
{
    static int time = 0;
    time++;
    size_t r, c;
    get_cursor_position(&r, &c);
    set_cursor_position(0, VGA_COLS - 10);
    printf("time: %d", time); 
    set_cursor_position(r, c);
}

void irq_init()
{
    pic_remap(PIC_REMAP_OFFSET, PIC_REMAP_OFFSET + 8);
    
    for (int i = 0; i < 16; i++)
    {
        set_interrupt_handler(PIC_REMAP_OFFSET + i, global_irq_handler);
    }
    register_irq_handler(0, irq_int_timer);
    asm("sti\n");
}


