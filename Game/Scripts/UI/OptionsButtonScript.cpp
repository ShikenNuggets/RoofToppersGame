#include "OptionsButtonScript.h"

#include <Graphics/UI/UIManager.h>

using namespace GamePackage;

OptionsButtonScript::OptionsButtonScript(){}

OptionsButtonScript::~OptionsButtonScript(){}

void OptionsButtonScript::OnUI(PizzaBox::UIEvent event_){
	if(event_ == PizzaBox::UIEvent::OnRelease){
		PizzaBox::UIManager::DisableSet("MainMenuSet");
		PizzaBox::UIManager::EnableSet("OptionsSet");
	}
}