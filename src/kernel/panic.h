#pragma once

#include "isr.h" // Includes pch: tty and printf

void panicf(const char* msg, ...);

void panicst(cpustate* frame);

void panicfst(cpustate* frame, const char* msg, ...);
