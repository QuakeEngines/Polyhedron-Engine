/*
// LICENSE HERE.

// InfoNull.cpp
*/

#include "../../g_local.h"
#include "../../effects.h"
#include "../../entities.h"
#include "../../utils.h"
#include "../../physics/stepmove.h"
#include "../../brushfuncs.h"

#include "../base/ServerGameEntity.h"

// This ServerEntity never spawns, and as such, no edicts will be wasted on it during spawn time
class InfoNull : public ServerGameEntity
{
public:
	DefineDummyMapClass( "info_null", InfoNull, ServerGameEntity );
};
