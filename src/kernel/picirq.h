#pragma once

#include "isr.h"

void register_irq_handler(int irq, interrupt_handler handler);

void irq_init();



