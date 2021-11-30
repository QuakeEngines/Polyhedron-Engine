/*
// LICENSE HERE.

//
// ChaseCamera.h
//
// The ChaseCamera does just what it says. It's used to chase a client.
// Think of spectator mode.
//
*/
#pragma once

class SynchedEntityBase;
class PlayerEntity;

void SVG_UpdateChaseCam(PlayerEntity* ent);
void SVG_ChaseNext(PlayerEntity* ent);
void SVG_ChasePrev(PlayerEntity* ent);
void SVG_GetChaseTarget(PlayerEntity* ent);