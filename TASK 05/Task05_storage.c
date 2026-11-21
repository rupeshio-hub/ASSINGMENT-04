#include <stdio.h>
#include "token.h"

int main(void) {
    printf("static: %d %d %d\n", next_token(), next_token(), next_token());
    printf("auto  : %d %d %d\n", auto_token(), auto_token(), auto_token());

    printf("extern: ");
    for (int i = 0; i < 3; i++) printf("%d ", next_extern_token());
    putchar('\n');

    /* register is a storage-class hint for a frequently used local variable.
       Its address is intentionally not taken. */
    printf("register loop: ");
    for (register int i = 1; i <= 3; i++) printf("%d ", i);
    putchar('\n');

    /* Independent counters can be maintained by callers. */
    int veg_counter = 1000, nonveg_counter = 2000;
    printf("caller counters: veg=%d, non-veg=%d\n",
           ++veg_counter, ++nonveg_counter);
    return 0;
}
