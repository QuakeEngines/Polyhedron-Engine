/*
// LICENSE HERE.

//
// SVGBaseMover.h
//
// Base move class, for buttons, platforms, anything that moves based on acceleration
// OR, stepmoves.
//
*/
#pragma once

class BaseTrigger;

using PushMoveEndFunction = void(EntityBase *);


constexpr uint32_t PlatLowTrigger = 1U;
struct MoverState
{
    static constexpr uint32_t Top = 0U;
    static constexpr uint32_t Bottom = 1U;
    static constexpr uint32_t Up = 2U;
    static constexpr uint32_t Down = 3U;
};

//-------------------
// Contains data for keeping track of velocity based moving entities.
// (In other words, entities that aren't a: Client or AI Player.
//-------------------
struct PushMoveInfo {
    // fixed data
    vec3_t startOrigin;
    vec3_t startAngles;
    vec3_t endOrigin;
    vec3_t endAngles;

    int32_t startSoundIndex;
    int32_t middleSoundIndex;
    int32_t endSoundIndex;

    float acceleration;
    float speed;
    float deceleration;
    float distance;

    float wait;

    // state data
    int32_t state;
    vec3_t dir;
    float currentSpeed;
    float moveSpeed;
    float nextSpeed;
    float remainingDistance;
    float deceleratedDistance;
    //void (*OnEndFunction)(ServerEntity *);
    PushMoveEndFunction* OnEndFunction;
};

class SVGBaseMover : public BaseTrigger {
public:
    //
    // Constructor/Deconstructor.
    //
    SVGBaseMover(ServerEntity* svEntity);
    virtual ~SVGBaseMover();

    DefineAbstractClass( SVGBaseMover, BaseTrigger );

    //
    // Interface functions. 
    //
    virtual void Precache() override;    // Precaches data.
    virtual void Spawn() override;       // Spawns the entity.
    virtual void Respawn() override;     // Respawns the entity.
    virtual void PostSpawn() override;   // PostSpawning is for handling entity references, since they may not exist yet during a spawn period.
    virtual void Think() override;       // General entity thinking routine.

    virtual void SpawnKey(const std::string& key, const std::string& value)  override;

    //
    // Pusher functions.
    //
    virtual void SetMoveDirection(const vec3_t& angles, qboolean resetAngles = false);

    //
    // Get/Set
    //
    // @returns The current acceleration.
    inline float GetAcceleration() override {
        return acceleration;
    }
    // @returns The current deceleration.
    inline float GetDeceleration() override {
        return deceleration;
    }
    // @returns The current speed.
    inline float GetSpeed() override {
        return speed;
    }
    // @returns The meant to become end position.
    const inline vec3_t& GetEndPosition() override {
        return endPosition;
    }
    // @returns The start position.
    const inline vec3_t& GetStartPosition() override {
        return startPosition;
    }
    // @returns The lip (left-over bit after moving.)
    const inline float& GetLip() {
        return lip;
    }

    //-----------------------------------------------------
    //
    // Set Functions.
    //
    //-----------------------------------------------------
    // @set The acceleration.
    inline void SetAcceleration(const float& acceleration) {
        this->acceleration = acceleration;
    }
    // @set the Deceleration.
    inline void SetDeceleration(const float& deceleration) {
        this->deceleration = deceleration;
    }
    // @set The speed.
    inline void SetSpeed(const float &speed) {
        this->speed = speed;
    }
    // @set the (wished for) end position.
    inline void SetEndPosition(const vec3_t& endPosition) {
        this->endPosition = endPosition;
    }
    // @set the start position.
    inline void SetStartPosition(const vec3_t& startPosition) {
        this->startPosition = startPosition;
    }
    // @set the lip.
    inline void SetLip( const float& lip ) {
        this->lip = lip;
    }

protected:
    // Calculates and returns the destination point
    // ASSUMES: startPosition and moveDirection are set properly
    vec3_t      CalculateEndPosition();

    // Swaps startPosition and endPosition, using the origin as an intermediary
    void        SwapPositions();

    // Brush movement methods
    void		BrushMoveDone();
    void		BrushMoveFinal();
    void		BrushMoveBegin();
    void		BrushMoveCalc( const vec3_t& destination, PushMoveEndFunction* function );
    // Same but for angular movement
    void        BrushAngleMoveDone();
    void        BrushAngleMoveFinal();
    void        BrushAngleMoveBegin();
    void        BrushAngleMoveCalc( PushMoveEndFunction* function );
    // Accelerative movement
    void        BrushAccelerateCalc();
    void        BrushAccelerate();
    void        BrushAccelerateThink();

    float       CalculateAccelerationDistance( float targetSpeed, float accelerationRate );

protected:

    //
    // Other base entity members. (These were old fields in edict_T back in the day.)
    //
    // The speed that this objects travels at.     
    float speed;
    // Acceleration speed.
    float acceleration;
    // Deceleration speed.
    float deceleration;
    // Direction of which to head down to when moving.
    vec3_t moveDirection;
    // Well, positions...
    //vec3_t position1, position2;
    // Position at where to start moving this thing from.
    vec3_t startPosition;
    // Position at where to end this thing from moving at all.
    vec3_t endPosition;
    // BaseMover moveInfo.
    PushMoveInfo moveInfo;
    // How far away to stop, from the destination
    float		lip{ 0.0f };
    // Kill target when triggered.
    //std::string killTargetStr;

    // Message when triggered.
    //std::string messageStr;

    // Master trigger entity.
    //std::string masterStr;

    // Timestamp that the trigger has been called at.
    //
    // ServerEntity pointers.
    // 

};