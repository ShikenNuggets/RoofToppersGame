#include "EndLevelTrigger.h"
using namespace GamePackage;

void EndLevelTrigger::OnCollision(const PizzaBox::CollisionInfo& other_) {
	if (other_.other->HasTag("Player")) {
		PizzaBox::SceneManager::LoadNextScene();
	}
}