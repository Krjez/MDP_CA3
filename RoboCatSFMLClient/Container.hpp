/*
*  Imported from CA2 and edited by:
*  Petr Sulc - GD4b - D00261476
*/

#pragma once

namespace gui
{
	class Container : public VisualElement
	{
	public:
		typedef std::shared_ptr<Container> Ptr;

	public:
		Container();
		void Pack(VisualElement::Ptr component);
		virtual bool IsSelectable() const override;
		virtual void HandleEvent(const sf::Event& event) override;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		bool HasSelection() const;
		void Select(std::size_t index);
		void SelectNext();
		void SelectPrevious();

	private:
		std::vector<VisualElement::Ptr> m_children;
		int m_selected_child;
	};
}

