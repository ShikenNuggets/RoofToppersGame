#ifndef TUTORIAL_SCENE_H
#define TUTORIAL_SCENE_H

#include <Core/Scene.h>

namespace GamePackage {
	class Tutorial : public PizzaBox::Scene {
	public:
		Tutorial();
		virtual ~Tutorial() override;

		virtual bool Initialize() override;
		virtual void Destroy() override;
	};
}
#endif //!TUTORIAL_SCENE_H