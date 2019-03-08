#ifndef MONSTER_CONTROLLER_H
#define MONSTER_CONTROLLER_H

#include <Audio/AudioSource.h>
#include <Graphics/Camera.h>
#include <Physics/Collider.h>
#include <Physics/Rigidbody.h>
#include <Script/Script.h>

#include "Animators/PlayerAnimator.h"
#include "GrapplePoint.h"

namespace GamePackage {
	class PlayerController : public PizzaBox::Script{
	public:
		PlayerController(PizzaBox::Camera* camera_, PlayerAnimator* animator_);
		virtual ~PlayerController() override;

		virtual void OnStart() override;
		virtual void Update(const float deltaTime_) override;
		virtual void OnDestroy() override;
		virtual void OnCollision(const PizzaBox::CollisionInfo& other_) override; 
		virtual void OnCollisionExit(PizzaBox::GameObject* other_) override;

	private:
		PizzaBox::Camera* camera;
		PlayerAnimator* animator;
		PizzaBox::Rigidbody* rigidbody;

		bool isWalking;
		bool isGrounded;
		bool isSwinging;
		bool isSwitchingToSwinging;

		float maxRotationPerSecond, MoveY;
		float pullSpeed, currentGrappleLength;
		float maxGrappleLength = 80.0f;

		void GroundMovement(float deltaTime_);
		void Swinging(float deltaTime_);

		void SwitchToSwinging();
		void SwitchToGroundMovement();
		
		GrapplePoint* FindNearestGrapple();
	};
}

#endif //!MONSTER_CONTROLLER_H