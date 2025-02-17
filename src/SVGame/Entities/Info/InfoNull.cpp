/*
// LICENSE HERE.

// InfoNull.cpp
*/

#include "../../ServerGameLocal.h"
#include "../../Effects.h"
#include "../../Entities.h"
#include "../../Utilities.h"
#include "../../Physics/StepMove.h"
#include "../../BrushFunctions.h"

#include "../Base/SVGBaseEntity.h"

// This entity never spawns, and as such, no edicts will be wasted on it during spawn time
class InfoNull : public SVGBaseEntity
{
public:
	DefineDummyMapClass( "info_null", InfoNull, SVGBaseEntity );
};
