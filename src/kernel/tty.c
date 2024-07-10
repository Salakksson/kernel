#include "tty.h"

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

void tty_clear()
{
    for(size_t i = 0; i < (ROWS * COLS); i++)
        ((uint16_t*)buffer)[i] = (((uint16_t)(colour >> 4) * 0b10001) << 8) + ' ';
}

void tty_colour(uint8_t fg, uint8_t bg)
{
    colour = fg | bg << 4;
}

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

void puts(char* str)
{
    for(char c; (c = *str); str++)
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
            puts("\nan error occured during puts!!!");
            return;
        }
        while (row >= ROWS)
        {
            memmove(buffer, buffer + COLS, COLS);
            for (size_t f = COLS; f < 2 * COLS; f++)
            {
                ((uint16_t*)buffer)[f + COLS * (ROWS - 1)] = (((uint16_t)(colour >> 4) * 0b10001) << 8) + ' ';
            }
            row--;
        }
    }
}
