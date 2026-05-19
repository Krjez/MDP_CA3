/*
*  Imported from CA2 and edited by:
*  Petr Sulc - GD4b - D00261476
*/

#pragma once
class CS_LobbyState : public LobbyState
{
public:
	CS_LobbyState(StateStack& stack);
	virtual void Draw() override;
	virtual bool Update(float dt) override;
	virtual bool HandleEvent(const sf::Event& event) override;

	void CheckAllReady();

	void AddPlayer(const ScoreBoardManager::Entry& player);
	void RemovePlayer(int id);
	void UpdatePlayer(ScoreBoardManager::Entry& player);
	void ClearPlayers();

	void StartGame();

private:
	void HandleIpInput(const sf::Event& event);
	void HandleNameInput(const sf::Event& event);

private:
	gui::Label::Ptr m_connection_label;
	gui::Button::Ptr m_ip_input;
	gui::Button::Ptr m_ready_button;
	gui::Button::Ptr m_name_input;

	gui::Container m_gui_container;

	std::map<uint8_t, gui::Label::Ptr> m_player_labels;

	bool m_is_ready;
};