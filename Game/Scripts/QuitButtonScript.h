#ifndef QUIT_BUTTON_SCRIPT_H
#define QUIT_BUTTON_SCRIPT_H

#include <Script/Script.h>

namespace GamePackage {
	class QuitButtonScript : public PizzaBox::Script{
	public:
		QuitButtonScript();
		virtual ~QuitButtonScript() override;

		void OnStart() override{}
		void Update(const float deltaTime_) override{}
		void OnDestroy() override{}
		virtual void OnUI(UIEvent event_);
	};
}

#endif //!QUIT_BUTTON_SCRIPT_H