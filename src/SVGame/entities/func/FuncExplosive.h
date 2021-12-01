
#pragma once

class FuncExplosive : public SynchedEntityBase{
public:
	FuncExplosive( ServerEntity* entity );
	virtual ~FuncExplosive() = default;

	DefineMapClass( "func_explosive", FuncExplosive, SynchedEntityBase);

	// Spawn flags
	static constexpr int32_t SF_StartDeactivated = 1 << 0;
	static constexpr int32_t SF_Animated = 1 << 1;
	static constexpr int32_t SF_AnimatedFast = 1 << 2;

	void Spawn() override;

	void ExplosiveDeath( SynchedEntityBase * inflictor, SynchedEntityBase * attacker, int damage, const vec3_t& point );
	void ExplosiveUse( SynchedEntityBase * other, SynchedEntityBase * activator );
	void ExplosiveAppearUse( SynchedEntityBase * other, SynchedEntityBase * activator );
};
