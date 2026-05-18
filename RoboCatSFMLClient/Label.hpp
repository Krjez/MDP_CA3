#pragma once

namespace gui
{
	class Label : public VisualElement
	{
	public:
		typedef std::shared_ptr<Label> Ptr;

	public:
		Label(const std::string& text);
		virtual bool IsSelectable() const override;
		void SetText(const std::string& text, bool centre = false);
		void HandleEvent(const sf::Event& event) override;
		void CentreText();
		sf::Text& GetTextRef();

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Text m_text;
	};
}


