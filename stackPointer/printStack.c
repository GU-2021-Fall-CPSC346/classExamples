/* SeeSP: Print the value of the stack pointer.
 * Build: gcc SeeSP.c -o SeeSP
 *
 * Towel - 2017
 */
#include <stdio.h>
#include <inttypes.h>

int main(void)
{
    register uintptr_t sp asm ("sp");
    printf("SP: 0x%016" PRIxPTR "\n", sp);
    return 0;
}
