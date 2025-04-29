#include "../incl/idt.h"

idt_entry IDT[256] = {0};

idt_descriptor IDT_Descriptor = {sizeof(IDT) - 1, IDT};

void fill_idt_entry(int i, void* entry_point, uint16_t segment, uint8_t flags)
{
    uint64_t b = (uintptr_t)(entry_point);    // Prevent gcc from complaining about pointer arithmetic
    IDT[i].offset_1 = b & 0xffff;
    IDT[i].selector = segment << 3; 
    IDT[i].ist      = 0;                      // Not using IST 
    IDT[i].flags    = flags; 
    IDT[i].offset_2 = (b >> 16) & 0xffff;
    IDT[i].offset_3 = b >> 32;
    IDT[i].reserved = 0;
}

void idt_enable(int i)
{
    IDT[i].flags |= IDT_FLAG_PRESENT;
}

void idt_disable(int i)
{
    IDT[i].flags &= ~IDT_FLAG_PRESENT;
}

void load_idt(idt_descriptor* desc)
{
    __asm__("lidt %0" :: "m"(*desc));
}






