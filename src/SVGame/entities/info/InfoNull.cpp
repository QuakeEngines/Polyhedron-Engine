/*
// LICENSE HERE.

// InfoNull.cpp
*/

#include "../../ServerGameLocal.h"
#include "../../Effects.h"
#include "../../Entities.h"
#include "../../Utilities.h"
#include "../../Physics/Stepmove.h"

#include "../base/PrivateEntityBase.h"

// This entity never spawns, and as such, no edicts will be wasted on it during spawn time
class InfoNull : public PrivateEntityBase
{
public:
	DefineDummyMapClass( "info_null", InfoNull, PrivateEntityBase);
};
