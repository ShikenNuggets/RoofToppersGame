#include "Game.h" 
// Scene Includes
#include "Scenes/LogoScene.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/Level1.h"
// Engine Includes
#include <Core/SceneManager.h>
#include <Core/GameManager.h>
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

	// switch to Option Screen button function 
	auto optionButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e) {
		if (e == PizzaBox::UIEvent::OnRelease) {
			PizzaBox::UIManager::DisableSet("MainMenuSet");
			PizzaBox::UIManager::EnableSet("OptionsSet");
		}
	});

	// Load next scene to start playing
	auto playButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e) {
		if (e == PizzaBox::UIEvent::OnRelease) {
			PizzaBox::SceneManager::LoadNextScene();
		}
	});

	// Quit the game
	auto quitButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e) {
		if (e == PizzaBox::UIEvent::OnRelease) {
			PizzaBox::GameManager::Stop();
		}
	});

	//MainMenuSet
	uiSet = new PizzaBox::UISet("MainMenuSet");
	uiSet->elements.push_back(new PizzaBox::TextUI("GameName", PizzaBox::Rect(0.315f, 0.5f, 0.15f, 0.175f), "Roof Toppers", "ArialFont"));

	uiSet->elements.push_back(new PizzaBox::ButtonUI("PlayButton", playButtonFunc, PizzaBox::Rect(0.4375f, 0.35f, 0.13f, 0.125f)));
	uiSet->elements.push_back(new PizzaBox::TextUI("PlayText", PizzaBox::Rect(0.365f, 0.24f, 0.15f, 0.125f), "Play", "ArialFont"));

	uiSet->elements.push_back(new PizzaBox::ButtonUI("OptionsButton", optionButtonFunc, PizzaBox::Rect(0.422f, 0.25f, 0.165f, 0.125f)));
	uiSet->elements.push_back(new PizzaBox::TextUI("OptionsText", PizzaBox::Rect(0.34f, 0.18f, 0.15f, 0.125f), "Options", "ArialFont"));

	uiSet->elements.push_back(new PizzaBox::ButtonUI("QuitButton", quitButtonFunc, PizzaBox::Rect(0.45f, 0.08f, 0.1f, 0.125f)));
	uiSet->elements.push_back(new PizzaBox::TextUI("QuitText", PizzaBox::Rect(0.365f, 0.08f, 0.15f, 0.125f), "Quit", "ArialFont"));
	PizzaBox::UIManager::AddSet(uiSet);

	//Stats Set
	uiSet = new PizzaBox::UISet("StatsSet");
	uiSet->elements.push_back(new PizzaBox::StatsTextUI("StatsTextUI", PizzaBox::Rect(0.01f, 0.56f, 0.08f, 0.08f), "ArialFont"));
	PizzaBox::UIManager::AddSet(uiSet);

	// switch FullScreen button function 
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
	// switch VSync button function 
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
	// switch back to main menu button function 
	auto backButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e) {
		if (e == PizzaBox::UIEvent::OnRelease) {
			PizzaBox::UIManager::DisableSet("OptionsSet");
			PizzaBox::UIManager::EnableSet("MainMenuSet");
		}
	});

	auto muteMusicButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e) {
		if (e == PizzaBox::UIEvent::OnRelease) { 
		}
	});

	auto muteVolumeButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e) {
		if (e == PizzaBox::UIEvent::OnRelease) { 
		}
	});

	//Options Set
	uiSet = new PizzaBox::UISet("OptionsSet");
	uiSet->elements.push_back(new PizzaBox::TextUI("MenuText", PizzaBox::Rect(0.33f, 0.5f, 0.15f, 0.175f), "Options", "ArialFont"));
	// FullScreen button
	uiSet->elements.push_back(new PizzaBox::ButtonUI("FullscreenButton", fullScreenButtonFunc, PizzaBox::Rect(0.405f, 0.35f, 0.22f, 0.125f)));
	uiSet->elements.push_back(new PizzaBox::TextUI("FullScreenText", PizzaBox::Rect(0.33f, 0.24f, 0.15f, 0.125f), "Fullscreen", "ArialFont"));
	// V-Sync button
	uiSet->elements.push_back(new PizzaBox::ButtonUI("VsyncButton", vsyncButtonFunc, PizzaBox::Rect(0.425f, 0.25f, 0.14f, 0.125f)));
	uiSet->elements.push_back(new PizzaBox::TextUI("VsyncText", PizzaBox::Rect(0.344f, 0.175f, 0.15f, 0.125f), "Vsync", "ArialFont"));
	// Mute Music button																																// TODO - Fix Positioning
	uiSet->elements.push_back(new PizzaBox::ButtonUI("MuteMusicButton", muteMusicButtonFunc, PizzaBox::Rect(0.2f, 0.25f, 0.14f, 0.125f)));
	uiSet->elements.push_back(new PizzaBox::TextUI("MuteMusicText", PizzaBox::Rect(0.344f, 0.175f, 0.15f, 0.125f), "Mute Music", "ArialFont"));
	// Mute Volume button																																// TODO - Fix Positioning
	uiSet->elements.push_back(new PizzaBox::ButtonUI("MuteVolumeButton", muteVolumeButtonFunc, PizzaBox::Rect(0.425f, 0.25f, 0.14f, 0.125f)));
	uiSet->elements.push_back(new PizzaBox::TextUI("MuteVolumeText", PizzaBox::Rect(0.344f, 0.175f, 0.15f, 0.125f), "Mute Volume", "ArialFont"));
	// back to main menu button
	uiSet->elements.push_back(new PizzaBox::ButtonUI("BackButton", backButtonFunc, PizzaBox::Rect(0.8f, 0.1f, 0.12f, 0.12f)));
	uiSet->elements.push_back(new PizzaBox::TextUI("BackText", PizzaBox::Rect(0.65f, 0.085f, 0.15f, 0.125f), "Back", "ArialFont"));

	PizzaBox::UIManager::AddSet(uiSet);
	// Win Set
	// Load MainMenu Scene
	auto TitleButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e) {
		if (e == PizzaBox::UIEvent::OnRelease) {
			PizzaBox::SceneManager::LoadScene(1);
		}
	});
	uiSet = new PizzaBox::UISet("WinSet");
	uiSet->elements.push_back(new PizzaBox::TextUI("MenuText", PizzaBox::Rect(0.33f, 0.5f, 0.15f, 0.175f), "Winner!", "ArialFont", PizzaBox::Color::Orange));
	// FullScreen button
	uiSet->elements.push_back(new PizzaBox::ButtonUI("ReturnButton", TitleButtonFunc, PizzaBox::Rect(0.405f, 0.35f, 0.28f, 0.14f)));
	uiSet->elements.push_back(new PizzaBox::TextUI("ReturnText", PizzaBox::Rect(0.33f, 0.24f, 0.15f, 0.125f), "Back To Title", "ArialFont"));
	// V-Sync button
	uiSet->elements.push_back(new PizzaBox::ButtonUI("QuitButton", quitButtonFunc, PizzaBox::Rect(0.425f, 0.15f, 0.14f, 0.125f)));
	uiSet->elements.push_back(new PizzaBox::TextUI("QuitText", PizzaBox::Rect(0.344f, 0.12f, 0.15f, 0.125f), "Quit", "ArialFont"));

	PizzaBox::UIManager::AddSet(uiSet);

	// Death Set 
	auto RestartButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e) {
		if (e == PizzaBox::UIEvent::OnRelease) { 
			PizzaBox::SceneManager:ReloadCurrentScene();
		}
	});
	uiSet = new PizzaBox::UISet("DeathSet");
	uiSet->elements.push_back(new PizzaBox::TextUI("MenuText", PizzaBox::Rect(0.33f, 0.5f, 0.15f, 0.175f), "You Died!", "ArialFont", PizzaBox::Color::Red));
	// Restart button
	uiSet->elements.push_back(new PizzaBox::ButtonUI("ReturnButton", RestartButtonFunc, PizzaBox::Rect(0.405f, 0.35f, 0.22f, 0.14f)));
	uiSet->elements.push_back(new PizzaBox::TextUI("ReturnText", PizzaBox::Rect(0.33f, 0.24f, 0.15f, 0.125f), "Restart", "ArialFont"));
	// Quit button
	uiSet->elements.push_back(new PizzaBox::ButtonUI("QuitButton", quitButtonFunc, PizzaBox::Rect(0.425f, 0.15f, 0.14f, 0.125f)));
	uiSet->elements.push_back(new PizzaBox::TextUI("QuitText", PizzaBox::Rect(0.344f, 0.12f, 0.15f, 0.125f), "Quit", "ArialFont"));

	PizzaBox::UIManager::AddSet(uiSet);
	
	//Add scenes to the SceneManager 
	PizzaBox::SceneManager::AddScene(new LogoScene());
	PizzaBox::SceneManager::AddScene(new MainMenuScene());
	PizzaBox::SceneManager::AddScene(new Level1());

	return true;
}

void Game::Destroy(){
}