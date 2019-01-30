#ifndef SAM_CONTROLLER_H
#define SAM_CONTROLLER_H

#include <Object/GameObject.h>
#include <Script/Script.h>

namespace GGJ{
	class SAMController : public PizzaBox::Script{
	public:
		enum class State{
			Idle,
			Targeting,
			Firing
		};

		SAMController(PizzaBox::GameObject* target_ = nullptr);

		virtual void OnStart() override;
		virtual void Update(const float deltaTime_) override;
		virtual void OnDestroy() override;

	private:
		PizzaBox::GameObject* target;
		State currentState;
		float delay;
		float timeSinceLastFire;
		float elapsedTime;
		float targetDistance;
		float rotateSpeed;
		float maxRotationPerSecond;

		void RotateTurret(const PizzaBox::Vector3& targetDir, float deltaTime_);
	};
}

#endif //!SAM_CONTROLLER_H