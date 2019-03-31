#include "GameController.h"

#include <Core/SceneManager.h>
#include <Core/Time.h>
#include <Graphics/RenderEngine.h>
#include <Graphics/UI/UIManager.h>
#include <Input/InputManager.h>

#include "Objects/Player.h"

using namespace GamePackage;

GameController::GameController(const PizzaBox::Vector3& pos_, const PizzaBox::Euler& rot_) : player(nullptr), camera(nullptr), spawnPos(pos_), spawnRotation(rot_), isPaused(false){
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
	if(PizzaBox::InputManager::GetKeyDown(SDLK_BACKQUOTE)){
		PizzaBox::UIManager::ToggleSet("StatsSet");
	}

	if(PizzaBox::InputManager::GetButtonUp("Exit") && !isPaused){
		TogglePause();
	}
}

void GameController::OnDestroy(){
}

void GameController::ResetScene(){
	PizzaBox::Time::SetTimeScale(1.0f);
	PizzaBox::RenderEngine::ShowCursor(false);
	PizzaBox::UIManager::DisableSet("PauseSet");
	PizzaBox::UIManager::DisableSet("WinSet");
	PizzaBox::UIManager::DisableSet("DeathSet");

	if(player != nullptr){
		PizzaBox::SceneManager::SceneManager::CurrentScene()->DestroyObject(player);
		player = nullptr;
	}

	player = PizzaBox::SceneManager::CurrentScene()->CreateObject<Player>(spawnPos, spawnRotation, PizzaBox::Vector3(0.01f, 0.01f, 0.01f));
	camera->SetTarget(player);

	camera->GetGameObject()->SetPosition(PizzaBox::Vector3(0.0f, 55.0f, 80.0f));
	camera->GetGameObject()->SetRotation(PizzaBox::Euler(-15.0f, 0.0f, 0.0f));
	camera->SetHasControl(true);
}

void GameController::TogglePause(){
	if(player != nullptr && !player->GetComponent<PlayerController>()->HasControl()){
		return;
	}

	isPaused = !isPaused;

	if(isPaused){
		PizzaBox::Time::SetTimeScale(0.0f);
		PizzaBox::RenderEngine::ShowCursor(true);
		PizzaBox::UIManager::EnableSet("PauseSet");
		camera->SetHasControl(false);
	}else{
		PizzaBox::Time::SetTimeScale(1.0f);
		PizzaBox::RenderEngine::ShowCursor(false);
		PizzaBox::UIManager::DisableSet("PauseSet");
		camera->SetHasControl(true);
	}
}