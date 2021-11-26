// LICENSE HERE.

//
// svgame/player/client.h
//
// N&C SVGame: Client Header
// 
//
#ifndef __SVGAME_PLAYER_CLIENT_H__
#define __SVGAME_PLAYER_CLIENT_H__

class PlayerEntity;

qboolean SVG_ClientConnect(ServerEntity *serverEntity, char* userinfo);
void SVG_ClientDisconnect(ServerEntity *serverEntity);

void SVG_HUD_BeginIntermission(ServerEntity* target);

// Tosses the client weapon.
void SVG_TossClientWeapon(PlayerEntity* playerClient);

void SVG_ClientBegin(PlayerEntity* playerClient);
void SVG_ClientCommand(PlayerEntity* playerClient);
void SVG_ClientUserinfoChanged(ServerEntity* ent, char* userinfo);

//void SVG_ClientBeginServerFrame(ServerGameEntity* ent); // WID: Moved to gamemodes.
void SVG_ClientThink(PlayerEntity* playerClient, ClientMoveCommand* cmd);

void SVG_ClientEndServerFrames(void);

#endif // __SVGAME_PLAYER_CLIENT_H__