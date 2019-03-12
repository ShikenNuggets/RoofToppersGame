#include "Game.h" 
// Scene Includes
#include "Scenes/LogoScene.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/Level1.h"
// Engine Includes
#include <Core/SceneManager.h>
#include <Core/Time.h>
#include <Input/InputManager.h>
#include <Graphics/RenderEngine.h>
#include <Graphics/UI/ButtonUI.h>
#include <Graphics/UI/ImageUI.h>
#include <Graphics/UI/UIManager.h>
#include <Graphics/UI/StatsTextUI.h>
#include <Audio/AudioManager.h>
#include <Resource/ResourceManager.h>

using namespace GamePackage;

Game::Game(const std::string name_) : GameInterface(name_){
}

Game::~Game(){
}

bool Game::Initialize(){
	PizzaBox::ResourceManager::LoadResource<PizzaBox::AudioResource>("GameplayMusic1");
	PizzaBox::ResourceManager::LoadResource<PizzaBox::AudioResource>("WalkingSFX");
	PizzaBox::ResourceManager::LoadResource<PizzaBox::AudioResource>("GrappleSFX");
	PizzaBox::ResourceManager::LoadResource<PizzaBox::AudioResource>("SwingingSFX");
	PizzaBox::ResourceManager::LoadResource<PizzaBox::AudioResource>("LandingSFX");
	PizzaBox::ResourceManager::LoadResource<PizzaBox::AudioResource>("JumpingSFX");
	PizzaBox::ResourceManager::LoadResource<PizzaBox::AudioResource>("WavesSFX");
	PizzaBox::ResourceManager::LoadResource<PizzaBox::AudioResource>("SplashSFX");

	PizzaBox::RenderEngine::SetWindowResolution(1280, 720);
	PizzaBox::RenderEngine::SetWindowBorderless(false);
	PizzaBox::RenderEngine::SetVSYNC(PizzaBox::Window::VSYNC::On);
	PizzaBox::Time::SetFrameRate(60);

	//Audio Channels
	//PizzaBox::AudioManager::CreateVolumeChannel("Music");
	/*
	//Logo
	PizzaBox::UISet* uiSet = new PizzaBox::UISet("LogoSet");
	PizzaBox::ImageUI* logo = new PizzaBox::ImageUI("Logo", "LogoHDImage", PizzaBox::Rect(0.0f, 0.0f, 1.0f, 1.0f));
	uiSet->elements.push_back(logo);
	PizzaBox::UIManager::AddSet(uiSet);

	//MainMenuSet
	uiSet = new PizzaBox::UISet("MainMenuSet");
	uiSet->elements.push_back(new PizzaBox::TextUI("GameName", PizzaBox::Rect(0.35, 0.5, 0.1, 0.125), "Protype Name", "ArialFont"));
	uiSet->elements.push_back(new PizzaBox::ButtonUI("PlayButton", PizzaBox::Rect(0.425, 0.35, 0.15, 0.125)));
	uiSet->elements.push_back(new PizzaBox::ButtonUI("QuitButton", PizzaBox::Rect(0.425, 0.2, 0.15, 0.125)));
	PizzaBox::UIManager::AddSet(uiSet);
	*/
	//Add scenes to the SceneManager 
	//PizzaBox::SceneManager::AddScene(new LogoScene());
	//PizzaBox::SceneManager::AddScene(new MainMenuScene());
	PizzaBox::SceneManager::AddScene(new Level1());
	PizzaBox::AudioManager::CreateVolumeChannel("Music");
	PizzaBox::AudioManager::CreateVolumeChannel("SFX");
	return true;
}

void Game::Destroy(){
	PizzaBox::ResourceManager::UnloadResource("GameplayMusic1");
	PizzaBox::ResourceManager::UnloadResource("WalkingSFX");
	PizzaBox::ResourceManager::UnloadResource("GrappleSFX");
	PizzaBox::ResourceManager::UnloadResource("SwingingSFX");
	PizzaBox::ResourceManager::UnloadResource("LandingSFX");
	PizzaBox::ResourceManager::UnloadResource("JumpingSFX");
	PizzaBox::ResourceManager::UnloadResource("WavesSFX");
	PizzaBox::ResourceManager::UnloadResource("SplashSFX");
}