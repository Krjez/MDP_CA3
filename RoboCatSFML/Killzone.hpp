#pragma once
class Killzone : public GameObject
{
public:

	CLASS_IDENTIFICATION('KILL', GameObject)

	static	GameObject* StaticCreate() { return new Killzone(); }

	virtual void Update() override;

	virtual uint32_t Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;
	virtual void Read(InputMemoryBitStream& inInputStream) override;

protected:
	Killzone();
	float mSpeed;
	float mMoved;
	float mMaxX;

};

typedef shared_ptr< Killzone >	KillzonePtr;