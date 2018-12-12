#ifndef DEFAULT_SCENE_H
#define DEFAULT_SCENE_H

#include <Core/Scene.h>

namespace GamePackage {
	class DefaultScene : public PizzaBox::Scene{
	public:
		DefaultScene();
		~DefaultScene();

		bool Initialize();
		void Destroy();
	};
}

#endif //!DEFAULT_SCENE_H
