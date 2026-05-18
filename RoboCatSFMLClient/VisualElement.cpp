#include "RoboCatClientPCH.hpp"
#include "VisualElement.hpp"

gui::VisualElement::VisualElement() : m_is_selected(false), m_is_active(false)
{
}

gui::VisualElement::~VisualElement()
{
}

bool gui::VisualElement::IsSelected() const
{
    return m_is_selected;
}

void gui::VisualElement::Select()
{
    m_is_selected = true;
}

void gui::VisualElement::Deselect()
{
    m_is_selected = false;
}

bool gui::VisualElement::IsActive() const
{
    return m_is_active;
}

void gui::VisualElement::Activate()
{
    m_is_active = true;
}

void gui::VisualElement::Deactivate()
{
    m_is_active = false;
}
