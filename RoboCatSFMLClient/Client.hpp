/*
*  Provided in class, edited by:
*  Petr Sulc - GD4b - D00261476
*  Jakub Polacek - GD4b - D00260171
*/

class Client : public Engine
{
public:

	static bool StaticInit();

protected:

	Client();

	virtual void DoFrame() override;
	virtual void HandleEvent(sf::Event& p_event) override;
	virtual bool PollEvent(sf::Event& p_event) override;
};
