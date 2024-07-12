#pragma once

#include "pch.h"

typedef struct
{
    uint16_t offset_1;
    uint16_t selector;
    uint8_t  ist;
    uint8_t  flags;
    uint16_t offset_2;
    uint32_t offset_3;
    uint32_t reserved;

}__attribute__((packed)) idt_entry;


typedef struct
{
    uint16_t limit;
    idt_entry* entry;
}__attribute__((packed)) idt_descriptor;

extern idt_descriptor IDT_Descriptor;

enum
{
    IDT_FLAG_INT      = 0x0e,
    IDT_FLAG_TRAP     = 0x0f,
    DPL_RING0         = 0x00,
    DPL_RING1         = 0x20,
    DPL_RING2         = 0x40,
    DPL_RING3         = 0x60,
    IDT_FLAG_PRESENT  = 0x80,
};


void fill_idt_entry(int i, void* base, uint16_t segment, uint8_t flags);

void idt_enable(int i);

void idt_disable(int i);

void load_idt(idt_descriptor* desc);



