#include "MainMenuScene.h"

#include <Audio/AudioListener.h>
#include <Audio/AudioSource.h>
#include <Graphics/Sky/SkyBox.h>
#include <Graphics/UI/UIManager.h>

#include "Scripts/MainMenuController.h"
#include "Scripts/QuitButtonScript.h"

using namespace GamePackage;

MainMenuScene::MainMenuScene(){
}

MainMenuScene::~MainMenuScene(){
}

bool MainMenuScene::Initialize(){
	SetSky(new PizzaBox::SkyBox("DarkSkybox"));

	PizzaBox::GameObject* mainCamera = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 0.0f, 20.0f), PizzaBox::Euler(-45.0f, 0.0f, 0.0f));
	mainCamera->AddComponent(new PizzaBox::Camera(PizzaBox::ViewportRect::fullScreen, PizzaBox::Camera::RenderMode::Perspective));
	mainCamera->AddComponent(new PizzaBox::AudioListener());

	// Button related Scripts
	auto scrp1 = new MainMenuController();
	mainCamera->AddComponent(scrp1);
	auto scrp2 = new QuitButtonScript();
	mainCamera->AddComponent(scrp2);
	
	// Background music 
	//mainCamera->AddComponent(new PizzaBox::AudioSource("MainMenuMusic", PizzaBox::AudioSource::SoundType::_2D, "Music"));

	PizzaBox::UIManager::EnableSet("MainMenuSet");

	PizzaBox::UIManager::GetElementFromSet<PizzaBox::UIElement>("MainMenuSet", "PlayButton")->SetScript(scrp1);
	PizzaBox::UIManager::GetElementFromSet<PizzaBox::UIElement>("MainMenuSet", "QuitButton")->SetScript(scrp2);

	return true;
}

void MainMenuScene::Destroy(){
	Scene::Destroy();
}