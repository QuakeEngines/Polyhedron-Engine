// LICENSE HERE.

//
// svgame/player/client.h
//
// N&C SVGame: Client Header
// 
//
#ifndef __SVGAME_PLAYER_CLIENT_H__
#define __SVGAME_PLAYER_CLIENT_H__

class PlayerClient;

qboolean SVG_ClientConnect(ServerEntity* ent, char* userinfo);
void SVG_ClientDisconnect(ServerEntity* ent);

void SVG_HUD_BeginIntermission(ServerEntity* targ);

// Tosses the client weapon.
void SVG_TossClientWeapon(PlayerClient* playerClient);

void SVG_ClientBegin(ServerEntity* ent);
void SVG_ClientCommand(ServerEntity* ent);
void SVG_ClientUserinfoChanged(ServerEntity* ent, char* userinfo);

//void SVG_ClientBeginServerFrame(SVGBaseEntity* ent); // WID: Moved to gamemodes.
void SVG_ClientThink(ServerEntity* ent, ClientMoveCommand* cmd);

void SVG_ClientEndServerFrames(void);

#endif // __SVGAME_PLAYER_CLIENT_H__