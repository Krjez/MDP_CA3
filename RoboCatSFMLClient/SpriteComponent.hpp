/*
*  Provided in class, edited by:
*  Petr Sulc - GD4b - D00261476
*  Jakub Polacek - GD4b - D00260171
*/

typedef shared_ptr< sf::Texture > TexturePtr;
typedef shared_ptr<sf::Font> FontPtr;

class SpriteComponent
{
public:

	SpriteComponent(GameObject* inGameObject, int z_order = 0);
	~SpriteComponent();


	void SetTexture(TexturePtr inTexture);
	virtual sf::Sprite& GetSprite();

	float GetZOrder() const { return m_z_order; }
	void SetTextureSize(int inWidth, int inHeight);

protected:

	sf::Sprite m_sprite;
	int m_z_order;

	//don't want circular reference...
	GameObject* mGameObject;
};

typedef shared_ptr< SpriteComponent >	SpriteComponentPtr;

