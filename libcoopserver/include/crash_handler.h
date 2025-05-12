#pragma once

#include <bits/types/siginfo_t.h>

void init_crash_handler();
void crash_handler(int sigNum, siginfo_t *info, void *context);