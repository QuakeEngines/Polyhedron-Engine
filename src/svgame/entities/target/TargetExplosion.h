
#pragma once

class TargetExplosion : public SynchedEntityBase{
public:
	TargetExplosion( ServerEntity* entity );
	virtual ~TargetExplosion() = default;
	
	DefineMapClass( "target_explosion", TargetExplosion, SynchedEntityBase);

	void Spawn() override;

	void ExplosionUse( SynchedEntityBase * other, SynchedEntityBase * activator );
	void ExplosionThink();
};
