#include "GameController.h"

#include <Core/Config.h>
#include <Core/SceneManager.h>
#include <Core/Time.h>
#include <Graphics/RenderEngine.h>
#include <Graphics/UI/ImageUI.h>
#include <Graphics/UI/TextUI.h>
#include <Graphics/UI/UIManager.h>
#include <Input/InputManager.h>
#include <Tools/EngineStats.h>
#include "Objects/Player.h"
#include "Scripts/BuildingSink.h"
using namespace GamePackage;

GameController::GameController(const PizzaBox::Vector3& pos_, const PizzaBox::Euler& rot_) : player(nullptr), camera(nullptr), spawnPos(pos_), spawnRotation(rot_), isPaused(false), hasCompletedTutorial(false), tutorialFadeOutTimer(0.0f), isFadingIn(true), tutorialFadeInTimer(0.0f){
}

GameController::~GameController(){
}

void GameController::OnStart(){
	PizzaBox::EngineStats::SetFloat("IGT", 0.0f);

	camera = PizzaBox::SceneManager::CurrentScene()->GetComponentInScene<CameraController>();
	if(camera == nullptr){
		PizzaBox::Debug::LogError("No PizzaBox::Camera found in scene!", __FILE__, __LINE__);
		return;
	}

	ResetScene();

	PizzaBox::UIManager::EnableSet("TutorialSet");
	SetTutorialUIControllerType(PizzaBox::Config::GetInt("ControlUIType"));
	SetTutorialUITransparency(1.0f);
}

void GameController::Update(const float deltaTime_){
	if(isFadingIn && !hasCompletedTutorial){
		tutorialFadeInTimer += PizzaBox::Time::RealDeltaTime();
		if(tutorialFadeInTimer > 0.5){
			SetTutorialUITransparency(1.0f);
			isFadingIn = false;
		}else{
			SetTutorialUITransparency(tutorialFadeInTimer * 2.0f);
		}
	}

	if(player != nullptr && player->GetComponent<PlayerController>() != nullptr && player->GetComponent<PlayerController>()->HasControl()){
		PizzaBox::EngineStats::AddToFloat("IGT", deltaTime_);
	}

	if(PizzaBox::InputManager::GetKeyDown(SDLK_BACKQUOTE)){
		PizzaBox::UIManager::ToggleSet("StatsSet");
	}

	if(PizzaBox::InputManager::GetButtonUp("Exit") && !isPaused){
		TogglePause();
	}

	if(PizzaBox::InputManager::GetKeyDown(SDLK_k)){
		if(PizzaBox::Config::GetInt("ControlUIType") == 0){
			PizzaBox::Config::SetInt("ControlUIType", 1);
		}else{
			PizzaBox::Config::SetInt("ControlUIType", 0);
		}
	}

	int ms = PizzaBox::Config::GetInt("MouseSensitivity");
	if(PizzaBox::InputManager::GetKeyDown(SDLK_EQUALS)){
		ms += 100;
	}else if(PizzaBox::InputManager::GetKeyDown(SDLK_MINUS)){
		ms -= 100;	
	}

	PizzaBox::Config::SetInt("MouseSensitivity", PizzaBox::Math::Clamp(100, 1000, ms));
}

void GameController::OnDestroy(){
}

void GameController::ResetScene(){
	PizzaBox::EngineStats::SetFloat("IGT", 0.0f);
	isPaused = false;
	PizzaBox::Time::SetTimeScale(1.0f);
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

	for (BuildingSink* bs : PizzaBox::SceneManager::CurrentScene()->GetComponentsInScene<BuildingSink>()) {
		bs->OnStart();
	}
}

void GameController::TogglePause(){
	if(player != nullptr && !player->GetComponent<PlayerController>()->HasControl()){
		return;
	}

	isPaused = !isPaused;

	if(isPaused){
		PizzaBox::Time::SetTimeScale(0.0f);
		PizzaBox::UIManager::EnableSet("PauseSet");
		camera->SetHasControl(false);
	}else{
		PizzaBox::Time::SetTimeScale(1.0f);
		PizzaBox::UIManager::DisableSet("PauseSet");
		camera->SetHasControl(true);
	}
}

void GameController::CompleteTutorial(){
	isFadingIn = false;
	hasCompletedTutorial = true;

	tutorialFadeOutTimer += PizzaBox::Time::RealDeltaTime();

	if(tutorialFadeOutTimer > 0.5f){
		SetTutorialUITransparency(1.0f);
		PizzaBox::UIManager::DisableSet("TutorialSet");
		return;
	}

	SetTutorialUITransparency(1.0f - (tutorialFadeOutTimer * 2.0f));
}

void GameController::SetTutorialUITransparency(float transparency_){
	if(!PizzaBox::UIManager::IsSetActive("TutorialSet")){
		return;
	}

	PizzaBox::UIManager::GetElementFromSet<PizzaBox::ImageUI>("TutorialSet", "XImage")->SetTransparency(transparency_);
	PizzaBox::UIManager::GetElementFromSet<PizzaBox::ImageUI>("TutorialSet", "CircleImage")->SetTransparency(transparency_);
	PizzaBox::UIManager::GetElementFromSet<PizzaBox::ImageUI>("TutorialSet", "AImage")->SetTransparency(transparency_);
	PizzaBox::UIManager::GetElementFromSet<PizzaBox::ImageUI>("TutorialSet", "BImage")->SetTransparency(transparency_);

	auto xText = PizzaBox::UIManager::GetElementFromSet<PizzaBox::TextUI>("TutorialSet", "XText");
	auto c = xText->GetColor();
	xText->SetColor(PizzaBox::Color(c.r, c.g, c.b, transparency_));

	auto circleText = PizzaBox::UIManager::GetElementFromSet<PizzaBox::TextUI>("TutorialSet", "CircleText");
	c = circleText->GetColor();
	circleText->SetColor(PizzaBox::Color(c.r, c.g, c.b, transparency_));
}

void GameController::SetTutorialUIControllerType(int type_){
	if(type_ == 0){
		//PS4
		PizzaBox::UIManager::GetElementFromSet<PizzaBox::ImageUI>("TutorialSet", "XImage")->SetEnable(true);
		PizzaBox::UIManager::GetElementFromSet<PizzaBox::ImageUI>("TutorialSet", "CircleImage")->SetEnable(true);
		PizzaBox::UIManager::GetElementFromSet<PizzaBox::ImageUI>("TutorialSet", "AImage")->SetEnable(false);
		PizzaBox::UIManager::GetElementFromSet<PizzaBox::ImageUI>("TutorialSet", "BImage")->SetEnable(false);
	}else if(type_ == 1){
		//Xbox
		PizzaBox::UIManager::GetElementFromSet<PizzaBox::ImageUI>("TutorialSet", "XImage")->SetEnable(false);
		PizzaBox::UIManager::GetElementFromSet<PizzaBox::ImageUI>("TutorialSet", "CircleImage")->SetEnable(false);
		PizzaBox::UIManager::GetElementFromSet<PizzaBox::ImageUI>("TutorialSet", "AImage")->SetEnable(true);
		PizzaBox::UIManager::GetElementFromSet<PizzaBox::ImageUI>("TutorialSet", "BImage")->SetEnable(true);
	}
}