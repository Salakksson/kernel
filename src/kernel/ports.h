#pragma once

#include "pch.h"

void port_outb(uint16_t port, uint8_t data);

uint8_t port_inb(uint16_t port);