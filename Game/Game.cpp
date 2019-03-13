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
	
	//Logo
	PizzaBox::UISet* uiSet = new PizzaBox::UISet("LogoSet");
	PizzaBox::ImageUI* logo = new PizzaBox::ImageUI("Logo", "LogoHDImage", PizzaBox::Rect(0.0f, 0.0f, 1.0f, 1.0f));
	uiSet->elements.push_back(logo);
	PizzaBox::UIManager::AddSet(uiSet);

	PizzaBox::ButtonUI* button;

	// Quit the game
	auto quitButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e) {
		if (e == PizzaBox::UIEvent::OnRelease) {
			PizzaBox::GameManager::Stop();
		}
	});

	// MainMenuSet
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
		 
		//MainMenuSet
		uiSet = new PizzaBox::UISet("MainMenuSet");
		uiSet->elements.push_back(new PizzaBox::TextUI("GameName", PizzaBox::Rect(0.5f, 0.8f, 0.15f, 0.175f), true, "Roof Toppers", "ArialFont"));

		button = new PizzaBox::ButtonUI("PlayButton", playButtonFunc,		PizzaBox::Rect(0.55f, 0.4f, 0.16f, 0.12f));
		button->AddText("Play");
		uiSet->elements.push_back(button); 

		button = new PizzaBox::ButtonUI("OptionsButton", optionButtonFunc,	PizzaBox::Rect(0.55f, 0.25f, 0.16f, 0.12f));
		button->AddText("Options");
		uiSet->elements.push_back(button); 

		button = new PizzaBox::ButtonUI("QuitButton", quitButtonFunc,		PizzaBox::Rect(0.55f, 0.1f, 0.16f, 0.12f));
		button->AddText("Quit");
		uiSet->elements.push_back(button); 

		PizzaBox::UIManager::AddSet(uiSet);

	// Stats Set
	{
		uiSet = new PizzaBox::UISet("StatsSet");
		uiSet->elements.push_back(new PizzaBox::StatsTextUI("StatsTextUI", PizzaBox::Rect(0.08f, 0.95f, 0.04f, 0.04f), "ArialFont"));
		PizzaBox::UIManager::AddSet(uiSet);
	}

	// Options Set
		// switch FullScreen button function 
		auto fullScreenButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e) {
			if (e == PizzaBox::UIEvent::OnRelease) {
				if (PizzaBox::RenderEngine::GetWindowBorderless()) {
					PizzaBox::RenderEngine::SetWindowResolution(1280, 720);
					PizzaBox::RenderEngine::SetWindowBorderless(false);
				}
				else {
					PizzaBox::RenderEngine::SetWindowResolution(1920, 1080);
					PizzaBox::RenderEngine::SetWindowBorderless(true);
				}
			}
		});
		// switch VSync button function 
		auto vsyncButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e) {
			if (e == PizzaBox::UIEvent::OnRelease) {
				if (PizzaBox::RenderEngine::GetVSYNC() == PizzaBox::Window::VSYNC::Off) {
					PizzaBox::Debug::Log("Enable VSYNC");
					PizzaBox::RenderEngine::SetVSYNC(PizzaBox::Window::VSYNC::On);
				}
				else {
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
		uiSet->elements.push_back(new PizzaBox::TextUI("MenuText", PizzaBox::Rect(0.6f, 0.85f, 0.15f, 0.175f), true, "Options", "ArialFont"));

		// FullScreen button
		button = new PizzaBox::ButtonUI("FullscreenButton", fullScreenButtonFunc, PizzaBox::Rect(0.55f, 0.45f, 0.15f, 0.125f));
		button->AddText("Fullscreen");
		uiSet->elements.push_back(button); 

		// V-Sync button
		button = new PizzaBox::ButtonUI("VsyncButton", vsyncButtonFunc, PizzaBox::Rect(0.55f, 0.35f, 0.15f, 0.125f));
		button->AddText("Vsync");
		uiSet->elements.push_back(button); 

		// Mute Music button																			// TODO - Add button Func
		button = new PizzaBox::ButtonUI("MuteMusicButton", muteMusicButtonFunc, PizzaBox::Rect(0.55f, 0.25f, 0.15f, 0.125f));
		button->AddText("Mute Music");
		uiSet->elements.push_back(button); 

		// Mute Volume button																			// TODO - Add button Func
		button = new PizzaBox::ButtonUI("MuteVolumeButton", muteVolumeButtonFunc, PizzaBox::Rect(0.55f, 0.15f, 0.15f, 0.125f));
		button->AddText("Mute Volume");
		uiSet->elements.push_back(button); 

		// back to main menu button
		button = new PizzaBox::ButtonUI("BackButton", backButtonFunc, PizzaBox::Rect(0.9f, 0.1f, 0.1f, 0.1f));
		button->AddText("Back");
		uiSet->elements.push_back(button); 

		PizzaBox::UIManager::AddSet(uiSet);

	// Win Set
		// Load MainMenu Scene
		auto TitleButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e) {
			if (e == PizzaBox::UIEvent::OnRelease) {
				PizzaBox::SceneManager::LoadScene(1);
			}
		});
		uiSet = new PizzaBox::UISet("WinSet");
		uiSet->elements.push_back(new PizzaBox::TextUI("MenuText", PizzaBox::Rect(0.65f, 0.8f, 0.15f, 0.175f), true, "Winner!", "ArialFont"));

		// FullScreen button
		button = new PizzaBox::ButtonUI("ReturnButton", TitleButtonFunc, PizzaBox::Rect(0.65f, 0.45f, 0.28f, 0.14f));
		button->AddText("Back To Title");
		uiSet->elements.push_back(button); 

		// V-Sync button
		button = new PizzaBox::ButtonUI("QuitButton", quitButtonFunc, PizzaBox::Rect(0.65f, 0.25f, 0.14f, 0.125f));
		button->AddText("Quit");
		uiSet->elements.push_back(button); 

		PizzaBox::UIManager::AddSet(uiSet);

	// Death Set 
		auto RestartButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e) {
			if (e == PizzaBox::UIEvent::OnRelease) {
				PizzaBox::SceneManager::ReloadCurrentScene();
			}
		});
		uiSet = new PizzaBox::UISet("DeathSet");
		uiSet->elements.push_back(new PizzaBox::TextUI("MenuText", PizzaBox::Rect(0.65f, 0.8f, 0.15f, 0.175f), true, "You Died!", "ArialFont"));

		// Restart button
		button = new PizzaBox::ButtonUI("ReturnButton", RestartButtonFunc, PizzaBox::Rect(0.65f, 0.45f, 0.22f, 0.14f));
		button->AddText("Restart");
		uiSet->elements.push_back(button); 

		// Quit button
		button = new PizzaBox::ButtonUI("QuitButton", quitButtonFunc, PizzaBox::Rect(0.65f, 0.25f, 0.14f, 0.125f));
		button->AddText("Quit");
		uiSet->elements.push_back(button); 

		PizzaBox::UIManager::AddSet(uiSet);
	
	// Pause Set 
		/*auto RestartButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e) {
			if (e == PizzaBox::UIEvent::OnRelease) {
				PizzaBox::SceneManager::ReloadCurrentScene();
			}
		});
		auto optionButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e) {
			if (e == PizzaBox::UIEvent::OnRelease) {
				PizzaBox::UIManager::DisableSet("PauseSet");
				PizzaBox::UIManager::EnableSet("OptionsSet");
			}
		});*/

		uiSet = new PizzaBox::UISet("PauseSet");
		uiSet->elements.push_back(new PizzaBox::TextUI("MenuText", PizzaBox::Rect(0.65f, 0.8f, 0.15f, 0.175f), true, "Pause!", "ArialFont"));

		// Restart button
		button = new PizzaBox::ButtonUI("ReturnButton", RestartButtonFunc, PizzaBox::Rect(0.65f, 0.45f, 0.22f, 0.14f));
		button->AddText("Restart");
		uiSet->elements.push_back(button);

		button = new PizzaBox::ButtonUI("OptionsButton", optionButtonFunc, PizzaBox::Rect(0.65f, 0.30f, 0.16f, 0.12f));
		button->AddText("Options");
		uiSet->elements.push_back(button);

		// Quit button
		button = new PizzaBox::ButtonUI("QuitButton", quitButtonFunc, PizzaBox::Rect(0.65f, 0.15f, 0.14f, 0.125f));
		button->AddText("Quit");
		uiSet->elements.push_back(button);

		PizzaBox::UIManager::AddSet(uiSet);

	// Tutorial Set
		uiSet = new PizzaBox::UISet("TutorialSet");

		std::string text;
		text = "W A S D to move";
		uiSet->elements.push_back(new PizzaBox::TextUI("TutorialText", PizzaBox::Rect(0.1f, 0.85f, 0.04f, 0.05f), true, text, "ArialFont"));

		text = "Space To Jump";
		uiSet->elements.push_back(new PizzaBox::TextUI("TutorialText", PizzaBox::Rect(0.1f, 0.8f, 0.04f, 0.05f), true, text, "ArialFont"));

		text = "Left Click to grapple to that yellow thing";
		uiSet->elements.push_back(new PizzaBox::TextUI("TutorialText", PizzaBox::Rect(0.1f, 0.75f, 0.04f, 0.05f), true, text, "ArialFont"));
		 
		PizzaBox::UIManager::AddSet(uiSet);

	//Add scenes to the SceneManager 
	PizzaBox::SceneManager::AddScene(new LogoScene());
	PizzaBox::SceneManager::AddScene(new MainMenuScene());
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