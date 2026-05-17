#pragma once

class CircleCollider : public Collider
{
private:
	float m_radius;

public:
	CircleCollider(GameObject* parent, float radius, bool trigger = false);

	virtual bool CheckCollision(Collider* other) override;

	virtual bool CollideWith(Collider* other) override;
	virtual bool CollideWith(BoxCollider* other) override;
	virtual bool CollideWith(CircleCollider* other) override;
	virtual bool CollideWith(PolygonCollider* other) override;

	ColliderType GetColliderType() const override { return ColliderType::kCircle; };

	float GetRadius() const;
	Vector3 GetCenter() const;
};