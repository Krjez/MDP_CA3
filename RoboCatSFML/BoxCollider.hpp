/*
*  Imported from CA2 and edited by:
*  Petr Sulc - GD4b - D00261476
*/

#pragma once
class BoxCollider : public Collider
{
public:
	BoxCollider(GameObject* parent, float width, float height, bool trigger = false);
	~BoxCollider();

	virtual bool CheckCollision(Collider* other) override;

	virtual bool CollideWith(Collider* other) override;
	virtual bool CollideWith(BoxCollider* other) override;
	virtual bool CollideWith(CircleCollider* other) override;
	virtual bool CollideWith(PolygonCollider* other) override;

	ColliderType GetColliderType() const override { return ColliderType::kBox; };

	Vector3 GetBoxSize() const;
};