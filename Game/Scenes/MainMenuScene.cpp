#include "MainMenuScene.h"

#include <Audio/AudioListener.h>
#include <Audio/AudioSource.h>
#include <Graphics/RenderEngine.h>
#include <Graphics/Sky/SkyBox.h>
#include <Graphics/UI/UIManager.h> 

using namespace GamePackage;

MainMenuScene::MainMenuScene(){
}

MainMenuScene::~MainMenuScene(){
}

bool MainMenuScene::Initialize(){
	PizzaBox::RenderEngine::ShowCursor(true);
	SetSky(new PizzaBox::SkyBox("CloudSkybox"));

	PizzaBox::GameObject* mainCamera = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 0.0f, 20.0f), PizzaBox::Euler(-45.0f, 0.0f, 0.0f));
	mainCamera->AddComponent(new PizzaBox::Camera(PizzaBox::ViewportRect::fullScreen, PizzaBox::Camera::RenderMode::Perspective));
	mainCamera->AddComponent(new PizzaBox::AudioListener());
	 
	
	// Background music 
	//mainCamera->AddComponent(new PizzaBox::AudioSource("MainMenuMusic", PizzaBox::AudioSource::SoundType::_2D, "Music"));

	PizzaBox::UIManager::EnableSet("MainMenuSet");
	  
	return true;
}

void MainMenuScene::Destroy(){
	Scene::Destroy();
}