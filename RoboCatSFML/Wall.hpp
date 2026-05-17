#pragma once
class Wall : public GameObject
{
public:

	CLASS_IDENTIFICATION('WALL', GameObject)

		enum EWallReplicationState
	{
		ERS_Collider = 1 << 0,

		ERS_AllState = ERS_Collider
	};

	static	GameObject* StaticCreate() { return new Wall(); }

	virtual uint32_t GetAllStateMask()	const override { return ERS_AllState | GameObject::ERS_AllState; }

	virtual uint32_t Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;
	virtual void Read(InputMemoryBitStream& inInputStream) override;

	void SetCollider(float width, float height);
	void SetCollider(float radius);
	void SetCollider(vector<Vector3> vertices);

protected:
	Wall();
	unique_ptr<Collider> m_collider;
};

typedef shared_ptr< Wall >	WallPtr;