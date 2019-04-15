#include "Game.h" 
// Scene Includes
#include "Scenes/LogoScene.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/Level1.h"
// Engine Includes
#include <Core/Config.h>
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

#include "Scripts/GameController.h"
#include "UI/IGT.h"

using namespace GamePackage;

Game::Game(const std::string name_) : GameInterface(name_){
}

Game::~Game(){
}

bool Game::Initialize(){
	PizzaBox::RenderEngine::SetVSYNC(PizzaBox::Window::VSYNC::On);
	//PizzaBox::RenderEngine::SetFogDensity(0.0003f);
	//PizzaBox::RenderEngine::SetWaterFogDensity(0.00001f);
	PizzaBox::Time::SetFrameRate(999);

	SetupLogoUI();
	SetupStatsUI();
	SetupMainMenuUI();
	SetupOptionsUI();
	SetupCreditsUI();
	SetupTutorialUI();
	SetupPauseUI();
	SetupWinUI();
	SetupDeathUI();
	SetupLoadingUI();

	if(!PizzaBox::Config::SettingExists("ControlUIType")){
		PizzaBox::Config::SetInt("ControlUIType", 0); //0 = PS4 (default), 1 = Xbox
	}

	if(!PizzaBox::Config::SettingExists("MouseSensitivity")){
		PizzaBox::Config::SetInt("MouseSensitivity", 500); //Has to be an int due to how the config system works
	}

	//Audio Channels
	//PizzaBox::AudioManager::CreateVolumeChannel("Music");

	//Add scenes to the SceneManager 
	PizzaBox::SceneManager::AddScene(new LogoScene());
	PizzaBox::SceneManager::AddScene(new MainMenuScene());
	PizzaBox::SceneManager::AddScene(new Level1());
	PizzaBox::AudioManager::CreateVolumeChannel("Music");
	PizzaBox::AudioManager::CreateVolumeChannel("SFX");
	return true;
}

void Game::Destroy(){
}

void Game::SetupLogoUI(){
	PizzaBox::UISet* uiSet = new PizzaBox::UISet("LogoSet");
	uiSet->AddElement(new PizzaBox::ImageUI("Logo", "LogoHDImage", PizzaBox::Rect(0.5f, 0.5f, 1.0f, 1.0f)));
	PizzaBox::UIManager::AddSet(uiSet);
}

void Game::SetupStatsUI(){
	auto uiSet = new PizzaBox::UISet("StatsSet");

	auto image = new PizzaBox::ImageUI("StatsImage", "BlackTexture", PizzaBox::Rect(0.09f, 0.925f, 0.175f, 0.095f));
	image->SetTransparency(0.25f);
	uiSet->AddElement(image);

	PizzaBox::TextUI* text = new PizzaBox::StatsTextUI("StatsTextUI", PizzaBox::Rect(0.075f, 0.92f, 0.12f, 0.05f), "ArialFont");
	text->SetColor(PizzaBox::Color::Yellow);
	uiSet->AddElement(text);

	text = new IGT("IGTText", PizzaBox::Rect(0.075f, 0.87f, 0.05f, 0.05f), "ArialFont");
	text->SetColor(PizzaBox::Color::Yellow);
	uiSet->AddElement(text);

	PizzaBox::UIManager::AddSet(uiSet);
}

void Game::SetupMainMenuUI(){
	auto playButtonFunc = UIEventFunc([](PizzaBox::UIEvent e){
		if(e == PizzaBox::UIEvent::OnRelease){
			PizzaBox::UIManager::DisableAllSets();
			PizzaBox::UIManager::EnableSet("LoadingSet");
			PizzaBox::SceneManager::LoadNextScene();
		}
	});

	auto optionButtonFunc = UIEventFunc([](PizzaBox::UIEvent e){
		if(e == PizzaBox::UIEvent::OnRelease){
			PizzaBox::UIManager::DisableSet("MainMenuSet");
			PizzaBox::UIManager::EnableSet("OptionsSet");
		}
	});

	auto creditsButtonFunc = UIEventFunc([](PizzaBox::UIEvent e){
		if(e == PizzaBox::UIEvent::OnRelease){
			PizzaBox::UIManager::DisableSet("MainMenuSet");
			PizzaBox::UIManager::EnableSet("CreditsSet");
		}
	});

	auto quitButtonFunc = UIEventFunc([](PizzaBox::UIEvent e){
		if(e == PizzaBox::UIEvent::OnRelease){
			PizzaBox::GameManager::Stop();
		}
	});

	auto uiSet = new PizzaBox::UISet("MainMenuSet");
	uiSet->AddElement(new PizzaBox::ImageUI("GameLogo", "GameLogo", PizzaBox::Rect(0.5f, 0.8f, 0.4f, 0.2f)));
	//uiSet->AddElement(new PizzaBox::TextUI("GameName", PizzaBox::Rect(0.5f, 0.8f, 0.3f, 0.15f), true, "Roof Toppers", "ArialFont"));

	auto button = new PizzaBox::ButtonUI("PlayButton", playButtonFunc, PizzaBox::Rect(0.5f, 0.475f, 0.15f, 0.1f));
	button->AddText("Play");
	uiSet->AddElement(button);

	button = new PizzaBox::ButtonUI("OptionsButton", optionButtonFunc, PizzaBox::Rect(0.5f, 0.35f, 0.15f, 0.1f));
	button->AddText("Options");
	uiSet->AddElement(button);

	button = new PizzaBox::ButtonUI("CreditsButton", creditsButtonFunc, PizzaBox::Rect(0.5f, 0.225f, 0.15f, 0.1f));
	button->AddText("Credits");
	uiSet->AddElement(button);

	button = new PizzaBox::ButtonUI("QuitButton", quitButtonFunc, PizzaBox::Rect(0.5f, 0.1f, 0.15f, 0.1f));
	button->AddText("Quit Game");
	uiSet->AddElement(button);

	PizzaBox::UIManager::AddSet(uiSet);
}

void Game::SetupOptionsUI(){
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

	auto backButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e){
		if(e == PizzaBox::UIEvent::OnRelease){
			PizzaBox::UIManager::DisableSet("OptionsSet");
			PizzaBox::UIManager::EnableSet("MainMenuSet");
		}
	});

	auto muteMusicButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e){
		if(e == PizzaBox::UIEvent::OnRelease){
			if(PizzaBox::AudioManager::GetVolume("Music") > 0.0f){
				PizzaBox::AudioManager::SetVolume("Music", 0.0f);
			}else{
				PizzaBox::AudioManager::SetVolume("Music", 1.0f);
			}
		}
	});

	auto muteVolumeButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e){
		if(e == PizzaBox::UIEvent::OnRelease){
			if(PizzaBox::AudioManager::GetVolume("SFX") > 0.0f){
				PizzaBox::AudioManager::SetVolume("SFX", 0.0f);
			} else{
				PizzaBox::AudioManager::SetVolume("SFX", 1.0f);
			}
		}
	});

	auto uiSet = new PizzaBox::UISet("OptionsSet");
	uiSet->AddElement(new PizzaBox::ImageUI("OptionsLogo", "OptionsLogo", PizzaBox::Rect(0.5f, 0.8f, 0.4f, 0.2f)));
	//uiSet->AddElement(new PizzaBox::TextUI("MenuText", PizzaBox::Rect(0.5f, 0.75f, 0.15f, 0.175f), true, "Options", "ArialFont"));

	auto button = new PizzaBox::ButtonUI("FullscreenButton", fullScreenButtonFunc, PizzaBox::Rect(0.5f, 0.5f, 0.15f, 0.1f));
	button->AddText("Fullscreen");
	uiSet->AddElement(button);

	button = new PizzaBox::ButtonUI("VsyncButton", vsyncButtonFunc, PizzaBox::Rect(0.5f, 0.38f, 0.15f, 0.1f));
	button->AddText("Vsync");
	uiSet->AddElement(button);

	button = new PizzaBox::ButtonUI("MuteMusicButton", muteMusicButtonFunc, PizzaBox::Rect(0.5f, 0.26f, 0.15f, 0.1f));
	button->AddText("Mute Music");
	uiSet->AddElement(button);

	button = new PizzaBox::ButtonUI("MuteVolumeButton", muteVolumeButtonFunc, PizzaBox::Rect(0.5f, 0.14f, 0.15f, 0.1f));
	button->AddText("Mute Volume");
	uiSet->AddElement(button);

	button = new PizzaBox::ButtonUI("BackButton", backButtonFunc, PizzaBox::Rect(0.9f, 0.1f, 0.1f, 0.1f));
	button->AddText("Back");
	button->SetReceivesBackInput(true);
	uiSet->AddElement(button);

	PizzaBox::UIManager::AddSet(uiSet);
}

void Game::SetupCreditsUI(){
	auto backButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e){
		if(e == PizzaBox::UIEvent::OnRelease){
			PizzaBox::UIManager::DisableSet("CreditsSet");
			PizzaBox::UIManager::EnableSet("MainMenuSet");
		}
	});

	auto uiSet = new PizzaBox::UISet("CreditsSet");
	uiSet->AddElement(new PizzaBox::ImageUI("CreditsLogo", "CreditsLogo", PizzaBox::Rect(0.5f, 0.8f, 0.4f, 0.2f)));

	auto image = new PizzaBox::ImageUI("CreditsPanel", "BlackTexture", PizzaBox::Rect(0.5f, 0.4f, 0.35f, 0.45f));
	image->SetTransparency(0.5f);
	uiSet->AddElement(image);

	auto text = new PizzaBox::TextUI("CreditsText0", PizzaBox::Rect(0.485f, 0.55f, 0.2f, 0.075f), false, "PizzaBox Engine Team:", "ArialFont");
	uiSet->AddElement(text);

	text = new PizzaBox::TextUI("CreditsText1", PizzaBox::Rect(0.485f, 0.5f, 0.125f, 0.075f), false, "Carter Rennick", "ArialFont");
	uiSet->AddElement(text);

	text = new PizzaBox::TextUI("CreditsText2", PizzaBox::Rect(0.46f, 0.45f, 0.075f, 0.075f), false, "Devon Ly", "ArialFont");
	uiSet->AddElement(text);

	text = new PizzaBox::TextUI("CreditsText3", PizzaBox::Rect(0.485f, 0.4f, 0.125f, 0.075f), false, "Jared Fukumoto", "ArialFont");
	uiSet->AddElement(text);

	text = new PizzaBox::TextUI("CreditsText4", PizzaBox::Rect(0.485f, 0.35f, 0.125f, 0.075f), false, "Sean Gallagher", "ArialFont");
	uiSet->AddElement(text);

	text = new PizzaBox::TextUI("CreditsText5", PizzaBox::Rect(0.485f, 0.25f, 0.21f, 0.06f), false, "Art and Animations gathered online", "ArialFont");
	uiSet->AddElement(text);

	text = new PizzaBox::TextUI("CreditsText6", PizzaBox::Rect(0.485f, 0.2f, 0.18f, 0.06f), false, "SFX and Music by Sean", "ArialFont");
	uiSet->AddElement(text);

	auto button = new PizzaBox::ButtonUI("BackButton", backButtonFunc, PizzaBox::Rect(0.9f, 0.1f, 0.1f, 0.1f));
	button->AddText("Back");
	button->SetReceivesBackInput(true);
	uiSet->AddElement(button);

	PizzaBox::UIManager::AddSet(uiSet);
}

void Game::SetupTutorialUI(){
	auto uiSet = new PizzaBox::UISet("TutorialSet");

	uiSet->AddElement(new PizzaBox::ImageUI("XImage", "XImage", PizzaBox::Rect(0.8f, 0.2f, 0.28125000000000012304687500000005f / 8.0f, 0.5f / 8.0f)));
	uiSet->AddElement(new PizzaBox::TextUI("XText", PizzaBox::Rect(0.86f, 0.15f, 0.07f, 0.0725f), false, " to jump", "ArialFont"));

	uiSet->AddElement(new PizzaBox::ImageUI("CircleImage", "CircleImage", PizzaBox::Rect(0.8f, 0.1f, 0.28125000000000012304687500000005f / 8.0f, 0.5f / 8.0f)));
	uiSet->AddElement(new PizzaBox::TextUI("CircleText", PizzaBox::Rect(0.87f, 0.05f, 0.095f, 0.08f), false, " to swing", "ArialFont"));

	uiSet->AddElement(new PizzaBox::ImageUI("AImage", "AImage", PizzaBox::Rect(0.8f, 0.2f, 0.28125000000000012304687500000005f / 8.0f, 0.5f / 8.0f)));
	uiSet->AddElement(new PizzaBox::ImageUI("BImage", "BImage", PizzaBox::Rect(0.8f, 0.1f, 0.28125000000000012304687500000005f / 8.0f, 0.5f / 8.0f)));

	PizzaBox::UIManager::AddSet(uiSet);
}

void Game::SetupPauseUI(){
	auto continueButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e){
		if(e == PizzaBox::UIEvent::OnRelease){
			auto gc = PizzaBox::SceneManager::CurrentScene()->GetComponentInScene<GameController>();
			if(gc != nullptr){
				gc->TogglePause();
			}
		}
	});

	auto restartButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e){
		if(e == PizzaBox::UIEvent::OnRelease){
			auto gc = PizzaBox::SceneManager::CurrentScene()->GetComponentInScene<GameController>();
			if(gc != nullptr){
				gc->ResetScene();
			}
		}
	});

	auto titleButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e){
		if(e == PizzaBox::UIEvent::OnRelease){
			PizzaBox::UIManager::DisableAllSets();
			PizzaBox::UIManager::EnableSet("LoadingSet");
			PizzaBox::Time::SetTimeScale(1.0f);
			PizzaBox::SceneManager::LoadScene(1);
		}
	});

	auto uiSet = new PizzaBox::UISet("PauseSet");
	uiSet->AddElement(new PizzaBox::ImageUI("PauseLogo", "PauseLogo", PizzaBox::Rect(0.5f, 0.8f, 0.4f, 0.2f)));
	//uiSet->elements.push_back(new PizzaBox::TextUI("MenuText", PizzaBox::Rect(0.5f, 0.8f, 0.25f, 0.175f), true, "Game Paused", "ArialFont"));

	auto button = new PizzaBox::ButtonUI("ContinueButton", continueButtonFunc, PizzaBox::Rect(0.5f, 0.45f, 0.18f, 0.1f));
	button->AddText("Continue");
	button->SetReceivesBackInput(true);
	uiSet->elements.push_back(button);

	button = new PizzaBox::ButtonUI("RestartButton", restartButtonFunc, PizzaBox::Rect(0.5f, 0.30f, 0.18f, 0.1f));
	button->AddText("Restart Level");
	uiSet->elements.push_back(button);

	button = new PizzaBox::ButtonUI("QuitToMenu", titleButtonFunc, PizzaBox::Rect(0.5f, 0.15f, 0.18f, 0.1f));
	button->AddText("Quit to Menu");
	uiSet->elements.push_back(button);

	PizzaBox::UIManager::AddSet(uiSet);
}

void Game::SetupWinUI(){
	auto titleButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e){
		if(e == PizzaBox::UIEvent::OnRelease){
			PizzaBox::UIManager::DisableAllSets();
			PizzaBox::UIManager::EnableSet("LoadingSet");
			PizzaBox::SceneManager::LoadScene(1);
		}
	});

	auto quitButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e){
		if(e == PizzaBox::UIEvent::OnRelease){
			PizzaBox::GameManager::Stop();
		}
	});
	
	auto uiSet = new PizzaBox::UISet("WinSet");
	uiSet->AddElement(new PizzaBox::ImageUI("WinLogo", "WinLogo", PizzaBox::Rect(0.5f, 0.8f, 0.4f, 0.2f)));
	//uiSet->elements.push_back(new PizzaBox::TextUI("MenuText", PizzaBox::Rect(0.5f, 0.8f, 0.15f, 0.1f), true, "You Win!", "ArialFont"));

	auto button = new PizzaBox::ButtonUI("ReturnButton", titleButtonFunc, PizzaBox::Rect(0.5f, 0.4f, 0.18f, 0.1f));
	button->AddText("Back To Title");
	button->SetReceivesBackInput(true);
	uiSet->elements.push_back(button);

	PizzaBox::UIManager::AddSet(uiSet);
}

void Game::SetupDeathUI(){
	auto restartButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e){
		if(e == PizzaBox::UIEvent::OnRelease){
			auto gc = PizzaBox::SceneManager::CurrentScene()->GetComponentInScene<GameController>();
			if(gc != nullptr){
				gc->ResetScene();
			}
		}
	});

	auto titleButtonFunc = std::function<void(PizzaBox::UIEvent)>([](PizzaBox::UIEvent e){
		if(e == PizzaBox::UIEvent::OnRelease){
			PizzaBox::UIManager::DisableAllSets();
			PizzaBox::UIManager::EnableSet("LoadingSet");
			PizzaBox::SceneManager::LoadScene(1);
		}
	});

	auto uiSet = new PizzaBox::UISet("DeathSet");
	uiSet->AddElement(new PizzaBox::ImageUI("FiredLogo", "FiredLogo", PizzaBox::Rect(0.5f, 0.8f, 0.4f, 0.2f)));
	//uiSet->elements.push_back(new PizzaBox::TextUI("MenuText", PizzaBox::Rect(0.5f, 0.8f, 0.15f, 0.1f), true, "You Died!", "ArialFont"));

	auto button = new PizzaBox::ButtonUI("ReturnButton", restartButtonFunc, PizzaBox::Rect(0.5f, 0.4f, 0.18f, 0.1f));
	button->AddText("Restart");
	button->SetReceivesBackInput(true);
	uiSet->elements.push_back(button);

	button = new PizzaBox::ButtonUI("QuitButton", titleButtonFunc, PizzaBox::Rect(0.5f, 0.25f, 0.18f, 0.1f));
	button->AddText("Quit to Menu");
	uiSet->elements.push_back(button);

	PizzaBox::UIManager::AddSet(uiSet);
}

void Game::SetupLoadingUI(){
	auto uiSet = new PizzaBox::UISet("LoadingSet");
	uiSet->AddElement(new PizzaBox::ImageUI("BackgroundImage", "BlackTexture", PizzaBox::Rect(0.5f, 0.5f, 1.0f, 1.0f), false));
	uiSet->AddElement(new PizzaBox::TextUI("LoadingText", PizzaBox::Rect(0.5f, 0.85f, 0.175f, 0.15f), true, "Loading...", "ArialFont"));
	PizzaBox::UIManager::AddSet(uiSet);
}