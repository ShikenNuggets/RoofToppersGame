#include "EndLevelTrigger.h"

#include <Graphics/RenderEngine.h>
#include <Graphics/UI/UIManager.h>

#include "CameraController.h"

using namespace GamePackage;

void EndLevelTrigger::OnCollision(const PizzaBox::CollisionInfo& other_){
	if(other_.other->HasTag("Player")){
		PizzaBox::UIManager::EnableSet("WinSet");

		auto cam = PizzaBox::SceneManager::CurrentScene()->GetComponentInScene<CameraController>();
		if(cam != nullptr){
			cam->SetHasControl(false);
		}
	}
}