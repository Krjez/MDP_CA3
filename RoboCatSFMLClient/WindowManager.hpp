/*
*  Provided in class, edited by:
*  Petr Sulc - GD4b - D00261476
*  Jakub Polacek - GD4b - D00260171
*/

class WindowManager
{

public:

	static bool StaticInit();
	static std::unique_ptr< sf::RenderWindow >	sInstance;
};