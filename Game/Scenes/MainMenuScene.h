#ifndef MAIN_MENU_SCENE_H
#define MAIN_MENU_SCENE_H

#include <Core/Scene.h>

namespace GamePackage {
	class MainMenuScene : public PizzaBox::Scene{
	public:
		MainMenuScene();
		virtual ~MainMenuScene() override;

		virtual bool Initialize() override;
		virtual void Destroy() override;
	};
}

#endif //!MAIN_MENU_SCENE_H