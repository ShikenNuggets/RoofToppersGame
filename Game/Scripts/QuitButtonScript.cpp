#include "QuitButtonScript.h"

#include <Core/GameManager.h>

using namespace GGJ;

QuitButtonScript::QuitButtonScript(){}

QuitButtonScript::~QuitButtonScript(){}

void QuitButtonScript::OnUI(PizzaBox::UIEvent event_){
	if(event_ == PizzaBox::UIEvent::OnClick){
		PizzaBox::GameManager::Stop();
	}
}