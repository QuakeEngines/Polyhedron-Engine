
#pragma once

class TargetEarthquake : public ServerGameEntity {
public:
	TargetEarthquake( ServerEntity* ServerEntity );
	virtual ~TargetEarthquake() = default;

	DefineMapClass( "target_earthquake", TargetEarthquake, ServerGameEntity );

	void Spawn() override;
	void SpawnKey( const std::string& key, const std::string& value ) override;

	void QuakeUse( ServerGameEntity* other, ServerGameEntity* activator );
	void QuakeThink();

private:
	float severity{ 200.0f };
	float duration{ 5.0f };
	float timeStamp{ 0.0f };
	float lastQuakeTime{ 0.0f };
};
