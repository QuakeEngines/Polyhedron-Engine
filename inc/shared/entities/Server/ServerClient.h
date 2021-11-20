// License here.
#pragma once

#include "shared/list.h"
#include "sharedgame/pmove.h"
#include "sharedgame/protocol.h"

#include "shared/entities/Server/ClientPersistentData.h"
#include "shared/entities/Server/ClientRespawnData.h"

class ServerClient {
public:
    // The client's current player state. (Communicated by server to clients.)
    PlayerState playerState;

    // Current ping.
    int32_t ping;

    // Client index number.
    int32_t clientNumber;
};