
#pragma once

class TargetEarthquake : public SynchedEntityBase{
public:
	TargetEarthquake( ServerEntity* entity );
	virtual ~TargetEarthquake() = default;

	DefineMapClass( "target_earthquake", TargetEarthquake, SynchedEntityBase);

	void Spawn() override;
	void SpawnKey( const std::string& key, const std::string& value ) override;

	void QuakeUse( SynchedEntityBase * other, SynchedEntityBase * activator );
	void QuakeThink();

private:
	float severity{ 200.0f };
	float duration{ 5.0f };
	float timeStamp{ 0.0f };
	float lastQuakeTime{ 0.0f };
};
