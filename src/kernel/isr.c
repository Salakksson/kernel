#include "isr.h"
#include "panic.h"

const char* exception_str[33] = 
{
	"division error",
	"debug",
	"unmaskable interrupt",
	"breakpoint",
	"overflow",
	"bound range exceeded",
	"invalid opcode",
	"device not available",
	"double fault",
	"coprocessor segment overrun (good luck)",
	"invalid tss",
	"segment not present",
	"stack segment fault",
	"general protection fault",
	"page fault",
	"reserved (good luck)",
	"x87 floating point exception",
	"alignment check",
	"machine check",
	"simd floating point exception",
	"virtualization exception",
	"control protection exception",
	"reserved (good luck)",
	"reserved (good luck)",
	"reserved (good luck)",
	"reserved (good luck)",
	"reserved (good luck)",
	"reserved (good luck)",
	"hypervisor injection exception",
	"vmm communication exception",
	"security exception",
	"reserved",
    "triple fault !!!!"
};

void print_interrupt_frame(interrupt_frame* frame)
{
    printf("rax: %lu\n", frame->rax);
    printf("rbx: %lu\n", frame->rbx);
    printf("rcx: %lu\n", frame->rcx);
    printf("rdx: %lu\n", frame->rdx);
    printf("rbp: %lu\n", frame->rbp);
    printf("rdi: %lu\n", frame->rdi);
    printf("rsi: %lu\n", frame->rsi);

    printf("rip: %p\n", frame->rip);
    printf("cs: %lu\n", frame->cs);
    printf("ss: %lu\n", frame->ss);
}

void global_isr_handler(interrupt_frame* frame)
{
    if (frame->vector > 32)
    {
        printf("Unimplemented: interrupts\n");
        return;
    }
    if (frame->procseg == 0 || 1) // currently all unhandled exceptions will panic, remove || 1 once processes are implemented  
    {
        // printf("procseg: %d\n", frame->procseg);
        panic_if(frame);
    }
    printf("impossible case?");
    panic_if(frame);
    printf("reached exception: '%s'\n", exception_str[frame->vector]);
    print_interrupt_frame(frame);
}

#define IMPLEMENT_INTERRUPTS
#include "idt.h"
#include "isr_all.h"

