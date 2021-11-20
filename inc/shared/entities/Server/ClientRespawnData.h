// License here.
#pragma once

// Predef.
class ClientPersistentData;

//-------------------
// The ClientRespawnData struct is used to store specific information about
// respawning. Also maintains a member variable for data that has to stay
// persistent during mapchanges/respawns in a coop game.
//-------------------
class ClientRespawnData{
    ClientPersistentData persistentCoopRespawn;   // What to set client->persistent to on a respawn
    int32_t enterGameFrameNumber;       // level.frameNumber the client entered the game
    int32_t score;                      // frags, etc
    vec3_t commandViewAngles;           // angles sent over in the last command

    qboolean isSpectator;               // client is a isSpectator
};