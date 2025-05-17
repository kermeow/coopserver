#include "hooks/configfile.h"
#include "hooks/coopnet.h"
#include "hooks/mods.h"
#include "hooks/pc_main.h"
#include "util.h"
#include <stdio.h>

void __attribute__((constructor)) dllmain(void) {
  printf("libcoopserver init\n");

  DETOUR_INSTALL(pc_main__main)
  DETOUR_INSTALL(configfile__save)
  DETOUR_INSTALL(coopnet__coopnet_populate_description)
  DETOUR_INSTALL(mods__mods_get_main_mod_name)
}