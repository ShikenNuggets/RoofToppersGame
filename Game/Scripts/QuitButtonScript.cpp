#include "QuitButtonScript.h"

#include <Core/GameManager.h>

using namespace GamePackage;

QuitButtonScript::QuitButtonScript(){}

QuitButtonScript::~QuitButtonScript(){}

void QuitButtonScript::OnUI(UIEvent event_){
	if(event_ == UIEvent::OnClick){
		PizzaBox::GameManager::Stop();
	}
}