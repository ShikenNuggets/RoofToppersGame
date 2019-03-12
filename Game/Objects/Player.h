#ifndef PLAYER_H
#define PLAYER_H

#include <Animation/AnimMeshRender.h>
#include <Audio/AudioSource.h>
#include <Graphics/Materials/TexturedMaterial.h>
#include <Object/GameObject.h>
#include <Physics/Rigidbody.h>

#include "Animators/PlayerAnimator.h"
#include "Scripts/PlayerController.h"

namespace GamePackage{
	class Player : public PizzaBox::GameObject{
	public:
		Player(const PizzaBox::Vector3& pos_, const PizzaBox::Euler& rot_, const PizzaBox::Vector3& scale_) : GameObject(pos_, rot_, scale_){
			SetTag("Player");
			PlayerAnimator* animator = new PlayerAnimator();
			std::vector<PizzaBox::MeshMaterial*> materials;
			materials.push_back(new PizzaBox::TexturedMaterial("RemyBody", true));
			materials.push_back(new PizzaBox::TexturedMaterial("RemyBody", true));
			materials.push_back(new PizzaBox::TexturedMaterial("RemyBody", true));
			materials.push_back(new PizzaBox::TexturedMaterial("RemyHair", true));
			materials.push_back(new PizzaBox::TexturedMaterial("RemyBottom", true));
			materials.push_back(new PizzaBox::TexturedMaterial("RemyTop", true));
			materials.push_back(new PizzaBox::TexturedMaterial("RemyShoes", true));
			AddComponent(new PizzaBox::AnimMeshRender("DudeModel", materials, animator));
			auto rb = new PizzaBox::Rigidbody(80.0f, true, true);
			rb->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
			rb->AddCollider(new PizzaBox::CapsuleCollider(5.0f, 10.0f), PizzaBox::Vector3(0.0f, 10.0f, 0.0f));

			auto grappleSFX = new PizzaBox::AudioSource("GrappleSFX", PizzaBox::AudioSource::SoundType::_2D, "SFX");
			auto jumpSFX = new PizzaBox::AudioSource("JumpingSFX", PizzaBox::AudioSource::SoundType::_2D, "SFX");
			auto walkSFX = new PizzaBox::AudioSource("WalkingSFX", PizzaBox::AudioSource::SoundType::_2D, "SFX");
			auto landingSFX = new PizzaBox::AudioSource("LandingSFX", PizzaBox::AudioSource::SoundType::_2D, "SFX");
			auto swingingSFX = new PizzaBox::AudioSource("SwingingSFX", PizzaBox::AudioSource::SoundType::_2D, "SFX");

			AddComponent(rb);
			AddComponent(grappleSFX);
			AddComponent(jumpSFX);
			AddComponent(walkSFX);
			AddComponent(landingSFX);
			AddComponent(swingingSFX);
			AddComponent(new PlayerController(animator, walkSFX, grappleSFX, jumpSFX, landingSFX, swingingSFX));
		}

		virtual ~Player() override{}
	};
}

#endif //!PLAYER_H