#pragma once

class PolygonCollider : public Collider
{
private:
	std::vector<Vector3> m_vertices;

public:
	PolygonCollider(GameObject* parent, std::vector<Vector3>& vertices, bool trigger = false);

	virtual bool CheckCollision(Collider* other) override;

	virtual bool CollideWith(Collider* other) override;
	virtual bool CollideWith(BoxCollider* other) override;
	virtual bool CollideWith(CircleCollider* other) override;
	virtual bool CollideWith(PolygonCollider* other) override;

	static Vector3 ApproximateCenter(std::vector<Vector3>& vertices);
	static void ProjectVertices(Vector3& normal, std::vector<Vector3>& vertices, float& outMin, float& outMax);
	static bool CheckPolygonSAT(
		Vector3& firstPos, std::vector<Vector3>& firstVertices,
		Vector3& secondPos, std::vector<Vector3>& secondVertices,

		Vector3& outNormal, float& outDepth);

	static Vector3 ClosestPolygonVertex(Vector3& from, Vector3& polyPos, std::vector<Vector3>& vertices);
	static bool CheckCircleSAT(
		Vector3& polyPos, std::vector<Vector3>& polyVertices,
		Vector3& circlePos, float circleRadius,
		Vector3& outNormal, float& outDepth);
};
