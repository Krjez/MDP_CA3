#pragma once

enum CollisionLayer
{
	kDefault = 1 << 0,
	kPlayer = 1 << 1,
	kPlayerDisabled = 1 << 2,
	kBall = 1 << 3,
	kWall = 1 << 4,
	kPlayerBarrier = 1 << 5,
	kPickup = 1 << 6,
	kGoal = 1 << 7,
};

class BoxCollider;
class CircleCollider;
class PolygonCollider;

class Collider : public Component
{
private:
	int m_id;
	int m_replicate_collisions;
	bool m_is_trigger;
	CollisionLayer m_layer;
	unsigned int m_ignore_layers;

protected:
	Vector3 m_box_size;

public:
	Collider(GameObject* parent, bool trigger = false);
	~Collider();
	virtual bool CheckCollision(Collider* other) = 0;

	virtual bool CollideWith(Collider* other) = 0;
	virtual bool CollideWith(BoxCollider* other) = 0;
	virtual bool CollideWith(CircleCollider* other) = 0;
	virtual bool CollideWith(PolygonCollider* other) = 0;

	int GetId() const;
	void SetReplicateCollisions(bool state);
	bool ShouldReplicateCollisions() const;
	void AssignId(int id);

	bool IsTrigger() const;
	CollisionLayer GetLayer() const;
	void SetLayer(CollisionLayer layer);
	void SetIgnoreLayers(unsigned int layers);

	bool CheckLayers(Collider* other) const;
	bool BoundingBoxOverlap(Collider* other);
	void ResolveCollision(Collider* other, Vector3& normal, float& depth);
};