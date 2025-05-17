#include "hooks/mods.h"
#include "offsets.h"
#include "util.h"
#include <stdio.h>

DETOUR_IMPL(mods__mods_get_main_mod_name, ADDRESS_MODS__MODS_GET_MAIN_MOD_NAME)
void mods__mods_get_main_mod_name_hook(char *destination, unsigned int maxSize) {
	snprintf(destination, maxSize, "coopserver testing");
}