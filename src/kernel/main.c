#include "tty.h"

void kernel_main()
{
    tty_clear();
    tty_colour(YELLOW, BLUE);
    puts("1\n2\n3\n4\n5\n");
    tty_colour(MAGENTA, WHITE);
    puts("6\n7\n8\n9\n10\n11\n12\n13\n14\n");
    puts("15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26");

    for(;;);
}
