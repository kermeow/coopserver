#include "hooks/pc_main.h"

#include "server/server_main.h"

#include "offsets.h"
#include "util.h"

DETOUR_IMPL(pc_main__main, ADDRESS_PC_MAIN__MAIN)
int pc_main__main_hook(int argc, char *argv[]) {
  return server_main(argc, argv);
}