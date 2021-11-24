/*
// LICENSE HERE.

//
// chasecamera.h
//
// The ChaseCamera does just what it says. It's used to chase a client.
// Think of spectator mode.
//
*/
#ifndef __SVGAME_CHASECAMERA_H__
#define __SVGAME_CHASECAMERA_H__

class ServerGameEntity;
class PlayerEntity;

void SVG_UpdateChaseCam(PlayerEntity* ent);
void SVG_ChaseNext(PlayerEntity* ent);
void SVG_ChasePrev(PlayerEntity* ent);
void SVG_GetChaseTarget(PlayerEntity* ent);

#endif