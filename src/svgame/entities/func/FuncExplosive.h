
#pragma once

class FuncExplosive : public ServerGameEntity {
public:
	FuncExplosive( ServerEntity* ServerEntity );
	virtual ~FuncExplosive() = default;

	DefineMapClass( "func_explosive", FuncExplosive, ServerGameEntity );

	// Spawn flags
	static constexpr int32_t SF_StartDeactivated = 1 << 0;
	static constexpr int32_t SF_Animated = 1 << 1;
	static constexpr int32_t SF_AnimatedFast = 1 << 2;

	void Spawn() override;

	void ExplosiveDeath( ServerGameEntity* inflictor, ServerGameEntity* attacker, int damage, const vec3_t& point );
	void ExplosiveUse( ServerGameEntity* other, ServerGameEntity* activator );
	void ExplosiveAppearUse( ServerGameEntity* other, ServerGameEntity* activator );
};
