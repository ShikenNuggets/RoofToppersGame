#ifndef MISSILE_H
#define MISSILE_H

#include <Object/GameObject.h>
#include <Script/Script.h>

namespace GGJ{
	class Missile : public PizzaBox::Script{
	public:
		Missile(PizzaBox::GameObject* target_);

		void OnStart() override;
		void Update(const float deltaTime_) override;
		void OnDestroy() override;

	private:
		PizzaBox::GameObject* target;
		float speed, lifeSpan, elapsedTime, targetingDuration, targetingStart;
		bool isTracking;

		void UpdateRotation(const PizzaBox::Vector3 targetDir);
	};
}

#endif //!MISSILE_H