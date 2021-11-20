#pragma once

class ServerGameEntity;

//=============================================
// FuncTimer
// 
// A utility ServerEntity for mappers, that triggers its targets
// every "wait" seconds + "random" if specified.
// 
// NOTE: pausetime is currently always 0
//=============================================
class FuncTimer : public ServerGameEntity {
public:
	FuncTimer( ServerEntity* ServerEntity );
	virtual ~FuncTimer() = default;

	DefineMapClass( "func_timer", FuncTimer, ServerGameEntity );

	// Spawn flags
	static constexpr int32_t SF_StartOn = 1 << 0;

	void Spawn() override;
	void SpawnKey( const std::string& key, const std::string& value ) override;

	void TimerThink();
	void TimerUse( ServerGameEntity* other, ServerGameEntity* activator );

protected:
	float randomTime{ 0.0f };
};
