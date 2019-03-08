#ifndef MAIN_MENU_CONTROLLER_H
#define MAIN_MENU_CONTROLLER_H

#include <Script/Script.h>

namespace GamePackage {
	class MainMenuController : public PizzaBox::Script{
	public:
		MainMenuController(){}
		virtual ~MainMenuController() override{}

		void OnStart() override;
		void Update(const float deltaTime_) override{}
		void OnDestroy() override{}
		virtual void OnUI(PizzaBox::UIEvent event_) override;
	};
}

#endif //!MAIN_MENU_CONTROLLER_H