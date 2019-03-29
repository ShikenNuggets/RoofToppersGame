#include "MainMenuScene.h"

#include <Audio/AudioListener.h>
#include <Audio/AudioSource.h>
#include <Graphics/RenderEngine.h>
#include <Graphics/Sky/SkyBox.h>
#include <Graphics/UI/UIManager.h> 
#include "Scripts/MusicScript.h"

using namespace GamePackage;

MainMenuScene::MainMenuScene(){
}

MainMenuScene::~MainMenuScene(){
}

bool MainMenuScene::Initialize(){
	PizzaBox::RenderEngine::SetFogDensity(0.0f);
	PizzaBox::RenderEngine::SetWaterFogDensity(0.0f);

	//Music
	auto mmu1 = new PizzaBox::AudioSource("MenuMusic", PizzaBox::AudioSource::SoundType::_2D, "Music");
	PizzaBox::GameObject* music = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 55.0f, 80.0f), PizzaBox::Euler(-15.0f, 0.0f, 0.0f));
	music->AddComponent(mmu1);
	music->AddComponent(new MusicScript(mmu1));

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