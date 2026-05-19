/*
*  Provided in class, edited by:
*  Petr Sulc - GD4b - D00261476
*/

#include "RoboCatClientPCH.hpp"

std::unique_ptr< RenderManager >	RenderManager::sInstance;

RenderManager::RenderManager()
{
	view.reset(sf::FloatRect(0, 0, 1280, 720));
	WindowManager::sInstance->setView(view);
}

void RenderManager::SortByZOrder()
{
	for (int i = 1; i < mComponents.size(); ++i) {
		SpriteComponent* key = mComponents[i];
		int j = i - 1;

		while (j >= 0 && mComponents[j]->GetZOrder() > key->GetZOrder()) {
			mComponents[j + 1] = mComponents[j];
			j = j - 1;
		}
		mComponents[j + 1] = key;
	}
}


void RenderManager::StaticInit()
{
	sInstance.reset(new RenderManager());
}


void RenderManager::AddComponent(SpriteComponent* inComponent)
{
	mComponents.emplace_back(inComponent);

	SortByZOrder();
}

void RenderManager::RemoveComponent(SpriteComponent* inComponent)
{
	int index = GetComponentIndex(inComponent);

	if (index != -1)
	{
		int lastIndex = (int)mComponents.size() - 1;
		if (index != lastIndex)
		{
			mComponents[index] = mComponents[lastIndex];
		}
		mComponents.pop_back();
	}

	SortByZOrder();
}

int RenderManager::GetComponentIndex(SpriteComponent* inComponent) const
{
	for (int i = 0, c = (int)mComponents.size(); i < c; ++i)
	{
		if (mComponents[i] == inComponent)
		{
			return i;
		}
	}

	return -1;
}


//this part that renders the world is really a camera-
//in a more detailed engine, we'd have a list of cameras, and then render manager would
//render the cameras in order
void RenderManager::RenderComponents()
{
	//Get the logical viewport so we can pass this to the SpriteComponents when it's draw time
	for (SpriteComponent* c : mComponents)
	{	
		WindowManager::sInstance->draw(c->GetSprite());	
	}
}

void RenderManager::Render()
{
	//Sets camera view by the first player, 70% of the way across the screen, and centered vertically
	float leadingPawnX = World::sInstance->GetLeadingPawnXLocation();

	if (leadingPawnX > 640)
	{
		view.setCenter(leadingPawnX - 256, 360);
	}
	else
	{
		view.setCenter(384, 360);
	}

	WindowManager::sInstance->setView(view);

	WindowManager::sInstance->clear(sf::Color(100, 149, 237, 255));

	RenderManager::sInstance->RenderComponents();

	HUD::sInstance->Render();

	//
	// Present our back buffer to our front buffer
	//
	WindowManager::sInstance->display();

}
