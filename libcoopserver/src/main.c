#include "hooks/pc_main.h"
#include "libdetour.h"
#include <stdio.h>

void __attribute__ ((constructor)) dllmain(void) {
    printf("libcoopserver init\n");

	detour_init(&pc_main__main_ctx, pc_main__main, pc_main__main_hook);
	detour_enable(&pc_main__main_ctx);
}