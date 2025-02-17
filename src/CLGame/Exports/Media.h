// License here.
// 
//
// ClientGameMedia implementation.
#pragma once

#include "Shared/Interfaces/IClientGameExports.h"

//---------------------------------------------------------------------
// Client Game Media IMPLEMENTATION.
//---------------------------------------------------------------------
class ClientGameMedia : public IClientGameExportMedia {
public:
    // Called upon initialization of the renderer.
    void Initialize() final;

    // This is called when the client stops the renderer.
    // Use this to unload remaining data.
    void Shutdown() final;

    // Called when the client wants to know the name of a custom load state.
    std::string GetLoadStateName(LoadState loadState) final;

    // This is called when the client starts, but also when the renderer has had
    // modified settings.
    //
    // It should register the basic screen media, 2D icons etc.
    void LoadScreen() final;

    // This is called when the client spawns into a server,
    //
    // It should register world related media here, such as:
    // Particles, (View-)Models, and Sounds.
    void LoadWorld() final;

private:
    // Load client models media here.
    void LoadModels();
    // Load client image media here.
    void LoadImages();
    // Load client sound media here.
    void LoadSounds();
};

