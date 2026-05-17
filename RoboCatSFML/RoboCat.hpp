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

	virtual void Update() override;

	void SimulateMovement(float inDeltaTime);
	void ProcessInput(float inDeltaTime, const InputState& inInputState) override;


	void			SetVelocity(const Vector3& inVelocity) { mVelocity = inVelocity; }
	const Vector3& GetVelocity()						const { return mVelocity; }

	virtual uint32_t Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;

protected:
	RoboCat();

private:


	void	AdjustVelocityByThrust(float inDeltaTime);

	Vector3				mVelocity;


	float				mMaxLinearSpeed;
	float				mMaxRotationSpeed;

	//bounce fraction when hitting various things
	float				mWallRestitution;
	float				mCatRestitution;

	float mMaxRotationSpeed;

protected:
	float mLastMoveTimestamp;
	float mThrustDir;
	bool mIsShooting;
};

typedef shared_ptr<RoboCat> RoboCatPtr;

