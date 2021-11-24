// LICENSE HERE.

//
// svgame/player/hud.h
//
// N&C SVGame: HUD Header
// 
//
#ifndef __SVGAME_PLAYER_HUD_H__
#define __SVGAME_PLAYER_HUD_H__

void HUD_MoveClientToIntermission(ServerEntity* client);
void SVG_HUD_SetClientStats(ServerEntity* ent);
void SVG_HUD_SetSpectatorStats(ServerEntity* ent);
void SVG_HUD_CheckChaseStats(ServerEntity* ent);
void HUD_ValidateSelectedItem(PlayerEntity* ent);
void SVG_HUD_GenerateDMScoreboardLayout(ServerGameEntity* client, ServerGameEntity* killer);

#endif // __SVGAME_PLAYER_HUD_H__