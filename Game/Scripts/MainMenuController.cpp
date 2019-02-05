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

void MainMenuController::OnUI(UIEvent event_){
	if(event_ == UIEvent::OnClick){
		PizzaBox::SceneManager::LoadScene(2);
	}
}