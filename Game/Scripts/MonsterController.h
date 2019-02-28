#ifndef MONSTER_CONTROLLER_H
#define MONSTER_CONTROLLER_H

#include <Audio/AudioSource.h>
#include <Graphics/Camera.h>
#include <Physics/Collider.h>
#include <Script/Script.h>

#include "Animators/MonsterAnimator.h"

namespace GGJ{
	class MonsterController : public PizzaBox::Script{
	public:
		MonsterController(PizzaBox::Camera* camera_, MonsterAnimator* animator_, PizzaBox::Collider* punchCollider_, PizzaBox::AudioSource* punch1_, PizzaBox::AudioSource* punch2_, PizzaBox::AudioSource* walk_);
		virtual ~MonsterController() override;

		virtual void OnStart() override;
		virtual void Update(const float deltaTime_) override;
		virtual void OnDestroy() override;
		virtual void OnCollision(PizzaBox::GameObject* other_) override;

		void BeginGrow();
		void BeginShrink();

	private:
		PizzaBox::Camera* camera;
		MonsterAnimator* animator;
		PizzaBox::Collider* punchCollider;
		PizzaBox::AudioSource* punch1;
		PizzaBox::AudioSource* punch2;
		PizzaBox::AudioSource* walk;

		bool isWalking;
		bool isPunching;

		float maxRotationPerSecond;
		bool isGrowing;
		bool isShrinking;
		float growSpeed;
		float shrinkSpeed;
		float oldScale;
		float sizeTimer;

		void Grow();
		void Shrink();
	};
}

#endif //!MONSTER_CONTROLLER_H