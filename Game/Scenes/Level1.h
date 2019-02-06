#ifndef LEVEL_ONE_SCENE_H
#define LEVEL_ONE_SCENE_H

#include <Core/Scene.h>

namespace GamePackage {
	class Level1 : public PizzaBox::Scene {
	public:
		Level1(); 
		virtual ~Level1() override;

		virtual bool Initialize() override;
		virtual void Destroy() override;
	};
}
#endif //!LEVEL_ONE_SCENE_H