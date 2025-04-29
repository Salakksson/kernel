#include "../incl/keyboard.h"
#include "../incl/ports.h"
#include "../incl/picirq.h"

#define PS2_PORT_DATA 0x60
#define PS2_PORT_STATUS 0x64
#define PS2_PORT_COMMAND 0x64

typedef struct
{
    unsigned char output_status: 1;
    unsigned char input_status: 1;
    unsigned char system_flag: 1;
    unsigned char command_or_data: 1;
    unsigned char unknown: 2;
    unsigned char time_out_err: 1;
    unsigned char parity_err: 1;
} __attribute__((packed)) ps2_status_reg;

typedef struct
{
    unsigned char port_int_1: 1;
    unsigned char port_int_2: 1;
    unsigned char system_flag: 1;
    unsigned char zerom: 1;
    unsigned char port_clock_1: 1;
    unsigned char port_clock_2: 1;
    unsigned char port_translation: 1;
    unsigned char zero: 1;
} __attribute__((packed)) ps2_config_byte;

typedef struct
{
    unsigned char system_reset: 1;
    unsigned char a20_gate: 1;
    unsigned char port_clock_2: 1;
    unsigned char port_data_2: 1;
    unsigned char output_buffer_full_byte1: 1;
    unsigned char output_buffer_full_byte2: 1;
    unsigned char port_clock_1: 1;
    unsigned char port_data_1: 1;
} __attribute__((packed)) ps2_output_port;

typedef struct
{
    union 
    {
        ps2_output_port port;
        ps2_config_byte conf;
        ps2_status_reg status;
        uint8_t data;
    }data;
}ps2_output;

typedef enum
{
    KEY_NULL = 256,
    KEY_ESCAPE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUALS, KEY_BACKSPACE,
    KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFTBRACE, KEY_RIGHTBRACE, KEY_ENTER,
    KEY_LEFTCTRL, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L,
    KEY_SEMICOLON, KEY_APOSTROPHE, KEY_GRAVE,
    KEY_LEFTSHIFT, KEY_BACKSLASH, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M,
    KEY_COMMA, KEY_DOT, KEY_SLASH, KEY_RIGHTSHIFT,
    KEY_KPASTERISK, KEY_LEFTALT, KEY_SPACE, KEY_CAPSLOCK,
    KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10,
    KEY_NUMLOCK, KEY_SCROLLLOCK,
    KEY_NP7, KEY_NP8, KEY_NP9, KEY_NPMINUS, KEY_NP4, KEY_NP5, KEY_NP6, KEY_NPPLUS, KEY_NP1, KEY_NP2, KEY_NP3, KEY_NP0, KEY_NPDOT,
    KEY_F11, KEY_F12
} KEY_CODE;

unsigned scancodes[] = 
{
    KEY_NULL, KEY_ESCAPE, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', KEY_BACKSPACE, 
    KEY_TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', KEY_ENTER, 
    KEY_LEFTCTRL, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 
    KEY_LEFTSHIFT, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', KEY_RIGHTSHIFT, 
    '*', KEY_LEFTALT, ' ', KEY_CAPSLOCK, 
    KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_NUMLOCK, KEY_SCROLLLOCK, 
    KEY_NP7, KEY_NP8, KEY_NP9, KEY_NPMINUS, KEY_NP4, KEY_NP5, KEY_NP6, KEY_NPPLUS, KEY_NP1, KEY_NP2, KEY_NP3, KEY_NP0, KEY_NPDOT,
    KEY_F11, KEY_F12
};

void irq_int_keyboard()
{
    unsigned char keyin = inb(PS2_PORT_DATA);
    unsigned key = scancodes[keyin];
    if (key < 256)
    {
        printf("%c", key);
        return;
    }
    else switch(key)
    {
        case KEY_ENTER:
            printf("\n");
        default:
            break;
    }
}

void initps2()
{
    // // TODO: ENSURE USB IS INITIALISED ON DODGY SYSTEMS,
    // //       ENSURE 8042 CONTROLLER EXISTS
    //
    // // disable ps2 devices
    // outb(PS2_PORT_COMMAND, 0xad); 
    // outb(PS2_PORT_COMMAND, 0xa7); 
    //
    // // flush output buffer
    // inb(PS2_PORT_DATA);
    // 
    // outb(PS2_PORT_COMMAND, 0x20); 
    // ps2_output config = {.data.data = inb(PS2_PORT_DATA)};
    // config.data.conf.port_int_1 = 0;
    // config.data.conf.port_int_2 = 0;
    // config.data.conf.port_translation = 0;
    // _Bool dual_channel = config.data.conf.port_clock_2; 
    // outb(PS2_PORT_COMMAND, 0x60);
    // outb(PS2_PORT_DATA, config.data.data);
    // if (dual_channel)
    // {
    //     outb(PS2_PORT_COMMAND, 0xa7);
    // }
    
    register_irq_handler(1, irq_int_keyboard);
    
}







