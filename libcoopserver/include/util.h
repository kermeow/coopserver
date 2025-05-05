#pragma once

#include "libdetour.h" // IWYU pragma: export

/*
 * Declare everything for a detour.
 */
#define DETOUR_DECL(FUNCRET, FUNCNAME, ...) \
DETOUR_DECL_TYPE(FUNCRET, FUNCNAME, __VA_ARGS__); \
extern detour_ctx_t FUNCNAME##_ctx; \
extern FUNCNAME##_t FUNCNAME; \
extern FUNCRET FUNCNAME##_hook(__VA_ARGS__);

/*
 * Implement everything for a detour except the hook.
 */
#define DETOUR_IMPL(FUNCNAME, ADDRESS) \
detour_ctx_t FUNCNAME##_ctx; \
FUNCNAME##_t FUNCNAME = (FUNCNAME##_t)ADDRESS;

/*
 * Declare a sm64coopdx function.
 */
#define COOP_FUNC_DECL(FUNCRET, FUNCNAME, ...) \
DETOUR_DECL_TYPE(FUNCRET, FUNCNAME, __VA_ARGS__);

/*
 * Implement a sm64coopdx function.
 */
#define COOP_CALL(FUNCNAME, ADDRESS, ...) ((FUNCNAME##_t)ADDRESS)(__VA_ARGS__)