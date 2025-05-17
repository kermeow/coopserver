#include "server/server_main.h"

#include "coop/game/game_init.h" // IWYU pragma: keep
#include "coop/pc/configfile.h"
#include "coop/pc/djui.h"        // IWYU pragma: keep
#include "coop/pc/fs.h"          // IWYU pragma: keep
#include "coop/pc/gfx/gfx_pc.h"  // IWYU pragma: keep
#include "coop/pc/network/network.h"
#include "coop/pc/pc_main.h"     // IWYU pragma: keep
#include "coop/pc/platform.h"    // IWYU pragma: keep
#include "coop/pc/rom_checker.h" // IWYU pragma: keep
#include "crash_handler.h"
#include "offsets.h"
#include "util.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int server_main(int argc, char *argv[]) {
  printf("libcoopserver main\n");

  init_crash_handler();

  // Mount FS in managed folder
  char *exe_path =
      COOP_CALL(sys_exe_path_dir, ADDRESS_PLATFORM__SYS_EXE_PATH_DIR);
  bool fs_mounted = COOP_CALL(fs_init, ADDRESS_FS__FS_INIT, exe_path);

  if (!fs_mounted) {
    printf("fs_init failed");
    return 1;
  }

  // Check for ROM
  bool valid_rom =
      COOP_CALL(main_rom_handler, ADDRESS_ROM_CHECKER__MAIN_ROM_HANDLER);
  if (!valid_rom) {
    printf("Couldn't find ROM");
    return 1;
  }

  // Enforce headless APIs
  memcpy((void *)ADDRESS_GFX__GFX_SDL, (void *)ADDRESS_GFX__GFX_DUMMY_WM,
         SIZEOF_GFX__GFX_WAPI);
  memcpy((void *)ADDRESS_GFX__GFX_OPENGL, (void *)ADDRESS_GFX__GFX_DUMMY_R,
         SIZEOF_GFX__GFX_RAPI);

  // Init
  COOP_CALL(gfx_init, ADDRESS_GFX__GFX_INIT, (void *)ADDRESS_GFX__GFX_SDL,
            (void *)ADDRESS_GFX__GFX_OPENGL, "");
  COOP_CALL(main_game_init, ADDRESS_PC_MAIN__MAIN_GAME_INIT, NULL);
  COOP_CALL(thread5_game_loop, ADDRESS_GAME__THREAD5_GAME_LOOP, NULL);

  *(void**)ADDRESS_AUDIO__AUDIO_API = (void*)ADDRESS_AUDIO__AUDIO_NULL;

  COOP_CALL(djui_init, ADDRESS_DJUI__DJUI_INIT);
  COOP_CALL(djui_unicode_init, ADDRESS_DJUI__DJUI_UNICODE_INIT);
  COOP_CALL(djui_init_late, ADDRESS_DJUI__DJUI_INIT_LATE);

  *find_option("uncapped_framerate")->boolValue = false;
  *find_option("frame_limit")->uintValue = 30;
  const struct ConfigOption* playerNameOpt = find_option("coop_player_name");
  snprintf(playerNameOpt->stringValue, playerNameOpt->maxStringLength, "coopserver test");

  COOP_CALL(network_set_system, ADDRESS_NETWORK__NETWORK_SET_SYSTEM, NS_COOPNET);
  COOP_CALL(network_init, ADDRESS_NETWORK__NETWORK_INIT, NT_SERVER, false);

  while (true) {
    COOP_CALL(produce_one_frame, ADDRESS_PC_MAIN__PRODUCE_ONE_FRAME);
  }

  return 0;
}