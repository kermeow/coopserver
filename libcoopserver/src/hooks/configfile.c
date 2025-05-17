#include "hooks/configfile.h"
#include "offsets.h"
#include "util.h"

DETOUR_IMPL(configfile__save, ADDRESS_CONFIGFILE__CONFIGFILE_SAVE)
void configfile__save_hook(const char *filename) {
	return;
}