
#pragma once

class FuncExplosive : public SVGBaseEntity {
public:
	FuncExplosive( Entity* entity );
	virtual ~FuncExplosive() = default;

	DefineMapClass( "func_explosive", FuncExplosive, SVGBaseEntity );

	// Spawn flags
	static constexpr int32_t SF_StartDeactivated = 1 << 0;
	static constexpr int32_t SF_Animated = 1 << 1;
	static constexpr int32_t SF_AnimatedFast = 1 << 2;

	void Spawn() override;

	void ExplosiveDeath( SVGBaseEntity* inflictor, SVGBaseEntity* attacker, int damage, const vec3_t& point );
	void ExplosiveUse( SVGBaseEntity* other, SVGBaseEntity* activator );
	void ExplosiveAppearUse( SVGBaseEntity* other, SVGBaseEntity* activator );
};
