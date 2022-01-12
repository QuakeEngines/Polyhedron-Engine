// License here.
// 
//
// ClientGameCore implementation.
#pragma once

#include "shared/interfaces/IClientGameExports.h"

//---------------------------------------------------------------------
// Client Game Core IMPLEMENTATION.
//---------------------------------------------------------------------
class ClientGameCore : public IClientGameExportCore {
public:
	// Initializes the client game.
	void Initialize() final;

	// Shuts down the client game.
	void Shutdown() final;

private:

};

