/*
*  Provided in class, edited by:
*  Petr Sulc - GD4b - D00261476
*  Jakub Polacek - GD4b - D00260171
*/

#include "RoboCatShared.hpp"

#include "regex"

#include "SFML\Graphics.hpp"

#include "InputManager.hpp"
#include "SpriteComponent.hpp"
#include "PlayerSpriteComponent.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "RenderManager.hpp"
#include "WindowManager.hpp"

#include "RoboCatClient.hpp"
#include "CGO_Wall.hpp"
#include "CGO_Killzone.hpp"
#include "Background.hpp"

#include "HUD.hpp"

#include "VisualElement.hpp"
#include "Button.hpp"
#include "Container.hpp"
#include "Label.hpp"

#include "MenuState.hpp"
#include "CS_LobbyState.hpp"
#include "CS_GameState.hpp"

#include "ReplicationManagerClient.hpp"
#include "NetworkManagerClient.hpp"
#include "Client.hpp"