#include "keyboard.h"
#include "ports.h"

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
    unsigned char system_reset: 1;
    unsigned char a20_gate: 1;
    unsigned char port_clock_2: 1;
    unsigned char port_data_2: 1;
    unsigned char output_buffer_full_byte1: 1;
    unsigned char output_buffer_full_byte2: 1;
    unsigned char port_clock_1: 1;
    unsigned char port_data_1: 1;
} __attribute__((packed)) ps2_config_byte;

typedef struct
{
    union 
    {
        ps2_config_byte conf;
        ps2_status_reg status;
        uint8_t data;
    }data;
}ps2_output;

void initps2()
{
    // TODO: ENSURE USB IS INITIALISED ON DODGY SYSTEMS,
    //       ENSURE 8042 CONTROLLER EXISTS

    // disable ps2 devices
    printf("attempting to send commands to ps2 controller\n");
    port_outb(PS2_PORT_COMMAND, 0xad); 
    port_outb(PS2_PORT_COMMAND, 0xa7); 

    // flush output buffer
    printf("attempting to clear ps2 controller buffer\n");
    port_inb(PS2_PORT_DATA);
    
    printf("attempting to read ps2 config byte\n");
    port_outb(PS2_PORT_COMMAND, 0x20); 
    ps2_output old = {.data.data = port_inb(PS2_PORT_DATA)};
    printf("ps2 config byte: 0x%x\n", old.data.data);

}
