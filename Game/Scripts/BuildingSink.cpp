#include "BuildingSink.h"
#include <Core/SceneManager.h>
#include <Graphics/Particles/ParticleSystem.h>

using namespace GamePackage;
BuildingSink::BuildingSink( float collapseTime_): collapseSpeed(0.0f), collapseTimer(0.0f), collapseTime(collapseTime_), collapse(false)
{
}
void BuildingSink::OnStart() {
	collapse = false;
	collapseSpeed = 10.0f;
	collapseTimer = 0.0f;
	//collapseTime = 25.0f;
}

BuildingSink::~BuildingSink()
{
}
void BuildingSink::Update(const float deltaTime_) {

	if (collapse == true) {

		gameObject->GetTransform()->Translate(PizzaBox::Vector3(0.0f, -collapseSpeed * deltaTime_, 0.0f));
		collapseTimer += deltaTime_;
		if (collapseTimer >= collapseTime) {
			PizzaBox::SceneManager::CurrentScene()->DestroyObject(gameObject);
		}

	}
}

void BuildingSink::OnCollision(const PizzaBox::GameObject* const other_) {
	collapse = true;
	if (other_->HasTag("Player")) {
		collapse = true;
	}
}

void BuildingSink::OnDestroy() {


}
void BuildingSink::BeginDestruction() {
}