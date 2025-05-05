#pragma once

#include "coop/pc/gfx/gfx_rendering_api.h"
#include "coop/pc/gfx/gfx_window_manager.h"

#include "util.h"

COOP_FUNC_DECL(void, gfx_init, struct GfxWindowManagerAPI *wapi, struct GfxRenderingAPI *rapi, const char *window_title)