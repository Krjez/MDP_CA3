/*
* Imported from CA2 and edited by:
* Petr Sulc - GD4b - D00261476
*/

#pragma once

enum CollisionLayer
{
	kDefault = 1 << 0,
	kPlayer = 1 << 1
};

enum ColliderType
{
	kBox,
	kCircle,
	kPolygon
};

class BoxCollider;
class CircleCollider;
class PolygonCollider;

class Collider : public Component
{
private:
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

	bool ShouldReplicateCollisions() const;

	bool IsTrigger() const;
	CollisionLayer GetLayer() const;
	void SetLayer(CollisionLayer layer);
	void SetIgnoreLayers(unsigned int layers);

	virtual ColliderType GetColliderType() const = 0;

	bool CheckLayers(Collider* other) const;
	bool BoundingBoxOverlap(Collider* other);
	void ResolveCollision(Collider* other, Vector3& normal, float& depth);
};