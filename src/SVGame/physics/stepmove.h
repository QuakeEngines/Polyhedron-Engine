// LICENSE HERE.

//
// stepmove.h
//
//
//
#ifndef __SVGAME_PHYSICS_STEPMOVE_H__
#define __SVGAME_PHYSICS_STEPMOVE_H__

void SVG_StepMove_CheckGround(SynchedEntityBase * ent);
qboolean SVG_StepMove_CheckBottom(SynchedEntityBase * ent);
qboolean SVG_StepMove_Walk(SynchedEntityBase * ent, float yaw, float dist);

#endif // __SVGAME_PHYSICS_STEPMOVE_H__