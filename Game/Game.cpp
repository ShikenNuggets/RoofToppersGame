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
	//PizzaBox::RenderEngine::SetWindowResolution(1280, 720);
	//PizzaBox::RenderEngine::SetWindowBorderless(false);
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
	uiSet->elements.push_back(new PizzaBox::ButtonUI("OptionsButton", PizzaBox::Rect(0.425f, 0.2f, 0.16f, 0.125f)));
	uiSet->elements.push_back(new PizzaBox::TextUI("OptionsText", PizzaBox::Rect(0.34f, 0.15f, 0.15f, 0.125f), "Options", "ArialFont"));
	PizzaBox::UIManager::AddSet(uiSet);

	//Stats Set
	uiSet = new PizzaBox::UISet("StatsSet");
	uiSet->elements.push_back(new PizzaBox::StatsTextUI("StatsTextUI", PizzaBox::Rect(0.01f, 0.56f, 0.08f, 0.08f), "ArialFont"));
	PizzaBox::UIManager::AddSet(uiSet);

	auto fullScreenButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e){
		if(e == PizzaBox::UIEvent::OnRelease){
			if(PizzaBox::RenderEngine::GetWindowBorderless()){
				PizzaBox::RenderEngine::SetWindowResolution(1280, 720);
				PizzaBox::RenderEngine::SetWindowBorderless(false);
			}else{
				PizzaBox::RenderEngine::SetWindowResolution(1920, 1080);
				PizzaBox::RenderEngine::SetWindowBorderless(true);
			}
		}
	});

	auto vsyncButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e){
		if(e == PizzaBox::UIEvent::OnRelease){
			if(PizzaBox::RenderEngine::GetVSYNC() == PizzaBox::Window::VSYNC::Off){
				PizzaBox::Debug::Log("Enable VSYNC");
				PizzaBox::RenderEngine::SetVSYNC(PizzaBox::Window::VSYNC::On);
			}else{
				PizzaBox::Debug::Log("Disable VSYNC");
				PizzaBox::RenderEngine::SetVSYNC(PizzaBox::Window::VSYNC::Off);
			}
		}
	});

	//Options Set
	uiSet = new PizzaBox::UISet("OptionsSet");
	uiSet->elements.push_back(new PizzaBox::TextUI("MenuText", PizzaBox::Rect(0.33f, 0.5f, 0.15f, 0.175f), "Options", "ArialFont"));
	uiSet->elements.push_back(new PizzaBox::ButtonUI("FullscreenButton", fullScreenButtonFunc, PizzaBox::Rect(0.41f, 0.35f, 0.22f, 0.125f)));
	uiSet->elements.push_back(new PizzaBox::TextUI("FullScreenText", PizzaBox::Rect(0.33f, 0.24f, 0.15f, 0.125f), "Fullscreen", "ArialFont"));

	uiSet->elements.push_back(new PizzaBox::ButtonUI("VsyncButton", vsyncButtonFunc, PizzaBox::Rect(0.425f, 0.25f, 0.15f, 0.125f)));
	uiSet->elements.push_back(new PizzaBox::TextUI("VsyncText", PizzaBox::Rect(0.342f, 0.175f, 0.15f, 0.125f), "Vsync", "ArialFont"));

	PizzaBox::UIManager::AddSet(uiSet);
	
	//Add scenes to the SceneManager 
	//PizzaBox::SceneManager::AddScene(new LogoScene());
	PizzaBox::SceneManager::AddScene(new MainMenuScene());
	PizzaBox::SceneManager::AddScene(new Level1());

	return true;
}

void Game::Destroy(){
}