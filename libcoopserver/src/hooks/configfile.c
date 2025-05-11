#include "hooks/configfile.h"
#include "offsets.h"
#include "util.h"

DETOUR_IMPL(configfile__save, ADDRESS_CONFIGFILE__SAVE)
void configfile_save_hook(const char *filename) {
	return;
}