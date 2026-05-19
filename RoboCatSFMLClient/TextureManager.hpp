/*
*  Provided in class, edited by:
*  Petr Sulc - GD4b - D00261476
*  Jakub Polacek - GD4b - D00260171
*/

class TextureManager
{
public:
	static void StaticInit();

	static std::unique_ptr<TextureManager>		sInstance;

	TexturePtr	GetTexture(const string& inTextureName);

private:
	TextureManager();

	bool CacheTexture(string inName, const char* inFileName);

	unordered_map< string, TexturePtr >	mNameToTextureMap;
};

