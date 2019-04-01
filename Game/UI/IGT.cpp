#include "IGT.h"

#include <sstream>
#include <iomanip>

#include <Core/Time.h>
#include <Tools/EngineStats.h>

using namespace GamePackage;

IGT::IGT(const std::string& name_, const PizzaBox::Rect& rect_, const std::string& fontName_) : TextUI(name_, rect_, false, "FPS: 0.00", fontName_, nullptr){}

IGT::~IGT(){}

void IGT::Render(){
	std::stringstream timeStream;
	timeStream << std::fixed << std::setprecision(2) << PizzaBox::EngineStats::GetFloat("IGT");

	SetText(timeStream.str());
	TextUI::Render();
}