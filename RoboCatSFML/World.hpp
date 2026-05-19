/*
*  Provided in class, edited by:
*  Petr Sulc - GD4b - D00261476
*  Jakub Polacek - GD4b - D00260171
*/

class World
{

public:

	static void StaticInit();

	static std::unique_ptr< World >		sInstance;

	void AddGameObject(GameObjectPtr inGameObject);
	void RemoveGameObject(GameObjectPtr inGameObject);

	void Update();

	const std::vector< GameObjectPtr >& GetGameObjects()	const { return mGameObjects; }

	float GetLeadingPawnXLocation();

private:

	World();

	std::vector< GameObjectPtr >	mGameObjects;
};

