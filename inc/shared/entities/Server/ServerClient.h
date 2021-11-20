// License here.
#pragma once

// Shared.
#include "shared/shared.h"

// Other.
#include "shared/list.h"
#include "sharedgame/pmove.h"
#include "sharedgame/protocol.h"

// Predefine.
struct PlayerState;

class ServerClient {
public:
    // The client's current player state. (Communicated by server to clients.)
    PlayerState playerState;

    // Current ping.
    int32_t ping;

    // Client index number.
    int32_t clientNumber;
};