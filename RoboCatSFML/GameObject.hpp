#pragma once
#define CLASS_IDENTIFICATION(in_code, in_class) \
enum {kClassId = in_code}; \
virtual uint32_t GetClassId() const {return kClassId;} \
static GameObject* CreateInstance() { return static_cast<GameObject*>(new in_class());}\

class Pawn;

class GameObject
{
public:
	CLASS_IDENTIFICATION('GOBJ', GameObject)

		enum EGameObjectReplicationState
	{
		ERS_Pose = 1 << 29,
		ERS_Color = 1 << 30,
		ERS_Texture = 1 << 31,

		ERS_AllState = ERS_Pose | ERS_Color | ERS_Texture
	};

	GameObject();
	virtual ~GameObject() {}

	virtual Pawn* AsPlayerPawn() { return nullptr; }

	virtual uint32_t GetAllStateMask() const { return ERS_AllState; }

	virtual void HandleCollision(GameObject* other) {}

	virtual void Update() {}

	virtual void HandleDying() {}

	void SetIndexInWorld(int inIndex) { mIndexInWorld = inIndex; }
	int	GetIndexInWorld()				const { return mIndexInWorld; }

	void SetRotation(float inRotation);
	float GetRotation()					const { return mRotation; }

	void SetScale(float inScale) { mScale = inScale; }
	float GetScale()						const { return mScale; }

	const Vector3& GetLocation() const { return mLocation; }
	void SetLocation(const Vector3& inLocation) { mLocation = inLocation; }

	Vector3	GetForwardVector() const;

	void SetColor(const Vector3& inColor) { mColor = inColor; }
	const Vector3& GetColor() const { return mColor; }

	void SetTextureSize(const Vector3& inSize) { mTextureSize = inSize; }
	const Vector3& GetTextureSize() const { return mTextureSize; }

	bool DoesWantToDie() const { return mDoesWantToDie; }
	void SetDoesWantToDie(bool inWants) { mDoesWantToDie = inWants; }

	int	GetNetworkId() const { return mNetworkId; }
	void SetNetworkId(int inNetworkId);

	virtual uint32_t Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const;
	virtual void Read(InputMemoryBitStream& inInputStream);

	virtual void SetTextureRect(float width, float height) {};

private:
	Vector3	mLocation;
	float mRotation;
	float mScale;

	Vector3	mColor;
	Vector3 mTextureSize;

	bool mDoesWantToDie;

	int	mIndexInWorld;
	int	mNetworkId;

};

typedef shared_ptr< GameObject > GameObjectPtr;
