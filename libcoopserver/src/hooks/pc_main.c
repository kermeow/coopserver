#include "hooks/pc_main.h"
#include "coop/pc/platform.h" // IWYU pragma: keep
#include "offsets.h"
#include "util.h"
#include <stdio.h>

DETOUR_IMPL(pc_main__main, ADDRESS_PC_MAIN__MAIN)
int pc_main__main_hook(int argc, char *argv[]) {
	printf("libcoopserver main :)\n");

	char* exe_path = COOP_CALL(sys_exe_path_dir, ADDRESS_PLATFORM__SYS_EXE_PATH_DIR);
	

	return 0;
}