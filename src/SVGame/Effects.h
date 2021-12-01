// LICENSE HERE.

//
// effects.h
//
//
// Gibs, to turning things into explosions.
//
#ifndef __SVGAME_EFFECTS_H__
#define __SVGAME_EFFECTS_H__

//
// Forward declaration.
//
class SynchedEntityBase;

//
// Debris.
//
void SVG_ThrowDebris(SynchedEntityBase * self, const char* modelname, float speed, const vec3_t& origin);

//
// Explosions.
//
void SVG_BecomeExplosion1(SynchedEntityBase * self);
void SVG_BecomeExplosion2(SynchedEntityBase * self);

//
// Gibs.
//
void SVG_ThrowClientHead(PlayerEntity* self, int damage);
void SVG_ThrowGib(SynchedEntityBase * self, const char* gibname, int damage, int type);

#endif // __SVGAME_PLAYER_WEAPONS_H__