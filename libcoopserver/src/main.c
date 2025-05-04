#include <stdio.h>

void __attribute__ ((constructor)) dllmain(void) {
    printf("libcoopserver init");

	
}