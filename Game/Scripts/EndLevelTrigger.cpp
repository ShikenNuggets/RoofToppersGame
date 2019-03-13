#include "EndLevelTrigger.h"

#include <Graphics/RenderEngine.h>
#include <Graphics/UI/UIManager.h>

using namespace GamePackage;

void EndLevelTrigger::OnCollision(const PizzaBox::CollisionInfo& other_){
	if(other_.other->HasTag("Player")){
		PizzaBox::RenderEngine::ShowCursor(true);
		PizzaBox::UIManager::EnableSet("WinSet");
	}
}