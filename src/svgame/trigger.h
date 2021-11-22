// LICENSE HERE.

//
// svgame/weapons/blaster.h
//
//
// Contains blaster declarations.
//
#ifndef __SVGAME_TRIGER_H__
#define __SVGAME_TRIGER_H__

void InitTrigger(ServerEntity* self);
void multi_wait(ServerEntity* ent);
void multi_trigger(ServerEntity* ent);
void Use_Multi(ServerEntity* ent, ServerEntity* other, ServerEntity* activator);
void Touch_Multi(ServerEntity* self, ServerEntity* other, cplane_t* plane, csurface_t* surf);

#endif // __SVGAME_TRIGER_H__