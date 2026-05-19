/*
*  Imported from CA2 and edited by:
*  Petr Sulc - GD4b - D00261476
*/

#include "RoboCatClientPCH.hpp"
#include "MenuState.hpp"

MenuState::MenuState(StateStack& stack) : State(stack)
{
    if(NetworkManagerClient::sInstance)
    {
        delete NetworkManagerClient::sInstance;
        NetworkManagerClient::sInstance = nullptr;
	}

    auto play_button = std::make_shared<gui::Button>();
    play_button->setPosition(sf::Vector2f(540, 200));
    play_button->SetText("Play");
    play_button->SetCallback([this]()
        {
			RequestStackClear();
            RequestStackPush<CS_LobbyState>();
        });

    auto exit_button = std::make_shared<gui::Button>();
    exit_button->setPosition(sf::Vector2f(540, 300));
    exit_button->SetText("Exit");
    exit_button->SetCallback([this]()
        {
            RequestStackClear();
        });

    m_gui_container.Pack(play_button);
    m_gui_container.Pack(exit_button);
}

void MenuState::Draw()
{
    auto& window = *WindowManager::sInstance.get();
    window.clear();
    window.setView(window.getDefaultView());
    window.draw(m_gui_container);
    window.display();
}

bool MenuState::Update(float dt)
{
    return true;
}

bool MenuState::HandleEvent(const sf::Event& event)
{
    m_gui_container.HandleEvent(event);
    return true;
}

