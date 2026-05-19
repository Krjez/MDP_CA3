/*
*  Provided in class, edited by:
*  Petr Sulc - GD4b - D00261476
*  Jakub Polacek - GD4b - D00260171
*/

class Server : public Engine
{
public:

	static bool StaticInit();

	virtual void DoFrame() override;

	virtual int Run();

	void HandleNewClient(ClientProxyPtr inClientProxy);
	void HandleLostClient(ClientProxyPtr inClientProxy);

	GameObjectPtr GetPlayerPawn(int inPlayerId);
	void SpawnPlayerPawn(int inPlayerId);

	void RestartWorld();


private:
	Server();
	void	SetupWorld();
};

