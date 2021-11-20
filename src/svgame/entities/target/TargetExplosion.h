
#pragma once

class TargetExplosion : public ServerGameEntity {
public:
	TargetExplosion( ServerEntity* ServerEntity );
	virtual ~TargetExplosion() = default;
	
	DefineMapClass( "target_explosion", TargetExplosion, ServerGameEntity );

	void Spawn() override;

	void ExplosionUse( ServerGameEntity* other, ServerGameEntity* activator );
	void ExplosionThink();
};
