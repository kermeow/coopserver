#include "hooks/pc_main.h"

#include "coop/game/game_init.h"
#include "coop/pc/djui.h"
#include "coop/pc/fs.h"         // IWYU pragma: keep
#include "coop/pc/gfx/gfx_pc.h" // IWYU pragma: keep
#include "coop/pc/pc_main.h"
#include "coop/pc/platform.h"   // IWYU pragma: keep
#include "coop/pc/rom_checker.h"
#include "offsets.h"
#include "util.h"

#include <stdio.h>
#include <string.h>

DETOUR_IMPL(pc_main__main, ADDRESS_PC_MAIN__MAIN)
int pc_main__main_hook(int argc, char *argv[]) {
  printf("libcoopserver main\n");

  // Mount FS in managed folder
  char *exe_path =
      COOP_CALL(sys_exe_path_dir, ADDRESS_PLATFORM__SYS_EXE_PATH_DIR);
  bool fs_mounted = COOP_CALL(fs_init, ADDRESS_FS__FS_INIT, exe_path);

  if (!fs_mounted) {
    printf("fs_init failed");
    return 1;
  }

  // Check for ROM
  bool valid_rom = COOP_CALL(main_rom_handler, ADDRESS_ROM_CHECKER__MAIN_ROM_HANDLER);
  if (!valid_rom) {
    printf("Couldn't find ROM");
    return 1;
  }

  // Enforce headless APIs
  memcpy((void *)ADDRESS_GFX__GFX_SDL, (void *)ADDRESS_GFX__GFX_DUMMY_WM,
         SIZEOF_GFX__GFX_WAPI);
  memcpy((void *)ADDRESS_GFX__GFX_OPENGL,
         (void *)ADDRESS_GFX__GFX_DUMMY_R, SIZEOF_GFX__GFX_RAPI);

  // Init
  COOP_CALL(gfx_init, ADDRESS_GFX__GFX_INIT,
            (void*)ADDRESS_GFX__GFX_SDL, (void*)ADDRESS_GFX__GFX_OPENGL,
            "");
  COOP_CALL(main_game_init, ADDRESS_PC_MAIN__MAIN_GAME_INIT, NULL);
  COOP_CALL(thread5_game_loop, ADDRESS_GAME__THREAD5_GAME_LOOP, NULL);

  memset((void *)ADDRESS_AUDIO__AUDIO_API, ADDRESS_AUDIO__AUDIO_API, sizeof(void*));

  COOP_CALL(djui_init, ADDRESS_DJUI__DJUI_INIT);
  COOP_CALL(djui_unicode_init, ADDRESS_DJUI__DJUI_UNICODE_INIT);
  COOP_CALL(djui_init_late, ADDRESS_DJUI__DJUI_INIT_LATE);

  return 0;
}