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
//#include <Audio/AudioManager.h>

using namespace GamePackage;

Game::Game(const std::string name_) : GameInterface(name_){
}

Game::~Game(){
}

bool Game::Initialize(){ 
	PizzaBox::RenderEngine::SetWindowResolution(1280, 720);
	PizzaBox::RenderEngine::SetWindowBorderless(false);
	PizzaBox::RenderEngine::SetVSYNC(PizzaBox::Window::VSYNC::Off);
	PizzaBox::Time::SetFrameRate(0);

	//Audio Channels
	//PizzaBox::AudioManager::CreateVolumeChannel("Music");
	
	//Logo
	PizzaBox::UISet* uiSet = new PizzaBox::UISet("LogoSet");
	PizzaBox::ImageUI* logo = new PizzaBox::ImageUI("Logo", "LogoHDImage", PizzaBox::Rect(0.0f, 0.0f, 1.0f, 1.0f));
	uiSet->elements.push_back(logo);
	PizzaBox::UIManager::AddSet(uiSet);

	//MainMenuSet
	uiSet = new PizzaBox::UISet("MainMenuSet");
	uiSet->elements.push_back(new PizzaBox::TextUI("GameName", PizzaBox::Rect(0.325f, 0.5f, 0.15f, 0.175f), "Roof Toppers", "ArialFont"));
	uiSet->elements.push_back(new PizzaBox::ButtonUI("PlayButton", PizzaBox::Rect(0.425f, 0.35f, 0.15f, 0.125f)));
	uiSet->elements.push_back(new PizzaBox::TextUI("PlayText", PizzaBox::Rect(0.36f, 0.24f, 0.15f, 0.125f), "Play", "ArialFont"));
	uiSet->elements.push_back(new PizzaBox::ButtonUI("QuitButton", PizzaBox::Rect(0.425f, 0.2f, 0.15f, 0.125f)));
	uiSet->elements.push_back(new PizzaBox::TextUI("QuitText", PizzaBox::Rect(0.36f, 0.15f, 0.15f, 0.125f), "Quit", "ArialFont"));
	PizzaBox::UIManager::AddSet(uiSet);
	
	//Add scenes to the SceneManager 
	//PizzaBox::SceneManager::AddScene(new LogoScene());
	PizzaBox::SceneManager::AddScene(new MainMenuScene());
	PizzaBox::SceneManager::AddScene(new Level1());

	return true;
}

void Game::Destroy(){
}