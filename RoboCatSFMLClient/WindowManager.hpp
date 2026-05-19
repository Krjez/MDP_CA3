/*
*  Provided in class, edited by:
*  Petr Sulc - GD4b - D00261476
*/

class WindowManager
{

public:

	static bool StaticInit();
	static std::unique_ptr< sf::RenderWindow >	sInstance;
};