#include "hooks/coopnet.h"
#include "coop/pc/network/coopnet.h"
#include "offsets.h"
#include "util.h"
#include <stdio.h>

DETOUR_IMPL(coopnet__coopnet_populate_description, ADDRESS_COOPNET__COOPNET_POPULATE_DESCRIPTION)
void coopnet__coopnet_populate_description_hook(void) {
	snprintf(sCoopNetDescription, MAX_COOPNET_DESCRIPTION_LENGTH, "fortnite balls");
}