#include "QuitButtonScript.h"

#include <Core/GameManager.h>

using namespace GamePackage;

QuitButtonScript::QuitButtonScript(){}

QuitButtonScript::~QuitButtonScript(){}

void QuitButtonScript::OnUI(PizzaBox::UIEvent event_){
	if(event_ == PizzaBox::UIEvent::OnRelease){
		PizzaBox::GameManager::Stop();
	}
}