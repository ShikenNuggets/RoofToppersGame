#include "Building.h"

#include <Core/SceneManager.h>
#include <Graphics/Particles/ParticleSystem.h>

#include "CameraController.h"
#include "MonsterController.h"

using namespace GamePackage;

Building::Building(float collapseTime_) : health(0.0f), wasHitThisFrame(false), isBeingDestroyed(false), collapseSpeed(0.0f), collapseTimer(0.0f), collapseTime(collapseTime_){
}

void Building::OnStart(){
	health = 3.0f;
	wasHitThisFrame = false;
	isBeingDestroyed = false;
	collapseSpeed = 10.0f;
	collapseTimer = 0.0f;
	//collapseTime = 5.0f;
}

void Building::Update(const float deltaTime_){
	if(wasHitThisFrame){
		health -= deltaTime_;
		wasHitThisFrame = false;
	}

	if(health <= 0.0f && !isBeingDestroyed){
		BeginDestruction();
	}

	if(isBeingDestroyed){
		gameObject->GetTransform()->Translate(PizzaBox::Vector3(0.0f, -collapseSpeed * deltaTime_, 0.0f));
		collapseTimer += deltaTime_;
		if(collapseTimer >= collapseTime){
			PizzaBox::SceneManager::CurrentScene()->DestroyObject(gameObject);
		}
	}
}

void Building::OnDestroy(){
}

void Building::OnCollision(const PizzaBox::GameObject* const other_){
	if(other_->HasTag("Player")){
		wasHitThisFrame = true;
	}
}

void Building::BeginDestruction(){
	isBeingDestroyed = true;
	auto thing = new PizzaBox::ParticleSystem(new PizzaBox::ParticleTexture("SmokeTexture", 7), 80.0f, 10.0f, 0.0f, collapseTime / 2.0f);
	gameObject->AddComponent(thing);
	thing->Translate(PizzaBox::Vector3(0.0f, 15.0f, 0.0f));
	thing->SetScale(8.0f);
	
	auto player = PizzaBox::SceneManager::CurrentScene()->FindWithTag("Player");
	if(player != nullptr){
		player->GetComponent<MonsterController>()->BeginGrow();
	}

	auto camera = PizzaBox::SceneManager::CurrentScene()->FindWithTag("Camera");
	if(camera != nullptr){
		camera->GetComponent<CameraController>()->BeginShaking(collapseTime, 2.5f);
	}

	auto sfxPlayer = gameObject->GetComponent<PizzaBox::AudioSource>();
	if(sfxPlayer != nullptr){
		sfxPlayer->PlayOnce();
	}
}