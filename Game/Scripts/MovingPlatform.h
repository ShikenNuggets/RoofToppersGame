#ifndef MOVING_PLATFORM_H
#define MOVING_PLATFORM_H

#include <Script/Script.h>
#include <Math/Vector.h>

namespace GamePackage {
	class MovingPlatform : public PizzaBox::Script {
	public:
		MovingPlatform();

		virtual void OnStart() override;
		virtual void Update(const float deltaTime_) override;
		virtual void OnDestroy() override;

		virtual void OnCollision(const PizzaBox::CollisionInfo& info_) override;
		//Setters
		void SetDirection(PizzaBox::Vector3 dir);
		void SetDirectionSpeed(float speed_);
		void SetDistance(float dis);
	private:
		//these are for setup
		PizzaBox::Vector3 direction;
		float directionSpeed;
		float distance;
		//These are for holding info
		float useSpeed;
		float origin;
	};
}

#endif //!MOVING_PLATFORM_H