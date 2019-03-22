#ifndef LEVEL_TWO_SCENE_H
#define LEVEL_TWO_SCENE_H

#include <Core/Scene.h>

namespace GamePackage {
	class Level2 : public PizzaBox::Scene {
	public:
		Level2();
		virtual ~Level2() override;

		virtual bool Initialize() override;
		virtual void Destroy() override;
	};
}
#endif //!LEVEL_TWO_SCENE_H