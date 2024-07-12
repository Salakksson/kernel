#pragma once

#include <stdint.h>
#include <stddef.h>
#include "tty.h"
#include "printf.h"

#define asm(a) __asm__(".intel_syntax noprefix\n" a "\n.att_syntax prefix")
