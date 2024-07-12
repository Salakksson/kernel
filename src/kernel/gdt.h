#pragma once

#include "pch.h"

typedef struct
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t limit_high;
    uint8_t base_high;
}__attribute__((packed)) gdt_entry;

typedef struct
{
    uint16_t size;
    gdt_entry* addr;
}__attribute__((packed)) gdt_descriptor;

typedef enum 
{
    ACCESS_CODE_READABLE          = 0x02,
    ACCESS_DATA_WRITEABLE         = 0x02,
    ACCESS_CODE_CONFORMING        = 0x04,
    ACCESS_DATA_DIRECTION_NORMAL  = 0x00,
    ACCESS_DATA_DIRECTION_DOWN    = 0x04,

    ACCESS_DATA_SEGMENT           = 0x10,
    ACCESS_CODE_SEGMENT           = 0x18,
    ACCESS_TASK_STATE             = 0x00,

    ACCESS_RING0                  = 0x00,
    ACCESS_RING1                  = 0x20,
    ACCESS_RING2                  = 0x40,
    ACCESS_RING3                  = 0x60,

    ACCESS_ENABLED                = 0x80,

} GDT_ACCESS;

typedef enum 
{
    GDT_FLAG_64BIT                = 0x20,
   GDT_FLAG_32BIT                 = 0x40,
    GDT_FLAG_16BIT                = 0x00,

    GDT_FLAG_GRANULARITY_FINE     = 0x00,
    GDT_FLAG_GRANULARITY_WIDE     = 0x80,
} GDT_FLAGS;

#define LOW_16(u)                 (u & 0xffff)
#define HMID_8(u)                 ((u >> 16) & 0xff)
#define HIGH_8(u)                 ((u >> 24) & 0xff)
#define FLAGS_LIMIT_HIGH(l, f)    (((l >> 16) & 0xf) | (f & 0xf0))

#define GDT_ENTRY(base, limit, access, flags) (gdt_entry)\
{\
    LOW_16(limit),                      \
    LOW_16(base),                       \
    HMID_8(base),                       \
    access,                             \
    FLAGS_LIMIT_HIGH(limit, flags),     \
    HIGH_8(base)                        \
}
