#include "RoboCatClientPCH.hpp"
#include "CS_LobbyState.hpp"

CS_LobbyState::CS_LobbyState(StateStack& stack) :
	LobbyState(stack),
	m_connection_label(nullptr),
	m_ip_input(nullptr),
	m_gui_container(),
	m_is_ready(false),
	m_player_labels()
{
	float midX = 640;

	gui::Label::Ptr nameLabel = std::make_shared<gui::Label>("Player Name:");
	nameLabel->setPosition(sf::Vector2f(midX, 100));
	nameLabel->GetTextRef().setCharacterSize(20);
	nameLabel->CentreText();
	m_gui_container.Pack(nameLabel);

	m_name_input = std::make_shared<gui::Button>();
	m_name_input->setPosition(sf::Vector2f(midX, 150));
	m_name_input->CentreButton();
	m_name_input->SetToggle(true);
	m_name_input->SetText(SaveManager::sInstance->LoadData("name", "Player"));
	m_gui_container.Pack(m_name_input);

	gui::Label::Ptr ipLabel = std::make_shared<gui::Label>("Enter Server IP:");
	ipLabel->setPosition(sf::Vector2f(midX, 200));
	ipLabel->GetTextRef().setCharacterSize(24);
	ipLabel->CentreText();
	m_gui_container.Pack(ipLabel);

	m_ip_input = std::make_shared<gui::Button>();
	m_ip_input->setPosition(sf::Vector2f(midX, 250));
	m_ip_input->CentreButton();
	m_ip_input->SetToggle(true);
	m_ip_input->SetText(SaveManager::sInstance->LoadData("ip"));
	m_gui_container.Pack(m_ip_input);

	m_connection_label = std::make_shared<gui::Label>("No Connection");
	m_connection_label->setPosition(sf::Vector2f(midX, 350));
	m_connection_label->GetTextRef().setCharacterSize(24);
	m_connection_label->GetTextRef().setFillColor(sf::Color::Red);
	m_connection_label->CentreText();
	m_gui_container.Pack(m_connection_label);

	auto connectButton = std::make_shared<gui::Button>();
	connectButton->setPosition(sf::Vector2f(midX, 300));
	connectButton->CentreButton();
	connectButton->SetText("Connect");
	connectButton->SetCallback([this]()
		{
			SocketAddressPtr serverAddress = SocketAddressFactory::CreateIPv4FromString(m_ip_input->GetText());
			NetworkManagerClient::StaticInit(*serverAddress, m_name_input->GetText());
			World::StaticInit();
		});
	m_gui_container.Pack(connectButton);

	m_ready_button = std::make_shared<gui::Button>();
	m_ready_button->setPosition(sf::Vector2f(midX, 575));
	m_ready_button->SetText("Ready Up");
	m_ready_button->CentreButton();
	m_ready_button->SetCallback([this]()
		{
			if (NetworkManagerClient::sInstance)
			{
				m_is_ready = !m_is_ready;
				NetworkManagerClient::sInstance->SetReady(m_is_ready);
				NetworkManagerClient::sInstance->SendLobbyPacket();
			}
		});
	m_gui_container.Pack(m_ready_button);

	auto back_button = std::make_shared<gui::Button>();
	back_button->setPosition(sf::Vector2f(midX, 625));
	back_button->SetText("Quit to Menu");
	back_button->CentreButton();
	back_button->SetCallback([this]()
		{
			RequestStackClear();
			RequestStackPush<MenuState>();
		});
	m_gui_container.Pack(back_button);
}

void CS_LobbyState::Draw()
{
	auto& window = *WindowManager::sInstance.get();

	window.clear();
	window.draw(m_gui_container);
	
	ClearPlayers();
	auto& entries = ScoreBoardManager::sInstance->GetEntries();
	for(auto& entry : entries)
	{
		AddPlayer(entry);
	}

	for (const auto& playerLabel : m_player_labels)
	{
		window.draw(*playerLabel.second);
	}

	window.display();
}

bool CS_LobbyState::Update(float dt)
{

	m_ready_button->SetVisibility(false);

	if (m_is_ready)
	{
		m_ready_button->SetText("Cancel Ready");
	}
	else
	{
		m_ready_button->SetText("Ready Up");
	}

	if (!NetworkManagerClient::sInstance)
	{
		m_connection_label->SetText("No Connection");
		m_connection_label->GetTextRef().setFillColor(sf::Color::Red);
		return false;
	}

	CheckAllReady();

	switch (NetworkManagerClient::sInstance->GetState())
	{
	case NetworkManagerClient::NCS_Uninitialized:
	{
		m_connection_label->SetText("No Connection");
		m_connection_label->GetTextRef().setFillColor(sf::Color::Red);
		break;
	}
	case NetworkManagerClient::NCS_SayingHello:
	{
		m_connection_label->SetText("Connecting...");
		m_connection_label->GetTextRef().setFillColor(sf::Color::Yellow);
		break;
	}
	case NetworkManagerClient::NCS_Welcomed:
	{
		m_connection_label->SetText("Connected");
		m_connection_label->GetTextRef().setFillColor(sf::Color::Green);
		m_ready_button->SetVisibility(true);
		break;
	}
	}
	return false;
}

bool CS_LobbyState::HandleEvent(const sf::Event& event)
{
	bool is_inputing_ip = false;
	bool is_inputing_name = false;

	if (m_ip_input && m_ip_input->IsActive())
	{
		is_inputing_ip = true;
		HandleIpInput(event);
	}

	if (m_name_input && m_name_input->IsActive())
	{
		is_inputing_name = true;
		HandleNameInput(event);
	}

	if (!is_inputing_ip && !is_inputing_name)
	{
		m_gui_container.HandleEvent(event);
	}
	return false;
}

void CS_LobbyState::CheckAllReady()
{
	bool allReady = true;

	auto& entries = ScoreBoardManager::sInstance->GetEntries();
	for (auto& entry : entries)
	{
		if (!entry.IsReady())
		{
			allReady = false;
			break;
		}
	}

	if (allReady && entries.size() >= 2)
	{
		RequestStackClear();
		RequestStackPush<CS_GameState>();
	}
}

void CS_LobbyState::HandleIpInput(const sf::Event& event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (
			event.key.scancode == sf::Keyboard::Scancode::Escape ||
			event.key.scancode == sf::Keyboard::Scancode::Enter)
		{
			m_ip_input->Deactivate();

			SaveManager::sInstance->SaveData("ip", m_ip_input->GetText());

			return;
		}
	}

	if (event.type == sf::Event::TextEntered && event.text.unicode < 128)
	{
		if (event.text.unicode == 8) // Backspace
		{
			std::string current_text = m_ip_input->GetText();
			if (!current_text.empty())
			{
				current_text.pop_back();
				m_ip_input->SetText(current_text);
			}
		}
		else
		{
			char symbol = static_cast<char>(event.text.unicode);
			std::regex ip_regex("([0-9.:])+");
			std::string appended_ip = m_ip_input->GetText() + symbol;
			if (std::regex_match(appended_ip, ip_regex))
			{
				m_ip_input->SetText(appended_ip);
			}
		}
	}
}

void CS_LobbyState::HandleNameInput(const sf::Event& event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (
			event.key.scancode == sf::Keyboard::Scancode::Escape ||
			event.key.scancode == sf::Keyboard::Scancode::Enter)
		{
			m_name_input->Deactivate();

			SaveManager::sInstance->SaveData("name", m_name_input->GetText());

			if (NetworkManagerClient::sInstance)
			{
				NetworkManagerClient::sInstance->SetName(m_name_input->GetText());
				NetworkManagerClient::sInstance->SendLobbyPacket();
			}
			return;
		}
	}

	if (event.type == sf::Event::TextEntered && event.text.unicode == 8) // Backspace
	{
		std::string current_text = m_name_input->GetText();
		if (!current_text.empty())
		{
			current_text.pop_back();
			m_name_input->SetText(current_text);
		}
	}
	if (event.type == sf::Event::TextEntered &&
		event.text.unicode > 31 &&
		event.text.unicode < 128 &&
		event.text.unicode != 59 && // ';' is reserved for save data separation
		event.text.unicode != 61 && // '=' is reserved for save data separation
		m_name_input->GetText().size() < 20)
	{
		char symbol = static_cast<char>(event.text.unicode);
		std::string appended_name = m_name_input->GetText() + symbol;
		m_name_input->SetText(appended_name);
	}
}

void CS_LobbyState::AddPlayer(const ScoreBoardManager::Entry& player)
{
	gui::Label::Ptr label = std::make_shared<gui::Label>(player.GetPlayerName());

	int offset = m_player_labels.size() * 50;
	label->setPosition(sf::Vector2f(320, 150.f + offset));
	label->GetTextRef().setFillColor(player.IsReady() ? sf::Color::Green : sf::Color::Red);
	label->GetTextRef().setCharacterSize(20);
	label->CentreText();

	m_player_labels.emplace(player.GetPlayerId(), std::move(label));
}

void CS_LobbyState::RemovePlayer(int id)
{
	auto label_itr = m_player_labels.find(id);
	float yPos = label_itr->second->getPosition().y;
	float xPos = label_itr->second->getPosition().x;
	if (label_itr != m_player_labels.end())
	{
		;
		m_player_labels.erase(label_itr);

		for (auto& label_pair : m_player_labels)
		{
			if (label_pair.second->getPosition().y > yPos && label_pair.second->getPosition().x == xPos)
			{
				label_pair.second->move(sf::Vector2f(0, -50));
			}
		}
	}
}

void CS_LobbyState::UpdatePlayer(ScoreBoardManager::Entry& player)
{
	m_player_labels[player.GetPlayerId()]->SetText(player.GetPlayerName(), true);
	m_player_labels[player.GetPlayerId()]->GetTextRef().setFillColor(player.IsReady() ? sf::Color::Green : sf::Color::Red);
}

void CS_LobbyState::ClearPlayers()
{
	m_player_labels.clear();
}

void CS_LobbyState::StartGame()
{
	RequestStackPush<CS_GameState>();
}

