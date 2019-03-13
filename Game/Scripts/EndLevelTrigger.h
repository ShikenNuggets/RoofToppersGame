#ifndef END_LEVEL_TRIGGER_H
#define END_LEVEL_TRIGGER_H

#include <Script/Script.h>
#include <Core/SceneManager.h>

namespace GamePackage{
	class EndLevelTrigger : public PizzaBox::Script{
	public:
		virtual void Update(const float deltaTime_) override{}
		virtual void OnDestroy() override{}

		virtual void OnCollision(const PizzaBox::CollisionInfo& other_) override;
	};
}

#endif // !END_LEVEL_TRIGGER_H