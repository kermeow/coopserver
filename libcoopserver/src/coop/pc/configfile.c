#include "coop/pc/configfile.h"
#include <string.h>

const struct ConfigOption* find_option(const char* name) {
	for (int i = 0; i < optionsLen; i++) {
		const struct ConfigOption* option = &options[i];
		if (strcmp(option->name, name) == 0) return option;
	}
	return NULL;
}