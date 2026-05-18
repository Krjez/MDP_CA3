#include "RoboCatClientPCH.hpp"
#include "Button.hpp"

gui::Button::Button()
    : m_sprite(*TextureManager::sInstance->GetTexture("button"))
    , m_text()
    , m_is_toggle(false)
    , m_is_visible(true)
{
    m_text.setFont(*FontManager::sInstance->GetFont("carlito"));
	m_text.setCharacterSize(16);

    ChangeTexture(ButtonType::kNormal);
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_text.setPosition(sf::Vector2f(bounds.getSize().x / 2, bounds.getSize().y / 2));
}

void gui::Button::SetCallback(Callback callback)
{
    m_callback = std::move(callback);
}

void gui::Button::SetToggle(bool flag)
{
    m_is_toggle = flag;
}

void gui::Button::SetVisibility(bool visible)
{
    m_is_visible = visible;
}

void gui::Button::CentreButton()
{
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(sf::Vector2f(std::floor(bounds.getPosition().x + bounds.getSize().x / 2.f), std::floor(bounds.getPosition().y + bounds.getSize().y / 2.f)));
    m_text.setPosition(sf::Vector2f(0, 0));
}

std::string gui::Button::GetText() const
{
    return m_text.getString();
}

void gui::Button::SetText(const std::string& text)
{
    m_text.setString(text);
    sf::FloatRect bounds = m_text.getLocalBounds();
    m_text.setOrigin(sf::Vector2f(std::floor(bounds.getPosition().x + bounds.getSize().x / 2.f), std::floor(bounds.getPosition().y + bounds.getSize().y / 2.f)));

}

bool gui::Button::IsSelectable() const
{
    return m_is_visible;
}

void gui::Button::Select()
{
    VisualElement::Select();
    ChangeTexture(ButtonType::kSelected);
}

void gui::Button::Deselect()
{
    VisualElement::Deselect();
    ChangeTexture(ButtonType::kNormal);
}

void gui::Button::Activate()
{
    VisualElement::Activate();
    if (m_is_toggle)
    {
        ChangeTexture(ButtonType::kPressed);
    }
    if (m_callback)
    {
        m_callback();
    }
    if (!m_is_toggle)
    {
        Deactivate();
    }
}

void gui::Button::Deactivate()
{
    VisualElement::Deactivate();
    if (m_is_toggle)
    {
        if (IsSelected())
        {
            ChangeTexture(ButtonType::kSelected);
        }
        else
        {
            ChangeTexture(ButtonType::kNormal);
        }
    }
}

void gui::Button::HandleEvent(const sf::Event& event)
{
}

void gui::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!m_is_visible)
        return;

    states.transform *= getTransform();
    target.draw(m_sprite, states);
    target.draw(m_text, states);
}

void gui::Button::ChangeTexture(ButtonType buttonType)
{
    sf::IntRect textureRect({ 0, 50 * static_cast<int>(buttonType) }, { 200, 50 });
    m_sprite.setTextureRect(textureRect);
}