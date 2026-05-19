/*
*  Imported from CA2 and edited by:
*  Petr Sulc - GD4b - D00261476
*/

#include "RoboCatClientPCH.hpp"
#include "Label.hpp"

gui::Label::Label(const std::string& text)
{
    m_text.setFont(*FontManager::sInstance->GetFont("carlito"));
    m_text.setCharacterSize(16);
	m_text.setString(text);
}

bool gui::Label::IsSelectable() const
{
    return false;
}

void gui::Label::SetText(const std::string& text, bool centre)
{
    m_text.setString(text);
    if (centre)
    {
        CentreText();
    }
}

void gui::Label::HandleEvent(const sf::Event& event)
{
}

void gui::Label::CentreText()
{
    sf::FloatRect bounds = m_text.getLocalBounds();
    m_text.setOrigin(sf::Vector2f(std::floor(bounds.getPosition().x + bounds.getSize().x / 2.f), std::floor(bounds.getPosition().y + bounds.getSize().y / 2.f)));

}

sf::Text& gui::Label::GetTextRef()
{
    return m_text;
}

void gui::Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_text, states);
}
