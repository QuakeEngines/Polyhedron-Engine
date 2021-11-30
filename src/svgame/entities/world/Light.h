/*
// LICENSE HERE.

//
// Light.h
//
// Light entity definition.
//
*/
#ifndef __SVGAME_ENTITIES_LIGHT_H__
#define __SVGAME_ENTITIES_LIGHT_H__

class BaseTrigger;

enum LightState : uint32_t {
    Off = 1,
    On = 2,
};

class Light : public BaseTrigger {
public:
    // Constructor/Deconstructor.
    Light(ServerEntity* svEntity);
    virtual ~Light();

    DefineMapClass( "light", Light, BaseTrigger );

    //
    // Interface functions. 
    //
    void Precache() override;    // Precaches data.
    void Spawn() override;       // Spawns the entity.
    void PostSpawn() override;   // PostSpawning is for handling entity references, since they may not exist yet during a spawn period.
    void Think() override;       // General entity thinking routine.

    void SpawnKey(const std::string& key, const std::string& value) override;

    //
    // Get/Set
    // 
    // 'customLightStyle'.
    inline const char *GetCustomLightStyle() {
        return customLightStyle.c_str();
    }
    void SetCustomLightStyle(const std::string& lightStyle) {
        this->customLightStyle = lightStyle;
    }

    //
    // Callback functions.
    //
    void LightUse(SynchedEntityBase * other, SynchedEntityBase * activator);
    void LightThink(void);

private:
    // Custom lightstyle string.
    std::string customLightStyle;

    // Light State flags. (Is it currently off, or triggered?)
    uint32_t lightState;
};


#pragma once

class SynchedEntityBase.h;

class PathCorner : public SynchedEntityBase{
public:
    PathCorner(ServerEntity* entity);
    virtual ~PathCorner() = default;

    DefineMapClass("path_corner", PathCorner, SynchedEntityBase.h);

    const vec3_t	BboxSize = vec3_t(8.0f, 8.0f, 8.0f);

    // Spawnflags
    static constexpr int32_t SF_Teleport = 1 << 0;

    void			Spawn() override;
    void			SpawnKey(const std::string& key, const std::string& value) override;

    // For AI
    virtual void	OnReachedCorner(SynchedEntityBase * traveler);

    inline const char* GetPathTarget() override {
        return pathTarget.c_str();
    }

private:
    std::string		pathTarget;
};

#endif // __SVGAME_ENTITIES_LIGHT_H__