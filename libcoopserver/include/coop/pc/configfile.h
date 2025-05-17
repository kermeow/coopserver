#pragma once

#include "offsets.h"
#include <stdbool.h>

enum ConfigOptionType {
    CONFIG_TYPE_BOOL,
    CONFIG_TYPE_UINT,
    CONFIG_TYPE_FLOAT,
    CONFIG_TYPE_BIND,
    CONFIG_TYPE_STRING,
    CONFIG_TYPE_U64,
    CONFIG_TYPE_COLOR,
};

struct ConfigOption {
    const char *name;
    enum ConfigOptionType type;
    union {
        bool *boolValue;
        unsigned int *uintValue;
        float* floatValue;
        char* stringValue;
        unsigned long* u64Value;
        unsigned char (*colorValue)[3];
    };
    int maxStringLength;
};

static const struct ConfigOption *options = (struct ConfigOption*)ADDRESS_CONFIG__OPTIONS;
static const unsigned int optionsLen = SIZEOF_CONFIG__OPTIONS / sizeof(struct ConfigOption);

// Custom
const struct ConfigOption* find_option(const char* name);