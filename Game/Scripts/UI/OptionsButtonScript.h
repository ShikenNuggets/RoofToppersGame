#ifndef OPTIONS_BUTTON_SCRIPT_H
#define OPTIONS_BUTTON_SCRIPT_H

#include <Script/Script.h>

namespace GamePackage{
	class OptionsButtonScript : public PizzaBox::Script{
	public:
		OptionsButtonScript();
		virtual ~OptionsButtonScript() override;

		void OnStart() override{}
		void Update(const float deltaTime_) override{}
		void OnDestroy() override{}
		virtual void OnUI(PizzaBox::UIEvent event_);
	};
}

#endif //!OPTIONS_BUTTON_SCRIPT_H