/*
*  Imported from CA2 and edited by:
*  Petr Sulc - GD4b - D00261476
*/

#pragma once

namespace gui
{
	class VisualElement : public sf::Drawable, public sf::Transformable
	{
	public:
		typedef std::shared_ptr<VisualElement> Ptr;

	public:
		VisualElement();
		virtual ~VisualElement();
		virtual bool IsSelectable() const = 0;
		bool IsSelected() const;
		virtual void Select();
		virtual void Deselect();
		virtual bool IsActive() const;
		virtual void Activate();
		virtual void Deactivate();

		virtual void HandleEvent(const sf::Event& event) = 0;

	private:
		bool m_is_selected;
		bool m_is_active;

	};
}


