/*
*  Written by:
*  Petr Sulc - GD4b - D00261476
*/

#pragma once
class GameObject;
class Vector3;

class Component
{
public:
	Component(GameObject* parent);
	const Vector3& GetParentLocation() const;
	void SetParentLocation(const Vector3& inLocation);

	const Vector3& GetLocalOffset() const;
	void SetLocalOffset(const Vector3& inOffset);

	const Vector3 GetAbsoluteLocation() const;

	const GameObject* GetParent() const;;
	GameObject* GetParent();;
private:
	GameObject* m_parent;
	Vector3 m_local_offset;
};

