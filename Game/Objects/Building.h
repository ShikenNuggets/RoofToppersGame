#ifndef BUILDING_H
#define BUILDING_H

#include <Graphics/Materials/TexturedMaterial.h>
#include <Graphics/Models/MeshRender.h>
#include <Object/GameObject.h>
#include <Physics/Collider.h>

namespace GamePackage{
	class Building : public PizzaBox::GameObject{
	public:
		Building(const PizzaBox::Vector3& pos_ = PizzaBox::Vector3(), const PizzaBox::Euler& rot_ = PizzaBox::Euler(), const PizzaBox::Vector3& scale_ = PizzaBox::Vector3(1.0f, 1.0f, 1.0f)) : GameObject(pos_, rot_, scale_){
			AddComponent(new PizzaBox::MeshRender("CubeModel", new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 20.0f)));
			AddComponent(new PizzaBox::Collider(GlobalScale()));
			SetTag("Platform");
			SetStatic(true);
		}

		virtual ~Building() override{}
	};
}

#endif BUILDING_H