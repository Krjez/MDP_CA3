/*
*  Provided in class, edited by:
*  Petr Sulc - GD4b - D00261476
*  Jakub Polacek - GD4b - D00260171
*/

class RoboCat : public GameObject, public Pawn
{
public:
	CLASS_IDENTIFICATION('RCAT', GameObject)

	enum ECatReplicationState
	{
		ECRS_Pose = 1 << 0,
		ECRS_Color = 1 << 1,
		ECRS_PlayerId = 1 << 2,

		ECRS_AllState = ECRS_Pose | ECRS_Color | ECRS_PlayerId
	};


	static	GameObject* StaticCreate() { return new RoboCat(); }

	virtual uint32_t GetAllStateMask()	const override { return ECRS_AllState; }

	virtual	Pawn* AsPlayerPawn() override { return this; }

	virtual void Update() override { };

	void ProcessInput(float inDeltaTime, const InputState& inInputState) override;

	PhysicsBody& GetPhysics() { return m_physics_body; }

	virtual uint32_t Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;

protected:
	RoboCat();

private:
	PhysicsBody m_physics_body;
	CircleCollider m_collider;

	float mMaxRotationSpeed;

protected:
	float mLastMoveTimestamp;
	float mThrustDir;
};

typedef shared_ptr<RoboCat> RoboCatPtr;

