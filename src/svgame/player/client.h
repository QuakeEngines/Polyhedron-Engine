// LICENSE HERE.

//
// svgame/player/client.h
//
// N&C SVGame: Client Header
// 
//
#pragma once

class PlayerEntity;

qboolean SVG_ClientConnect(ServerEntity *serverEntity, char* userinfo);
void SVG_ClientDisconnect(ServerEntity *serverEntity);

void SVG_HUD_BeginIntermission(ServerEntity* target);

// Tosses the client weapon.
void SVG_TossClientWeapon(PlayerEntity* playerClient);

void SVG_ClientBegin(ServerEntity* playerClient);
void SVG_ClientCommand(ServerEntity* playerClient);
void SVG_ClientUserinfoChanged(ServerEntity* ent, char* userinfo);

//void SVG_ClientBeginServerFrame(SynchedEntityBase * ent); // WID: Moved to gamemodes.
void SVG_ClientThink(ServerEntity* playerClient, ClientMoveCommand* cmd);

void SVG_ClientEndServerFrames(void);