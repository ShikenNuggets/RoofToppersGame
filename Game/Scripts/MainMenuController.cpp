#include "MainMenuController.h"

#include <Audio/AudioSource.h>
#include <Core/SceneManager.h>

using namespace GGJ;

void MainMenuController::OnStart(){
	auto musicPlayer = gameObject->GetComponent<PizzaBox::AudioSource>();
	if(musicPlayer != nullptr){
		musicPlayer->PlayContinuous();
	}
}

void MainMenuController::OnUI(PizzaBox::UIEvent event_){
	if(event_ == PizzaBox::UIEvent::OnClick){
		PizzaBox::SceneManager::LoadScene(2);
	}
}