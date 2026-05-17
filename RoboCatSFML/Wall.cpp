#include "RoboCatPCH.hpp"
#include "Wall.hpp"

Wall::Wall() :
	GameObject(),
	m_collider(new CircleCollider(this, 1.0f))
{
}

void Wall::SetCollider(float width, float height)
{
	m_collider = std::make_unique<BoxCollider>(this, width, height);
}

void Wall::SetCollider(float radius)
{
	m_collider = std::make_unique<CircleCollider>(this, radius);
}

void Wall::SetCollider(vector<Vector3> vertices)
{
	m_collider = std::make_unique<PolygonCollider>(this, vertices);
}

uint32_t Wall::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	
	uint32_t writtenState = GameObject::Write(inOutputStream, inDirtyState);
	
	if (inDirtyState & ERS_Collider)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(static_cast<int>(m_collider->GetColliderType()));

		switch (m_collider->GetColliderType())
		{
		case kBox:
		{
			BoxCollider* box = static_cast<BoxCollider*>(&*m_collider);
			inOutputStream.Write(box->GetBoxSize().mX);
			inOutputStream.Write(box->GetBoxSize().mY);
			break;
		}

		case kCircle:
		{
			CircleCollider* circle = static_cast<CircleCollider*>(&*m_collider);
			inOutputStream.Write(circle->GetRadius());
			break;
		}

		case kPolygon:
		{
			PolygonCollider* polygon = static_cast<PolygonCollider*>(&*m_collider);
			const vector<Vector3>& verts = polygon->GetVertices();
			inOutputStream.Write(verts.size(), 8);
			for (auto& vert : verts)
			{
				inOutputStream.Write(vert.mX);
				inOutputStream.Write(vert.mY);
			}
			break;
		}
		}
		writtenState |= ERS_Collider;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}
	
	return writtenState;
}

void Wall::Read(InputMemoryBitStream& inInputStream)
{
	GameObject::Read(inInputStream);
	
	bool stateBit;
	inInputStream.Read(stateBit);
	if (stateBit)
	{
		int type;
		inInputStream.Read(type);
		
		switch (type)
		{
		case kBox:
		{
			float x;
			inInputStream.Read(x);
			float y;
			inInputStream.Read(y);
			m_collider.reset(new BoxCollider(this,x, y));
			break;
		}

		case kCircle:
		{
			float radius;
			inInputStream.Read(radius);
			m_collider.reset(new CircleCollider(this, radius));
			break;
		}

		case kPolygon:
		{
			int size;
			std::vector<Vector3> verts;
			inInputStream.Read(size, 8);

			for (int i = 0; i < size; i++)
			{
				float x;
				float y;
				inInputStream.Read(x);
				inInputStream.Read(y);
				verts.emplace_back(Vector3(x,y,0));
			}

			m_collider.reset(new PolygonCollider(this, verts));
			break;
		}
		}
	}
}