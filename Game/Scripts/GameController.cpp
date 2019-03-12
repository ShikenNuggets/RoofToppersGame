#include "GameController.h"

#include <Core/SceneManager.h>

#include "Objects/Player.h"

using namespace GamePackage;

GameController::GameController(const PizzaBox::Vector3& pos_, const PizzaBox::Euler& rot_) : player(nullptr), camera(nullptr), spawnPos(pos_), spawnRotation(rot_){
}

GameController::~GameController(){
}

void GameController::OnStart(){
	camera = PizzaBox::SceneManager::CurrentScene()->GetComponentInScene<CameraController>();
	if(camera == nullptr){
		PizzaBox::Debug::LogError("No PizzaBox::Camera found in scene!", __FILE__, __LINE__);
		return;
	}

	ResetScene();
}

void GameController::Update(const float deltaTime_){
}

void GameController::OnDestroy(){
}

void GameController::ResetScene(){
	if(player != nullptr){
		PizzaBox::SceneManager::SceneManager::CurrentScene()->DestroyObject(player);
		player = nullptr;
	}

	player = PizzaBox::SceneManager::CurrentScene()->CreateObject<Player>(spawnPos, spawnRotation);
	camera->SetTarget(player);
}