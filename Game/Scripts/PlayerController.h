#ifndef MONSTER_CONTROLLER_H
#define MONSTER_CONTROLLER_H

#include <Audio/AudioSource.h>
#include <Graphics/Camera.h>
#include <Physics/Collider.h>
#include <Script/Script.h>

#include "Animators/PlayerAnimator.h"

namespace GamePackage {
	class PlayerController : public PizzaBox::Script{
	public:
		PlayerController(PizzaBox::Camera* camera_, PlayerAnimator* animator_);
		virtual ~PlayerController() override;

		virtual void OnStart() override;
		virtual void Update(const float deltaTime_) override;
		virtual void OnDestroy() override;
		virtual void OnCollision(PizzaBox::GameObject* other_) override; 

	private:
		PizzaBox::Camera* camera;
		PlayerAnimator* animator;  

		bool isWalking; 

		float maxRotationPerSecond, MoveY;
	};
}

#endif //!MONSTER_CONTROLLER_H