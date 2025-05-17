#pragma once

#include "util.h"

enum NetworkType {
    NT_NONE,
    NT_SERVER,
    NT_CLIENT
};

enum NetworkSystemType {
    NS_SOCKET,
    NS_COOPNET,
    NS_MAX,
};

COOP_FUNC_DECL(void, network_set_system, enum NetworkSystemType nsType);
COOP_FUNC_DECL(bool, network_init, enum NetworkType inNetworkType, bool reconnecting);