
#pragma once

class TargetSpeaker : public ServerGameEntity {
public:
	TargetSpeaker( ServerEntity* entity );
	virtual ~TargetSpeaker() = default;

	DefineMapClass( "target_speaker", TargetSpeaker, ServerGameEntity );
	
	static constexpr int32_t SF_LoopedOn = 1 << 0;
	static constexpr int32_t SF_LoopedOff = 1 << 1;
	static constexpr int32_t SF_Reliable = 1 << 2;

	void Spawn() override;
	void SpawnKey( const std::string& key, const std::string& value ) override;

	void SpeakerUse( ServerGameEntity* other, ServerGameEntity* activator );

private:
	std::string soundFile;
	float volume{ 1.0f };
	float attenuation{ 1.0f };
};
