ENTRY(start)

/* PHDRS */
/* { */
/*     headers PT_PHDR PHDRS; */
/*     text    PT_LOAD FILEHDR PHDRS; */
/*     rodata  PT_LOAD; */
/*     data    PT_LOAD; */
/*     dynamic PT_DYNAMIC; */
/* } */

SECTIONS
{
    /* . = 0xffffffff80000000 + SIZEOF_HEADERS; */
    /*  */
    /* .text :  */
    /* { */
    /*     *(.text .text.*) */
    /* } :text */
    /**/
    /* . = ALIGN(CONSTANT(MAXPAGESIZE)); */
    /* .rodata :  */
    /* { */
    /*     *(.rodata .rodata.*) */
    /* } :rodata */
    /**/
    /* . = ALIGN(CONSTANT(MAXPAGESIZE)); */
    /* .data :  */
    /* { */
    /*     *(.data .data.*) */
    /*     KEEP(*(.requests_start_marker)) */
    /*     KEEP(*(.requests)) */
    /*     KEEP(*(.requests_end_marker)) */
    /* } :data */
    /**/
    /* /* Dynamic section for relocations, both in its own PHDR and inside data PHDR. */ 
    /* .dynamic :  */
    /* { */
    /*     *(.dynamic) */
    /* } :data :dynamic */
    /**/
    /* /* NOTE: .bss needs to be the last thing mapped to :data, otherwise lots of */ 
    /* /* unnecessary zeros will be written to the binary. */ 
    /* /* If you need, for example, .init_array and .fini_array, those should be placed */ 
    /* /* above this. */ 
    /* .bss :  */
    /* { */
    /*     *(.bss .bss.*) */
    /*     *(COMMON) */
    /* } :data */
    /**/
    /* /* Discard .note.* and .eh_frame* since they may cause issues on some hosts. */ 
    /* /* Also discard the program interpreter section since we do not need one. This is */
    /* /* more or less equivalent to the --no-dynamic-linker linker flag, except that it */ 
    /* /* works with ld.gold. */ 
    /* /DISCARD/ : { */
    /*     *(.eh_frame*) */
    /*     *(.note .note.*) */
    /*     *(.interp) */
    /* } */

    /* if using multiboot: */
    . = 1M;
    .boot :
    {
        KEEP(*(.multiboot_header))
    }
    .text :
    {
        *(.text)
    }

}
