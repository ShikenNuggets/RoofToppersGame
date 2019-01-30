#ifndef BUILDING_H
#define BUILDING_H

#include <Object/GameObject.h>
#include <Script/Script.h>

namespace GGJ{
	class Building : public PizzaBox::Script{
	public:
		Building(float collapseTime_ = 5.0f);

		virtual void OnStart() override;
		virtual void Update(const float deltaTime_) override;
		virtual void OnDestroy() override;
		virtual void OnCollision(const PizzaBox::GameObject* const other_);

	private:
		float health;
		bool wasHitThisFrame;
		bool isBeingDestroyed;
		float collapseSpeed;
		float collapseTimer;
		float collapseTime;

		void BeginDestruction();
	};
}

#endif //!BUILDING_H