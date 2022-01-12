#pragma once

class SVGBaseEntity;
class SVGBaseMover;
class FuncDoor;

class FuncDoorRotating : public FuncDoor {
public:
	FuncDoorRotating( Entity* entity );
	virtual ~FuncDoorRotating() = default;

	DefineMapClass( "func_door_rotating", FuncDoorRotating, FuncDoor );

	void Spawn() override;
	void SpawnKey( const std::string& key, const std::string& value ) override;

protected:
	void DoGoUp() override;
	void DoGoDown() override;

protected:
	float distance{};
};
