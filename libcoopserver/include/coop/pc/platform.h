#pragma once

#include "util.h"

// typedef char*(*sys_user_path_t)(void);
// extern sys_user_path_t sys_user_path;

COOP_FUNC_DECL(char*, sys_user_path, void)
COOP_FUNC_DECL(char*, sys_resource_path, void)
COOP_FUNC_DECL(char*, sys_exe_path_dir, void)
COOP_FUNC_DECL(char*, sys_exe_path_file, void)
COOP_FUNC_DECL(char*, sys_file_extension, const char *fpath)
COOP_FUNC_DECL(char*, sys_file_name, const char *fpath)