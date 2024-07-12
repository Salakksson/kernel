#include "tty.h"
#include "ports.h"

struct tty_char
{
    uint8_t ch;
    uint8_t colour;
};

#define VRAM_ADDR ((void*)0xb8000)
#define ROWS (25)
#define COLS (80)

struct tty_char* buffer = VRAM_ADDR;
size_t col = 0;
size_t row = 0;
uint8_t colour = WHITE | BLACK << 4;

void* memmove(void* dest, const void* src, size_t n) 
{
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;

    if (d < s) for (size_t i = 0; i < n; i++)
    {
        d[i] = s[i];
    }
    else for (size_t i = n; i > 0; i--) 
    {
        d[i-1] = s[i-1];
    }

    return dest;
}

void set_cursor_position(size_t r, size_t c) 
{
    row = r;
    col = c;

    uint16_t position = row * COLS + col;

    port_outb(0x3D4, 0x0F);
    port_outb(0x3D5, (uint8_t)(position & 0xFF));
    port_outb(0x3D4, 0x0E);
    port_outb(0x3D5, (uint8_t)((position >> 8) & 0xFF));
}

static inline void clearchr(int i)
{
    ((uint16_t*)buffer)[i] = (colour << 8) + ' ';
}

void tty_movln()
{
    while (row >= ROWS)
    {
        memmove(buffer, buffer + COLS, sizeof(struct tty_char) * COLS * (ROWS - 1));
        for (size_t f = 0; f < COLS; f++)
        {
            clearchr(f + COLS * (ROWS - 1));
        }
        col = 0;
        row--;
    }
}

void tty_clear()
{
    for(size_t i = 0; i < (ROWS * COLS); i++)
        buffer[i] = (struct tty_char){.ch = ' ', .colour = colour};
    set_cursor_position(0, 0);
}

void tty_colour(uint8_t fg, uint8_t bg)
{
    colour = fg | bg << 4;
}

void _putchar(char c)
{
    if (' ' <= c && c <= '~' )
    {
        struct tty_char cc = {c, colour};
        buffer[col + row * COLS] = cc;
        col++;
        if (col >= COLS)
        {
            col = 0;
            row++;
        }
    }
    else switch(c)
    {
    case '\t':
        col += 4;
        if (col >= COLS)
        {
            col = 0;
            row++;
        }
        break;
    case '\n':
        col = 0;
        row++;
        break;
    default:
        tty_colour(RED, WHITE);
        puts("<unknown char>");
        return;
    }
    tty_movln();
    set_cursor_position(row, col);
}

// __attribute__((no_caller_saved_registers))
void puts(char* str)
{
    for(char c; (c = *str); str++)
    {
        _putchar(c);
    }
}

