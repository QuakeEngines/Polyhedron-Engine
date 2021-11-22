
#pragma once

class FuncWall : public ServerGameEntity {
public:
	FuncWall( ServerEntity* entity );
	virtual ~FuncWall() = default;

	DefineMapClass( "func_wall", FuncWall, ServerGameEntity );

	// Spawn flags
	static constexpr int32_t SF_TriggerSpawn = 1 << 0;
	static constexpr int32_t SF_Toggle = 1 << 1;
	static constexpr int32_t SF_StartOn = 1 << 2;
	static constexpr int32_t SF_Animated = 1 << 3;
	static constexpr int32_t SF_AnimatedFast = 1 << 4;

	void Spawn() override;

	void WallUse( ServerGameEntity* other, ServerGameEntity* activator );
};
