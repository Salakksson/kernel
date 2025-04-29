#pragma once

#include <stdint.h>
#include <stddef.h>
#include "vga.h"
#include "printf.h"

#define asm(a) __asm__(".intel_syntax noprefix\n" a "\n.att_syntax prefix")


void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
