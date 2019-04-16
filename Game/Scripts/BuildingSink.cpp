#include "BuildingSink.h"
#include <Core/SceneManager.h>
#include <Graphics/Particles/ParticleSystem.h>

using namespace GamePackage;
BuildingSink::BuildingSink(PizzaBox::Vector3 startPositon_, float collapseTime_, float collapseSpeed_, float delayTimer_): collapseSpeed(collapseSpeed_), collapseTimer(0.0f), collapseTime(collapseTime_), collapse(false),startPositon(startPositon_),delayTimer(delayTimer_){
}

BuildingSink::~BuildingSink(){
}

void BuildingSink::OnStart(){
	gameObject->SetPosition(startPositon);
	collapse = false;
	collapseTimer = 0.0f;
	//collapseTime = 25.0f;
}

void BuildingSink::Update(const float deltaTime_) {
	if (collapse == true) {
		collapseTimer += deltaTime_;
		if (collapseTimer >= delayTimer) {
			gameObject->GetTransform()->Translate(PizzaBox::Vector3(0.0f, -collapseSpeed * deltaTime_, 0.0f));
			if (collapseTimer >= (collapseTime + delayTimer)){
				collapse = false;
			}
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