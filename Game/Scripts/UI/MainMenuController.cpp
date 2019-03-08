#include "MainMenuController.h"

#include <Audio/AudioSource.h>
#include <Core/SceneManager.h>

using namespace GamePackage;

void MainMenuController::OnStart(){
	auto musicPlayer = gameObject->GetComponent<PizzaBox::AudioSource>();
	if(musicPlayer != nullptr){
		musicPlayer->PlayContinuous();
	}
}

void MainMenuController::OnUI(PizzaBox::UIEvent event_){
	if(event_ == PizzaBox::UIEvent::OnRelease){
		PizzaBox::SceneManager::LoadNextScene();
	}
}