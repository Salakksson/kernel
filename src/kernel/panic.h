#pragma once

#include "isr.h" // Includes pch: tty and printf

void panic_if(interrupt_frame* frame);
