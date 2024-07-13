#pragma once

#include "pch.h"

void outb(uint16_t port, uint8_t data);

uint8_t inb(uint16_t port);

inline void io_wait()
{
    outb(0x80, 0); // unused port
}
