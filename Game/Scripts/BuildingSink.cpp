#include "BuildingSink.h"
#include <Core/SceneManager.h>
#include <Graphics/Particles/ParticleSystem.h>

using namespace GamePackage;
BuildingSink::BuildingSink(PizzaBox::Vector3 startPositon_, float collapseTime_, float collapseSpeed_): collapseSpeed(collapseSpeed_), collapseTimer(0.0f), collapseTime(collapseTime_), collapse(false),startPositon(startPositon_){	
}

BuildingSink::~BuildingSink(){
}

void BuildingSink::OnStart(){
	gameObject->SetPosition(startPositon);
	collapse = false;
	collapseSpeed = 10.0f;
	collapseTimer = 0.0f;
	//collapseTime = 25.0f;
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

void BuildingSink::OnCollision(const PizzaBox::CollisionInfo& info_){	
	if(info_.other->HasTag("Player")){
		collapse = true;
	}
}

void BuildingSink::OnDestroy(){
}

void BuildingSink::BeginDestruction(){
}