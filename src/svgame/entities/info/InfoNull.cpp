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

#include "../base/SynchedEntityBase.h.h"

// This entity never spawns, and as such, no edicts will be wasted on it during spawn time
class InfoNull : public SynchedEntityBase.h
{
public:
	DefineDummyMapClass( "info_null", InfoNull, SynchedEntityBase);
};
