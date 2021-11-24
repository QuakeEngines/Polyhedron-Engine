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
class ServerGameEntity;

//
// Debris.
//
void SVG_ThrowDebris(ServerGameEntity* self, const char* modelname, float speed, const vec3_t& origin);

//
// Explosions.
//
void SVG_BecomeExplosion1(ServerGameEntity* self);
void SVG_BecomeExplosion2(ServerGameEntity* self);

//
// Gibs.
//
void SVG_ThrowClientHead(PlayerEntity* self, int damage);
void SVG_ThrowGib(ServerGameEntity* self, const char* gibname, int damage, int type);

#endif // __SVGAME_PLAYER_WEAPONS_H__