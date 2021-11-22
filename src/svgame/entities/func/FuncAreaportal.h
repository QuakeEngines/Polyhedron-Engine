#pragma once

class ServerGameEntity;

//=============================================
// FuncAreaportal
// 
// This is a non-visible object that divides the world into
// areas that are seperated when this portal is not activated.
// Usually enclosed in the middle of a door.
//=============================================
class FuncAreaportal : public ServerGameEntity {
public:
	FuncAreaportal( ServerEntity* entity );
	virtual ~FuncAreaportal() = default;

	DefineMapClass( "func_areaportal", FuncAreaportal, ServerGameEntity );

	void Spawn() override;
	void SpawnKey( const std::string& key, const std::string& value ) override;

	// For triggering by mappers
	void PortalUse( ServerGameEntity* other, ServerGameEntity* activator );
	// For doors and other autonomous entities
	void ActivatePortal( bool open );

protected:
	bool turnedOn{ false };
};
