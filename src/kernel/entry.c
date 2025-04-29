// #include <limine.h>
// #include "incl/panic.h"
//
// #define REQUEST __attribute__((used, section(".requests"))) static volatile
//
// REQUEST LIMINE_BASE_REVISION(2);
//
// // REQUEST struct limine_framebuffer_request framebuffer_request = {
// //     .id = LIMINE_FRAMEBUFFER_REQUEST,
// //     .revision = 0
// // };
//
// __attribute__((used, section(".requests_start_marker")))
// static volatile LIMINE_REQUESTS_START_MARKER;
//
// __attribute__((used, section(".requests_end_marker")))
// static volatile LIMINE_REQUESTS_END_MARKER;
//
// void kernel_main();
//
// void _start(void)
// {
//     
//     if (!LIMINE_BASE_REVISION_SUPPORTED)
//         panicf("TODO: Limine base revision unsupported\n");
//
//     kernel_main();
//     panicf("returned from kernel_main()???\n");
// }
